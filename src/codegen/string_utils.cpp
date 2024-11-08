#include "string_utils.hpp"
#include "llvm_codegen.hpp"
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IntrinsicInst.h>

namespace string_utils {

llvm::Function* declareStrlen(pryst::LLVMCodegen* codegen) {
    auto& llvmTypeRegistry = *codegen->getTypeRegistry();
    auto context = codegen->getContext();
    auto module = codegen->getModule();

    std::vector<llvm::Type*> strlenArgs;
    strlenArgs.push_back(llvmTypeRegistry.getPointerType());

    llvm::FunctionType* strlenType = llvm::FunctionType::get(
        llvm::Type::getInt64Ty(*context),
        strlenArgs,
        false
    );

    auto strlenFunc = llvm::Function::Create(
        strlenType,
        llvm::Function::ExternalLinkage,
        "strlen",
        module
    );

    codegen->registerFunction("strlen", strlenFunc);
    return strlenFunc;
}

llvm::Function* declareStrcpy(pryst::LLVMCodegen* codegen) {
    // strcpy(char* dest, const char* src) -> char*
    auto& llvmTypeRegistry = *codegen->getTypeRegistry();
    auto context = codegen->getContext();
    auto module = codegen->getModule();

    std::vector<llvm::Type*> strcpyArgs;
    strcpyArgs.push_back(llvmTypeRegistry.getPointerType());  // dest
    strcpyArgs.push_back(llvmTypeRegistry.getPointerType());  // src

    llvm::FunctionType* strcpyType = llvm::FunctionType::get(
        llvmTypeRegistry.getPointerType(),  // Return type: char*
        strcpyArgs,
        false
    );

    auto strcpyFunc = llvm::Function::Create(
        strcpyType,
        llvm::Function::ExternalLinkage,
        "strcpy",
        module
    );

    codegen->registerFunction("strcpy", strcpyFunc);
    return strcpyFunc;
}

llvm::Function* declareStrcat(pryst::LLVMCodegen* codegen) {
    auto& llvmTypeRegistry = *codegen->getTypeRegistry();
    auto context = codegen->getContext();
    auto module = codegen->getModule();

    std::vector<llvm::Type*> strcatArgs;
    strcatArgs.push_back(llvmTypeRegistry.getPointerType());  // dest
    strcatArgs.push_back(llvmTypeRegistry.getPointerType());  // src

    llvm::FunctionType* strcatType = llvm::FunctionType::get(
        llvmTypeRegistry.getPointerType(),  // Return type: char*
        strcatArgs,
        false
    );

    auto strcatFunc = llvm::Function::Create(
        strcatType,
        llvm::Function::ExternalLinkage,
        "strcat",
        module
    );

    codegen->registerFunction("strcat", strcatFunc);
    return strcatFunc;
}

llvm::Function* declareMemcpy(pryst::LLVMCodegen* codegen) {
    // memcpy(void* dest, const void* src, size_t n) -> void*
    auto& llvmTypeRegistry = *codegen->getTypeRegistry();
    auto context = codegen->getContext();
    auto module = codegen->getModule();

    std::vector<llvm::Type*> memcpyArgs;
    memcpyArgs.push_back(llvmTypeRegistry.getPointerType());  // dest
    memcpyArgs.push_back(llvmTypeRegistry.getPointerType());  // src
    memcpyArgs.push_back(llvm::Type::getInt64Ty(*context));                // size
    memcpyArgs.push_back(llvm::Type::getInt1Ty(*context));                // isVolatile

    llvm::FunctionType* memcpyType = llvm::FunctionType::get(
        llvm::Type::getVoidTy(*context),
        memcpyArgs,
        false
    );

    auto memcpyFunc = llvm::Function::Create(
        memcpyType,
        llvm::Function::ExternalLinkage,
        "llvm.memcpy.p0.p0.i64",
        module
    );

    memcpyFunc->addFnAttr(llvm::Attribute::WillReturn);
    memcpyFunc->addFnAttr(llvm::Attribute::NoUnwind);

    // Clear all parameter attributes
    for (auto& arg : memcpyFunc->args()) {
        arg.removeAttr(llvm::Attribute::NoAlias);
        arg.removeAttr(llvm::Attribute::NoCapture);
        arg.removeAttr(llvm::Attribute::ReadOnly);
        arg.removeAttr(llvm::Attribute::WriteOnly);
    }

    // Set parameter attributes explicitly to none
    llvm::AttributeList emptyAttrs;
    memcpyFunc->setAttributes(emptyAttrs);

    codegen->registerFunction("memcpy", memcpyFunc);
    return memcpyFunc;
}

FormatSpec parseFormatSpec(const std::string& spec) {
    FormatSpec result = {0, -1, ' ', '\0', false};  // Default values
    if (spec.empty()) return result;

    size_t pos = 0;
    // Check for alignment
    if (spec[pos] == '<') {
        result.leftAlign = true;
        pos++;
    }

    // Parse fill character and width
    if (pos < spec.length() && std::isdigit(spec[pos])) {
        if (spec[pos] == '0') {
            result.fill = '0';
            pos++;
        }
        std::string widthStr;
        while (pos < spec.length() && std::isdigit(spec[pos])) {
            widthStr += spec[pos++];
        }
        result.width = std::stoi(widthStr);
    }

    // Parse precision
    if (pos < spec.length() && spec[pos] == '.') {
        pos++;
        std::string precStr;
        while (pos < spec.length() && std::isdigit(spec[pos])) {
            precStr += spec[pos++];
        }
        result.precision = std::stoi(precStr);
    }

    // Parse type
    if (pos < spec.length()) {
        result.type = spec[pos];
    }

    return result;
}

llvm::Value* interpolateString(pryst::LLVMCodegen* codegen, const std::string& format,
                             const std::vector<llvm::Value*>& values,
                             const std::vector<FormatSpec>& specs) {
    auto& llvmTypeRegistry = *codegen->getTypeRegistry();
    auto context = codegen->getContext();
    auto builder = codegen->getBuilder();

    // Create a buffer for the result
    auto bufferSize = format.length() * 2;  // Estimate initial size
    auto buffer = builder->CreateAlloca(
        llvm::ArrayType::get(llvm::Type::getInt8Ty(*context), bufferSize),
        nullptr,
        "interpolated_str"
    );

    // Initialize buffer with format string
    auto formatStr = builder->CreateGlobalString(format);
    auto strcpyFunc = declareStrcpy(codegen);
    builder->CreateCall(strcpyFunc, {buffer, formatStr});

    // Process each value
    for (size_t i = 0; i < values.size(); i++) {
        auto value = values[i];
        auto& spec = specs[i];

        // Format the value based on its type and spec
        llvm::Value* formattedValue = nullptr;
        if (value->getType()->isFloatingPointTy()) {
            auto formatFloatFunc = declareFormatFloat(codegen);
            formattedValue = builder->CreateCall(formatFloatFunc, {
                value,
                llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), spec.precision),
                llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), spec.width),
                llvm::ConstantInt::get(llvm::Type::getInt8Ty(*context), spec.fill),
                llvm::ConstantInt::get(llvm::Type::getInt1Ty(*context), spec.leftAlign)
            });
        } else if (value->getType()->isIntegerTy()) {
            auto formatIntFunc = declareFormatInt(codegen);
            formattedValue = builder->CreateCall(formatIntFunc, {
                value,
                llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), spec.width),
                llvm::ConstantInt::get(llvm::Type::getInt8Ty(*context), spec.fill),
                llvm::ConstantInt::get(llvm::Type::getInt1Ty(*context), spec.leftAlign)
            });
        } else if (value->getType()->isIntegerTy(1)) {  // Boolean
            auto formatBoolFunc = declareFormatBool(codegen);
            formattedValue = builder->CreateCall(formatBoolFunc, {value});
        }

        // Replace placeholder with formatted value
        auto strcatFunc = declareStrcat(codegen);
        builder->CreateCall(strcatFunc, {buffer, formattedValue});
    }

    return buffer;
}

llvm::Function* declareFormatInt(pryst::LLVMCodegen* codegen) {
    auto& llvmTypeRegistry = *codegen->getTypeRegistry();
    auto context = codegen->getContext();
    auto module = codegen->getModule();

    std::vector<llvm::Type*> args;
    args.push_back(llvm::Type::getInt64Ty(*context));  // int value
    args.push_back(llvm::Type::getInt32Ty(*context));  // width
    args.push_back(llvm::Type::getInt8Ty(*context));   // fill char
    args.push_back(llvm::Type::getInt1Ty(*context));   // left align

    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvmTypeRegistry.getPointerType(),  // Return type: char*
        args,
        false
    );

    auto func = llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
        "pryst_format_int",
        module
    );

    codegen->registerFunction("pryst_format_int", func);
    return func;
}

llvm::Function* declareFormatBool(pryst::LLVMCodegen* codegen) {
    auto& llvmTypeRegistry = *codegen->getTypeRegistry();
    auto context = codegen->getContext();
    auto module = codegen->getModule();

    std::vector<llvm::Type*> args;
    args.push_back(llvm::Type::getInt1Ty(*context));  // bool value

    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvmTypeRegistry.getPointerType(),  // Return type: char*
        args,
        false
    );

    auto func = llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
        "pryst_format_bool",
        module
    );

    codegen->registerFunction("pryst_format_bool", func);
    return func;
}

llvm::Function* declareFormatFloat(pryst::LLVMCodegen* codegen) {
    auto& llvmTypeRegistry = *codegen->getTypeRegistry();
    auto context = codegen->getContext();
    auto module = codegen->getModule();

    std::vector<llvm::Type*> args;
    args.push_back(llvm::Type::getDoubleTy(*context));  // float value
    args.push_back(llvm::Type::getInt32Ty(*context));   // precision
    args.push_back(llvm::Type::getInt32Ty(*context));   // width
    args.push_back(llvm::Type::getInt8Ty(*context));    // fill char
    args.push_back(llvm::Type::getInt1Ty(*context));    // left align

    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvmTypeRegistry.getPointerType(),  // Return type: char*
        args,
        false
    );

    auto func = llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage,
        "pryst_format_float",
        module
    );

    codegen->registerFunction("pryst_format_float", func);
    return func;
}

} // namespace string_utils
