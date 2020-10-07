from antlr4 import ParseTreeWalker
from llvmlite import ir

from pryst.compiler.context.FunctionContext import FunctionContext
from pryst.compiler.listener.ExpressionListener import ExpressionListener
from pryst.compiler.util.type_mapper import map_type
from pryst.generated.PrystListener import PrystListener
from pryst.generated.PrystParser import PrystParser


class StatementListener(PrystListener):
    def __init__(self, builder: ir.IRBuilder, context: FunctionContext):
        self.context = context
        self.builder = builder

        self.condition = None

    def enterReturnStatement(self, ctx: PrystParser.ReturnStatementContext):
        walker = ParseTreeWalker()
        listener = ExpressionListener(self.builder, self.context)
        walker.walk(listener, ctx)

        if self.condition is not None:
            with self.builder.if_then(self.condition):
                self.builder.ret(listener.stack.pop())
        else:
            self.builder.ret(listener.stack.pop())

    def enterAssignmentStatement(self, ctx: PrystParser.AssignmentStatementContext):
        t = map_type(ctx.type_())
        name = ctx.ID().getText()
        pointer = self.builder.alloca(t, 1, name)

        walker = ParseTreeWalker()
        listener = ExpressionListener(self.builder, self.context)
        walker.walk(listener, ctx)
        value = listener.stack.pop()

        self.builder.store(value, pointer)
        self.context.add_variable(name, pointer)

    def enterIfStatement(self, ctx: PrystParser.IfStatementContext):
        walker = ParseTreeWalker()
        listener = ExpressionListener(self.builder, self.context)
        walker.walk(listener, ctx.equation().expression(0))
        left = listener.stack.pop()

        walker = ParseTreeWalker()
        listener = ExpressionListener(self.builder, self.context)
        walker.walk(listener, ctx.equation().expression(1))
        right = listener.stack.pop()

        operation = ctx.equation().op.getText()
        self.condition = self.builder.icmp_signed(
            cmpop=operation, lhs=left, rhs=right)

    def exitIfStatement(self, ctx: PrystParser.IfStatementContext):
        self.context = None
