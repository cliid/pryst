antlr4 -Dlanguage=Cpp -no-listener -visitor -o src/generated Pryst.g4
rm -rf build
mkdir build
cd build
cmake ..
make
./pryst ../examples/hello.pst --aot
