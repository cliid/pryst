#include <string>
#include <sstream>
#include <memory>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>

namespace pryst {
namespace runtime {

// Format string with placeholders
extern "C" char* format_string(const char* format, const char** args, int count) {
    std::string result;
    std::string fmt(format);

    size_t pos = 0;
    int arg_index = 0;

    while ((pos = fmt.find("{}")) != std::string::npos && arg_index < count) {
        result += fmt.substr(0, pos);
        result += args[arg_index++];
        fmt = fmt.substr(pos + 2);
    }

    result += fmt;

    char* output = new char[result.length() + 1];
    strcpy(output, result.c_str());
    return output;
}

// Create formatted string from int
extern "C" char* format_int(int value, const char* format) {
    std::stringstream ss;
    ss << value;
    std::string str = ss.str();
    char* result = new char[str.length() + 1];
    strcpy(result, str.c_str());
    return result;
}

// Create formatted string from float
extern "C" char* format_float(float value, const char* format) {
    std::stringstream ss;
    ss << value;
    std::string str = ss.str();
    char* result = new char[str.length() + 1];
    strcpy(result, str.c_str());
    return result;
}

// Free formatted string
extern "C" void free_formatted_string(char* str) {
    delete[] str;
}

} // namespace runtime
} // namespace pryst
