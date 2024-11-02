#include "type_metadata.hpp"
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <vector>

namespace pryst {

void TypeMetadata::addTypeInfo(llvm::Value* value, TypeInfoPtr typeInfo) {
    if (!value) return;

    auto* node = createTypeMetadata(typeInfo);
    if (!node) return;

    // If it's an instruction, add metadata to the instruction
    if (auto* inst = llvm::dyn_cast<llvm::Instruction>(value)) {
        inst->setMetadata("pryst.type", node);
    }
    // If it's a global variable, add metadata to the global variable
    else if (auto* global = llvm::dyn_cast<llvm::GlobalVariable>(value)) {
        global->setMetadata("pryst.type", node);
    }
}

void TypeMetadata::addFunctionTypeInfo(llvm::Function* function, FunctionTypeInfoPtr typeInfo) {
    if (!function || !typeInfo) return;

    auto* node = createFunctionTypeMetadata(typeInfo);
    if (node) {
        function->setMetadata("pryst.function.type", node);
    }
}

void TypeMetadata::addClassTypeInfo(llvm::StructType* structType, ClassTypeInfoPtr typeInfo) {
    if (!structType || !typeInfo) return;

    // Store class type info in module-level named metadata
    auto* node = createClassTypeMetadata(typeInfo);
    if (!node) return;

    std::string metadataName = "pryst.class." + typeInfo->getName();
    auto* namedMD = module_.getOrInsertNamedMetadata(metadataName);
    namedMD->addOperand(node);
}

llvm::MDNode* TypeMetadata::createTypeMetadata(TypeInfoPtr typeInfo) {
    if (!typeInfo) return nullptr;

    std::vector<llvm::Metadata*> ops;

    // Add type kind
    ops.push_back(getMDString(std::to_string(static_cast<int>(typeInfo->getKind()))));

    // Add type name
    ops.push_back(getMDString(typeInfo->getName()));

    return llvm::MDNode::get(context_, ops);
}

llvm::MDNode* TypeMetadata::createFunctionTypeMetadata(FunctionTypeInfoPtr typeInfo) {
    if (!typeInfo) return nullptr;

    std::vector<llvm::Metadata*> ops;

    // Add return type info
    ops.push_back(createTypeMetadata(typeInfo->getReturnType()));

    // Add parameter type info
    for (const auto& paramType : typeInfo->getParamTypes()) {
        ops.push_back(createTypeMetadata(paramType));
    }

    return llvm::MDNode::get(context_, ops);
}

llvm::MDNode* TypeMetadata::createClassTypeMetadata(ClassTypeInfoPtr typeInfo) {
    if (!typeInfo) return nullptr;

    std::vector<llvm::Metadata*> ops;

    // Add class name
    ops.push_back(getMDString(typeInfo->getName()));

    // Add method information
    std::vector<llvm::Metadata*> methodOps;
    for (const auto& method : typeInfo->getMethods()) {
        std::vector<llvm::Metadata*> methodInfo;
        methodInfo.push_back(getMDString(method.first)); // Method name
        methodInfo.push_back(createFunctionTypeMetadata(method.second)); // Method type
        methodOps.push_back(llvm::MDNode::get(context_, methodInfo));
    }
    ops.push_back(llvm::MDNode::get(context_, methodOps));

    // Add field information
    std::vector<llvm::Metadata*> fieldOps;
    for (const auto& field : typeInfo->getFields()) {
        std::vector<llvm::Metadata*> fieldInfo;
        fieldInfo.push_back(getMDString(field.first)); // Field name
        fieldInfo.push_back(createTypeMetadata(field.second)); // Field type
        fieldOps.push_back(llvm::MDNode::get(context_, fieldInfo));
    }
    ops.push_back(llvm::MDNode::get(context_, fieldOps));

    return llvm::MDNode::get(context_, ops);
}

TypeInfoPtr TypeMetadata::getTypeInfo(llvm::Value* value) {
    if (!value) return nullptr;

    llvm::MDNode* node = nullptr;

    // Get metadata based on value type
    if (auto* inst = llvm::dyn_cast<llvm::Instruction>(value)) {
        node = inst->getMetadata("pryst.type");
    }
    else if (auto* global = llvm::dyn_cast<llvm::GlobalVariable>(value)) {
        node = global->getMetadata("pryst.type");
    }

    return node ? parseTypeMetadata(node) : nullptr;
}

FunctionTypeInfoPtr TypeMetadata::getFunctionTypeInfo(llvm::Function* function) {
    if (!function) return nullptr;


    auto* node = function->getMetadata("pryst.function.type");
    return node ? parseFunctionTypeMetadata(node) : nullptr;
}

ClassTypeInfoPtr TypeMetadata::getClassTypeInfo(llvm::StructType* structType) {
    if (!structType || !structType->hasName()) return nullptr;

    std::string metadataName = "pryst.class." + structType->getName().str();
    auto* namedMD = module_.getNamedMetadata(metadataName);
    if (!namedMD || namedMD->getNumOperands() == 0) return nullptr;

    return parseClassTypeMetadata(namedMD->getOperand(0));
}

TypeInfoPtr TypeMetadata::parseTypeMetadata(llvm::MDNode* node) {
    if (!node || node->getNumOperands() < 2) return nullptr;

    auto* kindMD = llvm::dyn_cast<llvm::MDString>(node->getOperand(0));
    auto* nameMD = llvm::dyn_cast<llvm::MDString>(node->getOperand(1));
    if (!kindMD || !nameMD) return nullptr;

    int kind = std::stoi(getMDStringValue(kindMD));
    std::string name = getMDStringValue(nameMD);

    switch (static_cast<TypeInfo::Kind>(kind)) {
        case TypeInfo::Kind::Basic:
            return std::make_shared<BasicTypeInfo>(name);
        case TypeInfo::Kind::Function:
            // Function types are handled by parseFunctionTypeMetadata
            return nullptr;
        case TypeInfo::Kind::Class:
            // Class types are handled by parseClassTypeMetadata
            return nullptr;
        default:
            return nullptr;
    }
}

FunctionTypeInfoPtr TypeMetadata::parseFunctionTypeMetadata(llvm::MDNode* node) {
    if (!node || node->getNumOperands() < 1) return nullptr;

    // Parse return type
    auto returnType = parseTypeMetadata(llvm::dyn_cast<llvm::MDNode>(node->getOperand(0)));
    if (!returnType) return nullptr;

    // Parse parameter types
    std::vector<TypeInfoPtr> paramTypes;
    for (unsigned i = 1; i < node->getNumOperands(); ++i) {
        if (auto paramType = parseTypeMetadata(llvm::dyn_cast<llvm::MDNode>(node->getOperand(i)))) {
            paramTypes.push_back(paramType);
        }
    }

    return std::make_shared<FunctionTypeInfo>(returnType, paramTypes);
}

ClassTypeInfoPtr TypeMetadata::parseClassTypeMetadata(llvm::MDNode* node) {
    if (!node || node->getNumOperands() < 3) return nullptr;

    // Get class name
    auto* nameMD = llvm::dyn_cast<llvm::MDString>(node->getOperand(0));
    if (!nameMD) return nullptr;
    std::string className = getMDStringValue(nameMD);

    // Create class type
    auto classType = std::make_shared<ClassTypeInfo>(className);

    // Parse methods
    auto* methodsNode = llvm::dyn_cast<llvm::MDNode>(node->getOperand(1));
    if (methodsNode) {
        for (unsigned i = 0; i < methodsNode->getNumOperands(); ++i) {
            auto* methodNode = llvm::dyn_cast<llvm::MDNode>(methodsNode->getOperand(i));
            if (!methodNode || methodNode->getNumOperands() < 2) continue;

            auto* methodNameMD = llvm::dyn_cast<llvm::MDString>(methodNode->getOperand(0));
            auto* methodTypeNode = llvm::dyn_cast<llvm::MDNode>(methodNode->getOperand(1));
            if (!methodNameMD || !methodTypeNode) continue;

            std::string methodName = getMDStringValue(methodNameMD);
            if (auto methodType = parseFunctionTypeMetadata(methodTypeNode)) {
                classType->addMethod(methodName, methodType);
            }
        }
    }

    // Parse fields
    auto* fieldsNode = llvm::dyn_cast<llvm::MDNode>(node->getOperand(2));
    if (fieldsNode) {
        for (unsigned i = 0; i < fieldsNode->getNumOperands(); ++i) {
            auto* fieldNode = llvm::dyn_cast<llvm::MDNode>(fieldsNode->getOperand(i));
            if (!fieldNode || fieldNode->getNumOperands() < 2) continue;

            auto* fieldNameMD = llvm::dyn_cast<llvm::MDString>(fieldNode->getOperand(0));
            auto* fieldTypeNode = llvm::dyn_cast<llvm::MDNode>(fieldNode->getOperand(1));
            if (!fieldNameMD || !fieldTypeNode) continue;

            std::string fieldName = getMDStringValue(fieldNameMD);
            if (auto fieldType = parseTypeMetadata(fieldTypeNode)) {
                classType->addField(fieldName, fieldType);
            }
        }
    }

    return classType;
}

} // namespace pryst
