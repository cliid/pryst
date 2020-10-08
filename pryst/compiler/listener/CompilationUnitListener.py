import llvmlite.binding as llvm
from antlr4 import ParseTreeWalker
from llvmlite import ir

from pryst.generated.PrystListener import PrystListener
from pryst.generated.PrystParser import PrystParser


class CompilationUnitListener(PrystListener):
    stack = []

    def __init__(self):
        pass

    def init_stdlib(self):
        pass

    def enterCompilationUnit(self, ctx: PrystParser.CompilationUnitContext):
        pass
