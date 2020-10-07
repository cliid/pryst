from antlr4 import ParseTreeWalker
from llvmlite import ir

from pryst.compiler.context.FunctionContext import FunctionContext
from pryst.compiler.listener.StatementListener import StatementListener
from pryst.generated.PrystListener import PrystListener
from pryst.generated.PrystParser import PrystParser


class FunctionBodyListener(PrystListener):
    def __init__(self, builder: ir.IRBuilder, context: FunctionContext):
        self.builder = builder
        self.context = context

    def enterFunctionBody(self, ctx: PrystParser.FunctionBodyContext):
        for child in ctx.children:
            listener = StatementListener(self.builder, self.context)
            walker = ParseTreeWalker()
            walker.walk(listener, child)
