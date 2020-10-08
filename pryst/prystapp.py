import sys
import os
import argparse
from pathlib import Path
from antlr4 import *
from antlr4.tree.Trees import Trees
from pryst.utils.CST import CstFlattened, CstFiltered
import llvmlite.binding as llvm
from pryst.generated.PrystLexer import PrystLexer
from pryst.generated.PrystParser import PrystParser
from pryst.compiler.listener.CompilationUnitListener import CompilationUnitListener


def generate_object_file(module, output_name):
    llvm.initialize()
    llvm.initialize_native_target()
    llvm.initialize_native_asmprinter()
    target = llvm.Target.from_default_triple()

    target_machine = target.create_target_machine(opt=3)
    module_ref = llvm.parse_assembly(str(module))

    obj = target_machine.emit_object(module_ref)

    with open("./out/program.o", "wb") as f:
        f.write(obj)


def main():
    argParser = argparse.ArgumentParser()
    argParser.add_argument('filename', type=str, nargs='?',
                           help='Path to the script file.')
    argParser.add_argument('--tokens',  dest='parse_tree',  action='store_true',
                           help='Show string representation of a parse tree for the input')
    argParser.add_argument('--cst', dest='cst', action='store_true',
                           help='Show flattened concreted syntax tree for the input (parse tree)')
    #
    # Parse arguments
    #
    argParser.set_defaults(cst=False, parse_tree=False)
    args = argParser.parse_args()
    with open(args.filename) as file_contents:
        content = file_contents.read()
    if Path(args.filename).suffix == '.pst':
        os.system('rm -rf out')
        os.system('mkdir out')
        os.system('as ./bootstrap/start.s -o ./out/start.o')
        os.system(
            'clang -shared -O3 ./bootstrap/stdlib.c -o ./out/stdlib.o')
        input_stream = InputStream(content)
        lexer = PrystLexer(input_stream)
        tokens = CommonTokenStream(lexer)

        parser = PrystParser(tokens)
        parse_tree = parser.compilationUnit()
        # Print parse trees if need (full or flattened)
        if args.parse_tree:
            parseTreeString = Trees.toStringTree(parse_tree, recog=parser)
            print(parseTreeString)

        if args.cst:
            cst = CstFiltered(tree=parse_tree)
            print(cst)

        printer = CompilationUnitListener()
        walker = ParseTreeWalker()
        walker.walk(printer, parse_tree)
        generate_object_file(printer.module, args.filename)
        os.system(
            'ld ./out/program.o ./out/start.o ./out/stdlib.o -o ' + str(Path(args.filename))[:-4])
        os.system('objdump -d ' + str(Path(args.filename))[:-4])
    else:
        exit(1)  # Say is your extension .pst


if __name__ == '__main__':
    main()
