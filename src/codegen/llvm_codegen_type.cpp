#include "llvm_codegen.hpp"
#include "../semantic/type_info.hpp"
#include <llvm/IR/DerivedTypes.h>

void LLVMCodegen::addTypeInfo(llvm::Value* value, pryst::TypeInfoPtr typeInfo) {
    if (!typeMetadata || !value || !typeInfo) return;
    typeMetadata->addTypeInfo(value, typeInfo);
}

void LLVMCodegen::addFunctionTypeInfo(llvm::Function* function, pryst::FunctionTypeInfoPtr typeInfo) {
    if (!typeMetadata || !function || !typeInfo) return;
    typeMetadata->addFunctionTypeInfo(function, typeInfo);
}

void LLVMCodegen::addClassTypeInfo(llvm::StructType* structType, pryst::ClassTypeInfoPtr typeInfo) {
    if (!typeMetadata || !structType || !typeInfo) return;
    typeMetadata->addClassTypeInfo(structType, typeInfo);
}

pryst::TypeInfoPtr LLVMCodegen::getTypeInfo(llvm::Value* value) {
    return typeMetadata ? typeMetadata->getTypeInfo(value) : nullptr;
}

pryst::FunctionTypeInfoPtr LLVMCodegen::getFunctionTypeInfo(llvm::Function* function) {
    return typeMetadata ? typeMetadata->getFunctionTypeInfo(function) : nullptr;
}

pryst::ClassTypeInfoPtr LLVMCodegen::getClassTypeInfo(llvm::StructType* structType) {
    return typeMetadata ? typeMetadata->getClassTypeInfo(structType) : nullptr;
}

// Update constructor to initialize typeMetadata
LLVMCodegen::LLVMCodegen() {
    context = std::make_unique<llvm::LLVMContext>();
    module = std::make_unique<llvm::Module>("pryst", *context);
    builder = std::make_unique<llvm::IRBuilder<>>(*context);
    typeMetadata = std::make_unique<pryst::TypeMetadata>(*context, *module);

    // Initialize basic types in the type registry
    auto& registry = pryst::TypeRegistry::getInstance();
    registry.getIntType();
    registry.getFloatType();
    registry.getBoolType();
    registry.getStrType();
}

// Helper method to convert LLVM types to Pryst type info
pryst::TypeInfoPtr LLVMCodegen::getLLVMTypeInfo(llvm::Type* type) {
    if (!type) return nullptr;
    auto& registry = pryst::TypeRegistry::getInstance();

    if (type->isIntegerTy(32)) return registry.getIntType();
    if (type->isDoubleTy()) return registry.getFloatType();
    if (type->isIntegerTy(1)) return registry.getBoolType();
    if (type->isPointerTy() && type->getPointerElementType()->isIntegerTy(8))
        return registry.getStrType();

    if (auto structType = llvm::dyn_cast<llvm::StructType>(type)) {
        return getClassTypeInfo(structType);
    }

    if (auto funcType = llvm::dyn_cast<llvm::FunctionType>(type)) {
        std::vector<pryst::TypeInfoPtr> paramTypes;
        for (unsigned i = 0; i < funcType->getNumParams(); ++i) {
            if (auto paramType = getLLVMTypeInfo(funcType->getParamType(i))) {
                paramTypes.push_back(paramType);
            }
        }
        auto returnTypeInfo = getLLVMTypeInfo(funcType->getReturnType());
        if (returnTypeInfo) {
            return registry.getFunctionType(returnTypeInfo, paramTypes);
        }
    }

    return nullptr;
}

// Update visitor methods to store type information

std::any LLVMCodegen::visitVariableDecl(PrystParser::VariableDeclContext* ctx) {
    auto result = PrystBaseVisitor::visitVariableDecl(ctx);
    if (auto value = std::any_cast<llvm::Value*>(&result)) {
        if (auto typeInfo = getLLVMTypeInfo((*value)->getType())) {
            addTypeInfo(*value, typeInfo);
        }
    }
    return result;
}

std::any LLVMCodegen::visitNamedFunction(PrystParser::NamedFunctionContext* ctx) {
    auto result = PrystBaseVisitor::visitNamedFunction(ctx);
    if (auto func = std::any_cast<llvm::Function*>(&result)) {
        if (auto typeInfo = getLLVMTypeInfo((*func)->getFunctionType())) {
            if (auto funcTypeInfo = std::dynamic_pointer_cast<pryst::FunctionTypeInfo>(typeInfo)) {
                addFunctionTypeInfo(*func, funcTypeInfo);
            }
        }
    }
    return result;
}


std::any LLVMCodegen::visitClassDeclaration(PrystParser::ClassDeclarationContext* ctx) {
    auto result = PrystBaseVisitor::visitClassDeclaration(ctx);
    if (auto structType = std::any_cast<llvm::StructType*>(&result)) {
        std::string className = ctx->IDENTIFIER()->getText();
        auto& registry = pryst::TypeRegistry::getInstance();
        if (auto classType = registry.lookupType(className)) {
            if (auto classTypeInfo = std::dynamic_pointer_cast<pryst::ClassTypeInfo>(classType)) {
                addClassTypeInfo(*structType, classTypeInfo);
            }
        }
    }
    return result;
}

// Update type conversion methods to maintain type information
llvm::Value* LLVMCodegen::convertToDouble(llvm::Value* value) {
    auto result = PrystBaseVisitor::convertToDouble(value);
    if (result) {
        auto& registry = pryst::TypeRegistry::getInstance();
        addTypeInfo(result, registry.getFloatType());
    }
    return result;
}

llvm::Value* LLVMCodegen::convertToInt(llvm::Value* value) {
    auto result = PrystBaseVisitor::convertToInt(value);
    if (result) {
        auto& registry = pryst::TypeRegistry::getInstance();
        addTypeInfo(result, registry.getIntType());
    }
    return result;
}
