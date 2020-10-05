from pryst.AST.builder.ExprVisitor import ExprVisitorMixin
from pryst.AST.builder.StmtVisitor import StmtVisitorMixin

from pryst.parser.PrystParser import PrystParser
from pryst.parser.PrystVisitor import PrystVisitor

from pryst.AST import ast


class CustomVisitor(StmtVisitorMixin, ExprVisitorMixin, PrystVisitor):

    #
    # Visit parse tree produced from a file
    #
    def visitFile_input(self, ctx: PrystParser.File_inputContext):
        statements = []

        for stmt in ctx.stmt():
            statement = self.visit(stmt)
            if statement != None:
                if type(statement) is list:
                    statements += statement
                else:
                    statements.append(statement)

        return ast.Module(body=statements)

    #
    # Single input is used both in interpreter mode and with strings passes as a parameter
    #
    def visitSingle_input(self, ctx: PrystParser.Single_inputContext):
        if ctx.compound_stmt() != None:
            return ast.Interactive(self.visit(ctx.compound_stmt()))

        elif ctx.simple_stmt() != None:
            return ast.Interactive(self.visit(ctx.simple_stmt()))

        return None

    #
    # Visit single expression (call to the eval() function)
    #
    def visitEval_input(self, ctx: PrystParser.Eval_inputContext):
        return ast.EvalExpression(self.visit(ctx.test()))
