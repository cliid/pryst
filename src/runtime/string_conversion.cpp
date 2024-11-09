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

// Convert integer to string
extern "C" char* int_to_string(int value) {
    std::string str = std::to_string(value);
    char* result = new char[str.length() + 1];
    strcpy(result, str.c_str());
    return result;
}

// Convert float to string
extern "C" char* float_to_string(float value) {
    std::string str = std::to_string(value);
    // Remove trailing zeros after decimal point
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    if (str.back() == '.') {
        str.pop_back();
    }
    char* result = new char[str.length() + 1];
    strcpy(result, str.c_str());
    return result;
}

// Create empty string
extern "C" char* create_empty_string() {
    char* result = new char[1];
    result[0] = '\0';
    return result;
}

} // namespace runtime
} // namespace pryst
