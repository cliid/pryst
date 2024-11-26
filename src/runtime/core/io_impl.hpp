#pragma once

#include <string>
#include <memory>
#include <fstream>
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Function.h"

// Function declarations for runtime bindings
extern "C" {
    void pryst_io_print_impl(const char* message);
    void pryst_io_println_impl(const char* message);
    char* pryst_io_readLine_impl();
    char pryst_io_getChar_impl();
    void* pryst_io_File_new(const char* path);
    char* pryst_io_File_readString(void* file);
    bool pryst_io_File_writeString(void* file, const char* content);
    void pryst_io_File_close(void* file);
}

namespace pryst {
namespace io {

class IOImpl {
public:
    static void print(const std::string& message);
    static void println(const std::string& message);
    static std::string readLine();
    static char getChar();

    static void registerInLLVM(llvm::Module* module, llvm::IRBuilder<>& builder);
};

class FileImpl {
private:
    std::string path;
    std::unique_ptr<std::fstream> file;

public:
    FileImpl(const std::string& path);
    ~FileImpl();

    // Updated method names and return types for better error handling
    std::string* readString();  // Returns nullptr on error
    bool writeString(const std::string& content);
    void close();

    static void registerInLLVM(llvm::Module* module, llvm::IRBuilder<>& builder);

    // Helper method to check if file is open and valid
    bool isValid() const { return file && file->is_open(); }
};

} // namespace io
} // namespace pryst
