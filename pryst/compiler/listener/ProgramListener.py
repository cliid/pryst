import llvmlite.binding as llvm
from antlr4 import ParseTreeWalker
from llvmlite import ir

from pryst.compiler.context.FunctionContext import FunctionContext
from pryst.compiler.context.ProgramContext import ProgramContext
from pryst.compiler.listener.FunctionListener import FunctionListener
from pryst.generated.PrystListener import PrystListener
from pryst.generated.PrystParser import PrystParser


class ProgramListener(PrystListener):
    stack = []

    def __init__(self):
        self.module = ir.Module("expression")
        self.context = ProgramContext()
        self.init_stdlib()

    def init_stdlib(self):
        llvm.load_library_permanently('./out/stdlib.o')

        int_type = ir.IntType(32)
        printint_type = ir.FunctionType(int_type, (int_type,))
        printint = ir.Function(self.module, printint_type, name="printint")

        stdlib_function_context = FunctionContext(
            "printint", self.context, printint)
        self.context.add_function("printint", stdlib_function_context)

    def enterFunction(self, ctx: PrystParser.FunctionContext):
        listener = FunctionListener(self.module, self.context)

        walker = ParseTreeWalker()
        walker.walk(listener, ctx)
