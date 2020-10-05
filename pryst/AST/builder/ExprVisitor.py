from pryst.parser.PrystParser import PrystParser
from pryst.parser.PrystVisitor import PrystVisitor

from pryst import AST
from pryst.AST.ast import MemoryContext


class ExprVisitorMixin(PrystVisitor):

    #
    # Tests (comparisons)
    #

    def visitComparison(self, ctx: PrystParser.ComparisonContext):
        left = self.visit(ctx.test(0))
        right = self.visit(ctx.test(1))
        op = ctx.comp_op().getText()

        firstSymbolType = ctx.comp_op().children[0].symbol.type

        if firstSymbolType == PrystParser.IN:
            op = AST.expr.Compare.Op.IN
        elif firstSymbolType == PrystParser.IS:
            op = AST.expr.Compare.Op.IS

        if len(ctx.comp_op().children) == 2:
            secondSymbolType = ctx.comp_op().children[1].symbol.type

            if firstSymbolType == PrystParser.NOT and secondSymbolType == PrystParser.IN:
                op = AST.expr.Compare.Op.NOT_IN
            elif firstSymbolType == PrystParser.IS and secondSymbolType == PrystParser.NOT:
                op = AST.expr.Compare.Op.IS_NOT
            else:
                raise ValueError("Unexpected binary comparison operation")

        return AST.expr.BinaryComp(left=left, right=right, op=op)

    def visitNotTest(self, ctx: PrystParser.NotTestContext):
        test = self.visit(ctx.test())
        return AST.expr.UnaryComp(operand=test, op=AST.expr.Compare.Op.NOT)

    def visitAndTest(self, ctx: PrystParser.AndTestContext):
        left = self.visit(ctx.test(0))
        right = self.visit(ctx.test(1))
        return AST.expr.BinaryComp(left=left, right=right, op=AST.expr.Compare.Op.AND)

    def visitOrTest(self, ctx: PrystParser.AndTestContext):
        left = self.visit(ctx.test(0))
        right = self.visit(ctx.test(1))
        return AST.expr.BinaryComp(left=left, right=right, op=AST.expr.Compare.Op.OR)

    #
    # Arithmetic (@expr rule)
    #

    binaryExprTable = {
        PrystParser.ADD: AST.expr.AddOp,
        PrystParser.MINUS: AST.expr.SubOp,
        PrystParser.STAR: AST.expr.MultOp,
        PrystParser.DIV: AST.expr.DivOp,
        PrystParser.MOD: AST.expr.ModOp,
        PrystParser.LEFT_SHIFT: AST.expr.LshiftOp,
        PrystParser.RIGHT_SHIFT: AST.expr.RshiftOp,
        PrystParser.AND_OP: AST.expr.BitAndOp,
        PrystParser.XOR: AST.expr.BitXorOp,
        PrystParser.OR_OP: AST.expr.BitOrOp,
    }

    def visitGenericExpr(self, ctx):
        left = self.visit(ctx.expr(0))
        right = self.visit(ctx.expr(1))

        try:
            return ExprVisitorMixin.binaryExprTable[ctx.op.type](left, right)
        except KeyError:
            raise ValueError("Unexpected op type")

    def visitMulDivMod(self, ctx: PrystParser.MulDivModContext):
        return self.visitGenericExpr(ctx)

    def visitAddSub(self, ctx: PrystParser.AddSubContext):
        return self.visitGenericExpr(ctx)

    def visitShifts(self, ctx: PrystParser.ShiftsContext):
        return self.visitGenericExpr(ctx)

    def visitBitAnd(self, ctx: PrystParser.BitAndContext):
        return self.visitGenericExpr(ctx)

    def visitBitXor(self, ctx: PrystParser.BitXorContext):
        return self.visitGenericExpr(ctx)

    def visitBitOr(self, ctx: PrystParser.BitOrContext):
        return self.visitGenericExpr(ctx)

    #
    # Factor rule
    #

    def visitUnaryExpr(self, ctx: PrystParser.UnaryExprContext):
        operand = ctx.factor().accept(self)
        return AST.expr.UnaryOp(op=ctx.op.text, operand=operand)

    def visitParenExpr(self, ctx: PrystParser.ParenExprContext):
        return self.visit(ctx.test())

    def visitAtom(self, ctx: PrystParser.AtomContext):
        if ctx.NONE() != None:
            return AST.expr.NameConstant('None')
        elif ctx.TRUE() != None:
            return AST.expr.NameConstant('True')
        elif ctx.FALSE() != None:
            return AST.expr.NameConstant('False')

        # Visit other nodes
        return self.visitChildren(ctx)

    #
    # Name access: PlainName, FuncInvoke, SubName
    #

    def nameContextFor(self, ctx):
        if type(ctx.parentCtx) is PrystParser.ExprStmtAssignContext or type(ctx.parentCtx) is PrystParser.ExprStmtAugmentedContext:
            return MemoryContext.Store
        else:
            return MemoryContext.Load

    def visitPlainName(self, ctx: PrystParser.PlainNameContext):
        context = self.nameContextFor(ctx)
        return AST.expr.Name(id=ctx.NAME().getText(), ctx=context)

    def visitFuncInvoke(self, ctx: PrystParser.FuncInvokeContext):
        funcName = self.visit(ctx.nameaccess())
        args = []

        if ctx.arglist() != None:
            for argStmt in ctx.arglist().test():
                arg = self.visit(argStmt)
                if arg != None:
                    args.append(arg)

        return AST.expr.CallExpr(func=funcName, args=args)

    def visitDottedName(self, ctx: PrystParser.DottedNameContext):
        left = self.visit(ctx.nameaccess())
        attrName = ctx.NAME().getText()
        return AST.stmt.Attribute(value=left, attr=attrName, ctx=MemoryContext.Load)

    def visitSubName(self, ctx: PrystParser.SubNameContext):
        leftNode = self.visit(ctx.nameaccess())
        subscript = self.visit(ctx.subscript())

        context = self.nameContextFor(ctx)

        return AST.stmt.Subscript(value=leftNode, slice=subscript, ctx=context)

    #
    # Index and slice operations
    #

    def visitSubscriptIndex(self, ctx: PrystParser.SubscriptIndexContext):
        test = self.visit(ctx.test())
        return AST.stmt.Index(value=test)

    def visitSubscriptSlice(self, ctx: PrystParser.SubscriptSliceContext):
        lower = upper = None

        if ctx.lower != None:
            lower = self.visit(ctx.lower)

        if ctx.upper != None:
            upper = self.visit(ctx.upper)

        return AST.stmt.Slice(lower=lower, upper=upper, step=None)
    #
    # Collection definitions
    #

    def visitDictorsetmaker(self, ctx: PrystParser.DictorsetmakerContext):
        if ctx.dictormaker() != None:
            return self.visit(ctx.dictormaker())

        if ctx.setmaker() != None:
            return self.visit(ctx.setmaker())

    def visitDictMaker(self, ctx: PrystParser.DictMakerContext):
        if ctx.dictorsetmaker() != None:
            return self.visit(ctx.dictorsetmaker())

        return AST.expr.DictContainer({})

    def visitSetmaker(self, ctx: PrystParser.SetmakerContext):
        result = set({})
        for test in ctx.test():
            result.add(self.visit(test))
        return AST.expr.SetContainer(result)

    def visitDictormaker(self, ctx: PrystParser.DictormakerContext):
        if ctx.test(0) != None:
            left = self.visit(ctx.test(0))
            right = self.visit(ctx.test(1))
            return AST.expr.DictContainer({left: right})

        if ctx.dictormaker(0) != None:
            left = self.visit(ctx.dictormaker(0))
            right = self.visit(ctx.dictormaker(1))

            result = left.copy()
            result.update(right)

            if type(result) is not AST.expr.DictContainer:
                return AST.expr.DictContainer(result)
            else:
                return result

    def visitListMaker(self, ctx: PrystParser.ListMakerContext):
        if ctx.testlist_comp() == None:
            return AST.expr.ListContainer([])

        return AST.expr.ListContainer(self.visit(ctx.testlist_comp()))

    def visitTupleMaker(self, ctx: PrystParser.TupleMakerContext):
        if ctx.testlist_comp() == None:
            return AST.expr.TupleContainer(())

        return AST.expr.TupleContainer(tuple(self.visit(ctx.testlist_comp())))

    def visitTestlist_comp(self, ctx: PrystParser.Testlist_compContext):
        if ctx.test() != None:
            return [self.visit(ctx.test())]

        if ctx.testlist_comp(1) == None:
            return self.visit(ctx.testlist_comp(0))

        left = self.visit(ctx.testlist_comp(0))
        right = self.visit(ctx.testlist_comp(1))
        result = []

        if type(left) is list:
            result += left
        else:
            result.append(left)

        if type(right) is list:
            result += right
        else:
            result.append(right)

        return result

    #
    # Strings and numbers
    #

    def visitNumber(self, ctx: PrystParser.NumberContext):
        if ctx.integer() != None:
            return self.visit(ctx.integer())

        elif ctx.FLOAT_NUMBER() != None:
            number = float(ctx.FLOAT_NUMBER().getText())
            return AST.expr.Num(number)

        raise ValueError()

    def visitInteger(self, ctx: PrystParser.IntegerContext):
        if ctx.DECIMAL_INTEGER() != None:
            decimal = int(ctx.DECIMAL_INTEGER().getText())
            return AST.expr.Num(decimal)

        elif ctx.HEX_INTEGER() != None:
            hex = int(ctx.HEX_INTEGER().getText(), 16)
            return AST.expr.Num(hex)

        elif ctx.BIN_INTEGER() != None:
            bin = int(ctx.BIN_INTEGER().getText(), 2)
            return AST.expr.Num(bin)

        elif ctx.OCT_INTEGER() != None:
            oct = int(ctx.OCT_INTEGER().getText(), 8)
            return AST.expr.Num(oct)

        raise ValueError()

    def visitString(self, ctx: PrystParser.StringContext):
        node = ctx.STRING_LITERAL()
        if node != None:
            text = node.getText()[1:-1]
            return AST.expr.Str(text)

        raise ValueError()
