from llvmlite import ir

from pryst.generated.PrystParser import PrystParser


def map_type(t: PrystParser.Type_Context):
    val = t.getText()

    if val == "int":
        return ir.IntType(32)
    elif val == "double":
        return ir.DoubleType()
    else:
        raise Exception("Can't map type to llvm")
