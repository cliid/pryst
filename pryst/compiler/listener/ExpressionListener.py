from antlr4 import ParseTreeWalker
from llvmlite import ir
from llvmlite.ir import Argument

from pryst.compiler.context.FunctionContext import FunctionContext
from pryst.generated.PrystLexer import PrystLexer
from pryst.generated.PrystListener import PrystListener
from pryst.generated.PrystParser import PrystParser


class ExpressionListener(PrystListener):
    stack = []

    def __init__(self, builder: ir.IRBuilder, context: FunctionContext):
        self.context = context
        self.builder = builder

    def exitExpressionFunctionCall(self, ctx: PrystParser.ExpressionFunctionCallContext):
        program_context = self.context.program_context
        callee_function_context = program_context.get_function(
            ctx.functionCall().ID().getText())
        callee_function = callee_function_context.function

        params = []
        for param in ctx.functionCall().params().param():
            #     listener = ExpressionListener(self.builder, self.context)
            #     walker = ParseTreeWalker()
            #     walker.walk(listener, param.expression())
            #     expression_result = listener.stack.pop()
            params.append(self.stack.pop())
        #     self.stack.pop()

        self.stack.append(self.builder.call(callee_function, params))

    def exitExpressionAdd(self, ctx: PrystParser.ExpressionAddContext):
        left = self.stack.pop()
        right = self.stack.pop()

        if isinstance(left.type, ir.DoubleType) or isinstance(right.type, ir.DoubleType):
            add_function = self.builder.fadd
            sub_function = self.builder.fsub

            double_type = ir.DoubleType()
            left = self.builder.inttoptr(left, double_type)
            right = self.builder.inttoptr(right, double_type)

        elif isinstance(left.type, ir.IntType) and isinstance(right.type, ir.IntType):
            add_function = self.builder.add
            sub_function = self.builder.sub
        else:
            raise Exception(
                "Cannot convert {} and {} to the same type".format(left, right))

        if ctx.op.text == "+":
            self.stack.append(add_function(right, left))
        elif ctx.op.text == "-":
            self.stack.append(sub_function(right, left))

    def exitExpressionMul(self, ctx: PrystParser.ExpressionAddContext):
        left = self.stack.pop()
        right = self.stack.pop()

        if ctx.op.text == "*":
            self.stack.append(self.builder.mul(right, left))
        elif ctx.op.text == "/":
            self.stack.append(self.builder.udiv(right, left))

    def enterAtom(self, ctx: PrystParser.AtomContext):
        t = ctx.op.type
        val = ctx.getText()
        if t == PrystLexer.INT:
            res = ir.Constant(ir.IntType(32), int(val))
        elif t == PrystLexer.DECIMAL:
            res = ir.Constant(ir.DoubleType(), float(val))
        elif t == PrystParser.ID:
            pointer = self.context.get_variable(val)

            # Can be either argument or local variable
            if isinstance(pointer, Argument):
                res = pointer
            else:
                res = self.builder.load(pointer, val)
        else:
            raise Exception(
                "Cannot convert type {0} to machine LLVM".format(str(t)))

        self.stack.append(res)
