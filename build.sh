#!/bin/bash

# Generate ANTLR files
antlr4 -Dlanguage=Cpp -no-listener -visitor -o src/generated Pryst.g4

# Copy template files
cp templates/PrystBaseVisitor.h.template src/generated/PrystBaseVisitor.h
cp templates/PrystVisitor.h.template src/generated/PrystVisitor.h

# Build project
rm -rf build
mkdir build
cd build
# export CC=/usr/bin/clang-20
# export CXX=/usr/bin/clang++-20
cmake ..
make
