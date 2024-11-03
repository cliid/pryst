#include "llvm_codegen.hpp"
#include <iostream>

// Implementation of reflection API functions
llvm::Value* LLVMCodegen::generateGetType(llvm::Value* value) {
    std::cout << "DEBUG: Generating getType() call" << std::endl;

    // Get the type metadata from the value
    llvm::MDNode* typeMD = getTypeMetadata(value);
    if (!typeMD) {
        std::cerr << "ERROR: No type metadata found for value" << std::endl;
        return nullptr;
    }

    // Create a string constant with the type name
    llvm::MDString* typeNameMD = llvm::cast<llvm::MDString>(typeMD->getOperand(0));
    std::string typeName = typeNameMD->getString().str();

    return builder->CreateGlobalStringPtr(typeName);
}

llvm::Value* LLVMCodegen::generateIsInstance(llvm::Value* value, const std::string& typeName) {
    std::cout << "DEBUG: Generating isInstance() call for type '" << typeName << "'" << std::endl;

    // Get the type metadata from the value
    llvm::MDNode* typeMD = getTypeMetadata(value);
    if (!typeMD) {
        std::cerr << "ERROR: No type metadata found for value" << std::endl;
        return builder->getInt1(false);
    }

    // Get the actual type name from metadata
    llvm::MDString* actualTypeNameMD = llvm::cast<llvm::MDString>(typeMD->getOperand(0));
    std::string actualTypeName = actualTypeNameMD->getString().str();

    // Check if types match exactly
    if (actualTypeName == typeName) {
        return builder->getInt1(true);
    }

    // Check inheritance chain if it's a class type
    if (isClassType(actualTypeName)) {
        ClassInfo classInfo = getClassInfo(actualTypeName);
        while (!classInfo.baseClassName.empty()) {
            if (classInfo.baseClassName == typeName) {
                return builder->getInt1(true);
            }
            classInfo = getClassInfo(classInfo.baseClassName);
        }
    }

    return builder->getInt1(false);
}

llvm::MDNode* LLVMCodegen::getTypeMetadata(llvm::Value* value) {
    if (!value) return nullptr;

    // If the value is an instruction, check for metadata
    if (auto inst = llvm::dyn_cast<llvm::Instruction>(value)) {
        return inst->getMetadata("type");
    }

    // If the value is a global variable, check for metadata
    if (auto global = llvm::dyn_cast<llvm::GlobalVariable>(value)) {
        return global->getMetadata("type");
    }

    return nullptr;
}

void LLVMCodegen::attachTypeMetadata(llvm::Value* value, const std::string& typeName) {
    if (!value) return;

    llvm::LLVMContext& context = module->getContext();
    llvm::MDNode* typeMD = llvm::MDNode::get(context,
        llvm::MDString::get(context, typeName));

    // Attach metadata to instruction or global variable
    if (auto inst = llvm::dyn_cast<llvm::Instruction>(value)) {
        inst->setMetadata("type", typeMD);
    } else if (auto global = llvm::dyn_cast<llvm::GlobalVariable>(value)) {
        global->setMetadata("type", typeMD);
    }
}
