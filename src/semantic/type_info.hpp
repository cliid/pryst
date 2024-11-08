#pragma once

#include <string>
#include <memory>
#include <llvm/IR/Type.h>

namespace pryst {

enum class TypeKind;

class TypeInfo {
public:
    TypeInfo(const std::string& name, llvm::Type* llvmType)
        : name_(name), llvmType_(llvmType) {}

    virtual ~TypeInfo() = default;

    const std::string& getName() const { return name_; }
    llvm::Type* getLLVMType() const { return llvmType_; }
    virtual TypeKind getKind() const = 0;

    size_t getSize() const {
        if (!llvmType_) return 0;
        return llvmType_->getPrimitiveSizeInBits() / 8;
    }

    virtual std::string toString() const { return name_; }

protected:
    std::string name_;
    llvm::Type* llvmType_;
};

} // namespace pryst
