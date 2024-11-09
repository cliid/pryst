antlr4 -Dlanguage=Cpp -no-listener -visitor -o src/generated Pryst.g4
rm -rf build
mkdir build
cd build
# export CC=/usr/bin/clang-20
# export CXX=/usr/bin/clang++-20
cmake ..
make
