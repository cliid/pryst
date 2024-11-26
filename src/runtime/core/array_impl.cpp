#include "array_impl.hpp"
#include <stdexcept>
#include "llvm/IR/Verifier.h"
#include <cstring>
#include <sstream>

namespace pryst {
namespace core {

ArrayImpl::ArrayImpl(const std::string& elementType)
    : data(nullptr), length_(0), capacity_(0), type(elementType) {
}

ArrayImpl::~ArrayImpl() {
    if (data) {
        free(data);
    }
}

void ArrayImpl::ensureCapacity(size_t needed) {
    if (needed <= capacity_) return;
    size_t newCapacity = capacity_ == 0 ? 1 : capacity_ * 2;
    while (newCapacity < needed) newCapacity *= 2;
    void** newData = (void**)realloc(data, newCapacity * sizeof(void*));
    if (!newData) throw std::bad_alloc();
    data = newData;
    capacity_ = newCapacity;
}

void ArrayImpl::push(void* element) {
    ensureCapacity(length_ + 1);
    ((void**)data)[length_++] = element;
}

void* ArrayImpl::pop() {
    if (length_ == 0) return nullptr;
    return ((void**)data)[--length_];
}

void* ArrayImpl::shift() {
    if (length_ == 0) return nullptr;
    void* first = ((void**)data)[0];
    memmove(data, (void**)data + 1, (length_ - 1) * sizeof(void*));
    length_--;
    return first;
}

void ArrayImpl::unshift(void* element) {
    ensureCapacity(length_ + 1);
    memmove((void**)data + 1, data, length_ * sizeof(void*));
    ((void**)data)[0] = element;
    length_++;
}

int ArrayImpl::indexOf(void* element) const {
    for (size_t i = 0; i < length_; i++) {
        if (((void**)data)[i] == element) return static_cast<int>(i);
    }
    return -1;
}

ArrayImpl* ArrayImpl::slice(size_t start, size_t end) const {
    if (start > length_) start = length_;
    if (end > length_) end = length_;
    if (start > end) end = start;

    ArrayImpl* result = new ArrayImpl(type);
    size_t newLength = end - start;
    if (newLength > 0) {
        result->ensureCapacity(newLength);
        memcpy(result->data, (void**)data + start, newLength * sizeof(void*));
        result->length_ = newLength;
    }
    return result;
}

std::string ArrayImpl::join(const std::string& separator) const {
    std::ostringstream result;
    for (size_t i = 0; i < length_; i++) {
        if (i > 0) result << separator;
        // Assuming elements are strings for now
        result << (const char*)((void**)data)[i];
    }
    return result.str();
}

void ArrayImpl::registerInLLVM(llvm::Module* module, llvm::IRBuilder<>& builder) {
    auto& context = module->getContext();

    // Create array struct type
    std::vector<llvm::Type*> arrayFields;
    arrayFields.push_back(llvm::Type::getInt8PtrTy(context));  // data pointer
    arrayFields.push_back(llvm::Type::getInt64Ty(context));    // length
    arrayFields.push_back(llvm::Type::getInt64Ty(context));    // capacity
    arrayFields.push_back(llvm::Type::getInt8PtrTy(context));  // type string
    auto arrayStructTy = llvm::StructType::create(context, arrayFields, "struct.pryst.core.Array");

    // Register array methods
    // Constructor
    auto ctorTy = llvm::FunctionType::get(
        arrayStructTy->getPointerTo(),
        {llvm::Type::getInt8PtrTy(context)},  // elementType
        false
    );
    auto ctor = llvm::Function::Create(
        ctorTy,
        llvm::Function::ExternalLinkage,
        "pryst_core_Array_new",
        module
    );

    // Length method
    auto lengthTy = llvm::FunctionType::get(
        llvm::Type::getInt64Ty(context),
        {arrayStructTy->getPointerTo()},
        false
    );
    auto lengthFn = llvm::Function::Create(
        lengthTy,
        llvm::Function::ExternalLinkage,
        "pryst_core_Array_length",
        module
    );

    // Push method
    auto pushTy = llvm::FunctionType::get(
        llvm::Type::getVoidTy(context),
        {arrayStructTy->getPointerTo(), llvm::Type::getInt8PtrTy(context)},
        false
    );
    auto pushFn = llvm::Function::Create(
        pushTy,
        llvm::Function::ExternalLinkage,
        "pryst_core_Array_push",
        module
    );

    // Pop method
    auto popTy = llvm::FunctionType::get(
        llvm::Type::getInt8PtrTy(context),
        {arrayStructTy->getPointerTo()},
        false
    );
    auto popFn = llvm::Function::Create(
        popTy,
        llvm::Function::ExternalLinkage,
        "pryst_core_Array_pop",
        module
    );

    // Shift method
    auto shiftTy = llvm::FunctionType::get(
        llvm::Type::getInt8PtrTy(context),
        {arrayStructTy->getPointerTo()},
        false
    );
    auto shiftFn = llvm::Function::Create(
        shiftTy,
        llvm::Function::ExternalLinkage,
        "pryst_core_Array_shift",
        module
    );

    // Unshift method
    auto unshiftTy = llvm::FunctionType::get(
        llvm::Type::getVoidTy(context),
        {arrayStructTy->getPointerTo(), llvm::Type::getInt8PtrTy(context)},
        false
    );
    auto unshiftFn = llvm::Function::Create(
        unshiftTy,
        llvm::Function::ExternalLinkage,
        "pryst_core_Array_unshift",
        module
    );

    // IndexOf method
    auto indexOfTy = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(context),  // Changed to int32 to match int return type
        {arrayStructTy->getPointerTo(), llvm::Type::getInt8PtrTy(context)},
        false
    );
    auto indexOfFn = llvm::Function::Create(
        indexOfTy,
        llvm::Function::ExternalLinkage,
        "pryst_core_Array_indexOf",
        module
    );

    // Slice method
    auto sliceTy = llvm::FunctionType::get(
        arrayStructTy->getPointerTo(),
        {arrayStructTy->getPointerTo(), llvm::Type::getInt64Ty(context), llvm::Type::getInt64Ty(context)},
        false
    );
    auto sliceFn = llvm::Function::Create(
        sliceTy,
        llvm::Function::ExternalLinkage,
        "pryst_core_Array_slice",
        module
    );

    // Join method
    auto joinTy = llvm::FunctionType::get(
        llvm::Type::getInt8PtrTy(context),
        {arrayStructTy->getPointerTo(), llvm::Type::getInt8PtrTy(context)},
        false
    );
    auto joinFn = llvm::Function::Create(
        joinTy,
        llvm::Function::ExternalLinkage,
        "pryst_core_Array_join",
        module
    );

    // Delete method
    auto deleteTy = llvm::FunctionType::get(
        llvm::Type::getVoidTy(context),
        {arrayStructTy->getPointerTo()},
        false
    );
    auto deleteFn = llvm::Function::Create(
        deleteTy,
        llvm::Function::ExternalLinkage,
        "pryst_core_Array_delete",
        module
    );

    // Verify all functions
    for (auto& fn : module->getFunctionList()) {
        if (fn.getName().startswith("pryst_core_Array_")) {
            llvm::verifyFunction(fn);
        }
    }
}

} // namespace core
} // namespace pryst
