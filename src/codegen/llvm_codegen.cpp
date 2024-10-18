#include "llvm_codegen.hpp"
#include "ast/ast.hpp"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <unordered_map>
#include <stdexcept>

LLVMCodegen::LLVMCodegen()
    : context(std::make_unique<llvm::LLVMContext>()),
      module(std::make_unique<llvm::Module>("pryst", *context)),
      builder(std::make_unique<llvm::IRBuilder<>>(*context)),
      lastValue(nullptr) {}

std::unique_ptr<llvm::Module> LLVMCodegen::generateModule(Program& program) {
    program.accept(*this);
    return std::move(module);
}

void LLVMCodegen::visitProgram(Program& node) {
    for (const auto& decl : node.declarations) {
        decl->accept(*this);
    }
}

void LLVMCodegen::visitFunctionDeclaration(FunctionDeclaration& node) {
    std::vector<llvm::Type*> paramTypes;
    for (const auto& param : node.parameters) {
        paramTypes.push_back(getLLVMType(param.type));
    }

    llvm::FunctionType* funcType = llvm::FunctionType::get(getLLVMType(node.returnType), paramTypes, false);
    llvm::Function* func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, node.name, module.get());

    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(*context, "entry", func);
    builder->SetInsertPoint(entryBlock);

    // Add parameters to symbol table
    unsigned idx = 0;
    for (auto& arg : func->args()) {
        arg.setName(node.parameters[idx].name);
        llvm::AllocaInst* alloca = builder->CreateAlloca(arg.getType(), nullptr, arg.getName());
        builder->CreateStore(&arg, alloca);
        namedValues[arg.getName().str()] = alloca;
        idx++;
    }

    node.body->accept(*this);

    // Ensure the function has a return statement
    if (!builder->GetInsertBlock()->getTerminator()) {
        if (func->getReturnType()->isVoidTy()) {
            builder->CreateRetVoid();
        } else {
            builder->CreateRet(llvm::Constant::getNullValue(func->getReturnType()));
        }
    }

    llvm::verifyFunction(*func);
}

void LLVMCodegen::visitVariableDeclaration(VariableDeclaration& node) {
    llvm::AllocaInst* alloca = builder->CreateAlloca(getLLVMType(node.type), nullptr, node.name);
    if (node.initializer) {
        node.initializer->accept(*this);
        builder->CreateStore(lastValue, alloca);
    }
    namedValues[node.name] = alloca;
}

void LLVMCodegen::visitClassDeclaration(ClassDeclaration& node) {
    // Class code generation not implemented
}

void LLVMCodegen::visitBlock(Block& node) {
    for (const auto& stmt : node.statements) {
        stmt->accept(*this);
    }
}

void LLVMCodegen::visitExpressionStatement(ExpressionStatement& node) {
    node.expression->accept(*this);
}

void LLVMCodegen::visitIfStatement(IfStatement& node) {
    node.condition->accept(*this);
    llvm::Value* condValue = lastValue;

    llvm::Function* function = builder->GetInsertBlock()->getParent();

    // Pass 'function' as the parent when creating the blocks
    llvm::BasicBlock* thenBlock = llvm::BasicBlock::Create(*context, "then", function);
    llvm::BasicBlock* elseBlock = llvm::BasicBlock::Create(*context, "else", function);
    llvm::BasicBlock* mergeBlock = llvm::BasicBlock::Create(*context, "ifcont", function);

    builder->CreateCondBr(condValue, thenBlock, elseBlock);

    builder->SetInsertPoint(thenBlock);
    node.thenBranch->accept(*this);
    builder->CreateBr(mergeBlock);

    // No need to push 'elseBlock' into the function's basic block list
    // Since we already specified 'function' as the parent when creating it

    builder->SetInsertPoint(elseBlock);
    if (node.elseBranch) {
        node.elseBranch->accept(*this);
    }
    builder->CreateBr(mergeBlock);

    // No need to push 'mergeBlock' into the function's basic block list

    builder->SetInsertPoint(mergeBlock);
}

void LLVMCodegen::visitWhileStatement(WhileStatement& node) {
    llvm::Function* function = builder->GetInsertBlock()->getParent();

    llvm::BasicBlock* condBlock = llvm::BasicBlock::Create(*context, "cond", function);
    llvm::BasicBlock* bodyBlock = llvm::BasicBlock::Create(*context, "body", function);
    llvm::BasicBlock* afterBlock = llvm::BasicBlock::Create(*context, "after", function);

    builder->CreateBr(condBlock);

    builder->SetInsertPoint(condBlock);
    node.condition->accept(*this);
    llvm::Value* condValue = lastValue;
    builder->CreateCondBr(condValue, bodyBlock, afterBlock);

    builder->SetInsertPoint(bodyBlock);
    node.body->accept(*this);
    builder->CreateBr(condBlock);

    builder->SetInsertPoint(afterBlock);
}

void LLVMCodegen::visitForStatement(ForStatement& node) {
    llvm::Function* function = builder->GetInsertBlock()->getParent();

    // Initialize loop variable
    if (node.initializer) {
        node.initializer->accept(*this);
    }

    llvm::BasicBlock* condBlock = llvm::BasicBlock::Create(*context, "cond", function);
    llvm::BasicBlock* bodyBlock = llvm::BasicBlock::Create(*context, "body", function);
    llvm::BasicBlock* incrementBlock = llvm::BasicBlock::Create(*context, "increment", function);
    llvm::BasicBlock* afterBlock = llvm::BasicBlock::Create(*context, "after", function);

    builder->CreateBr(condBlock);

    builder->SetInsertPoint(condBlock);
    if (node.condition) {
        node.condition->accept(*this);
        llvm::Value* condValue = lastValue;
        builder->CreateCondBr(condValue, bodyBlock, afterBlock);
    } else {
        // Infinite loop
        builder->CreateBr(bodyBlock);
    }

    builder->SetInsertPoint(bodyBlock);
    node.body->accept(*this);
    builder->CreateBr(incrementBlock);

    builder->SetInsertPoint(incrementBlock);
    if (node.increment) {
        node.increment->accept(*this);
    }
    builder->CreateBr(condBlock);

    builder->SetInsertPoint(afterBlock);
}

void LLVMCodegen::visitReturnStatement(ReturnStatement& node) {
    if (node.value) {
        node.value->accept(*this);
        builder->CreateRet(lastValue);
    } else {
        builder->CreateRetVoid();
    }
}

void LLVMCodegen::visitBinaryExpression(BinaryExpression& node) {
    node.left->accept(*this);
    llvm::Value* left = lastValue;
    node.right->accept(*this);
    llvm::Value* right = lastValue;

    if (node.op == "+") {
        lastValue = builder->CreateAdd(left, right, "addtmp");
    } else if (node.op == "-") {
        lastValue = builder->CreateSub(left, right, "subtmp");
    } else if (node.op == "*") {
        lastValue = builder->CreateMul(left, right, "multmp");
    } else if (node.op == "/") {
        lastValue = builder->CreateSDiv(left, right, "divtmp");
    } else if (node.op == "%") {
        lastValue = builder->CreateSRem(left, right, "modtmp");
    } else if (node.op == "==") {
        lastValue = builder->CreateICmpEQ(left, right, "cmptmp");
    } else if (node.op == "!=") {
        lastValue = builder->CreateICmpNE(left, right, "cmptmp");
    } else if (node.op == "<") {
        lastValue = builder->CreateICmpSLT(left, right, "cmptmp");
    } else if (node.op == "<=") {
        lastValue = builder->CreateICmpSLE(left, right, "cmptmp");
    } else if (node.op == ">") {
        lastValue = builder->CreateICmpSGT(left, right, "cmptmp");
    } else if (node.op == ">=") {
        lastValue = builder->CreateICmpSGE(left, right, "cmptmp");
    } else if (node.op == "&&") {
        lastValue = builder->CreateAnd(left, right, "andtmp");
    } else if (node.op == "||") {
        lastValue = builder->CreateOr(left, right, "ortmp");
    } else {
        throw std::runtime_error("Unsupported binary operator: " + node.op);
    }
}

void LLVMCodegen::visitUnaryExpression(UnaryExpression& node) {
    node.operand->accept(*this);
    llvm::Value* operand = lastValue;

    if (node.op == "-") {
        lastValue = builder->CreateNeg(operand, "negtmp");
    } else if (node.op == "!") {
        lastValue = builder->CreateNot(operand, "nottmp");
    } else {
        throw std::runtime_error("Unsupported unary operator: " + node.op);
    }
}

void LLVMCodegen::visitLiteralExpression(LiteralExpression& node) {
    if (node.type == "int") {
        lastValue = llvm::ConstantInt::get(*context, llvm::APInt(32, std::stoi(node.value), true));
    } else if (node.type == "float") {
        lastValue = llvm::ConstantFP::get(*context, llvm::APFloat(std::stof(node.value)));
    } else if (node.type == "bool") {
        lastValue = llvm::ConstantInt::get(*context, llvm::APInt(1, node.value == "true" ? 1 : 0));
    } else if (node.type == "str") {
        lastValue = builder->CreateGlobalString(node.value, "strtmp");
    } else {
        throw std::runtime_error("Unknown literal type: " + node.type);
    }
}

void LLVMCodegen::visitVariableExpression(VariableExpression& node) {
    llvm::Value* variableValue = namedValues[node.name];
    if (!variableValue) {
        throw std::runtime_error("Unknown variable: " + node.name);
    }

    // Safely cast llvm::Value* to llvm::AllocaInst*
    llvm::AllocaInst* variable = llvm::dyn_cast<llvm::AllocaInst>(variableValue);
    if (!variable) {
        throw std::runtime_error("Variable is not an AllocaInst: " + node.name);
    }

    llvm::Type* varType = variable->getAllocatedType();
    lastValue = builder->CreateLoad(varType, variable, node.name);
}


void LLVMCodegen::visitCallExpression(CallExpression& node) {
    llvm::Function* calleeFunc = module->getFunction(node.callee);
    if (!calleeFunc) {
        throw std::runtime_error("Unknown function: " + node.callee);
    }

    if (calleeFunc->arg_size() != node.arguments.size()) {
        throw std::runtime_error("Incorrect number of arguments passed to function: " + node.callee);
    }

    std::vector<llvm::Value*> argsV;
    for (auto& arg : node.arguments) {
        arg->accept(*this);
        argsV.push_back(lastValue);
    }

    lastValue = builder->CreateCall(calleeFunc, argsV, "calltmp");
}

void LLVMCodegen::visitNewExpression(NewExpression& node) {
    // Object creation not implemented
    throw std::runtime_error("NewExpression code generation not implemented");
}

void LLVMCodegen::visitAssignmentExpression(AssignmentExpression& node) {
    node.value->accept(*this);
    llvm::Value* value = lastValue;

    llvm::Value* variable = namedValues[node.name];
    if (!variable) {
        throw std::runtime_error("Unknown variable: " + node.name);
    }

    builder->CreateStore(value, variable);
    lastValue = value;
}

void LLVMCodegen::visitGroupingExpression(GroupingExpression& node) {
    node.expression->accept(*this);
}

void LLVMCodegen::visitParameter(Parameter& node) {
    // Parameters are handled in visitFunctionDeclaration
}

llvm::Type* LLVMCodegen::getLLVMType(const std::string& typeName) {
    if (typeName == "int") {
        return llvm::Type::getInt32Ty(*context);
    } else if (typeName == "float") {
        return llvm::Type::getFloatTy(*context);
    } else if (typeName == "bool") {
        return llvm::Type::getInt1Ty(*context);
    } else if (typeName == "str") {
        return llvm::PointerType::getInt8Ty(*context);
    } else {
        throw std::runtime_error("Unknown type: " + typeName);
    }
}
