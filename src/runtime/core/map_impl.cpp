#include "map_impl.hpp"
#include <map>
#include <string>
#include <vector>
#include <cstring>
#include <stdexcept>

namespace pryst {
namespace core {  // Changed from runtime to core

MapImpl::MapImpl(const std::string& kt, const std::string& vt)
    : keyType(kt), valueType(vt) {}

MapImpl::~MapImpl() {
    clear();
}

void MapImpl::set(const std::string& key, void* value) {
    auto it = data.find(key);
    if (it != data.end()) {
        deleteValue(it->second);
    }
    data[key] = value;
}

void* MapImpl::get(const std::string& key) const {
    auto it = data.find(key);
    return it != data.end() ? it->second : nullptr;
}

bool MapImpl::has(const std::string& key) const {
    return data.find(key) != data.end();
}

void MapImpl::remove(const std::string& key) {
    auto it = data.find(key);
    if (it != data.end()) {
        deleteValue(it->second);
        data.erase(it);
    }
}

void MapImpl::clear() {
    for (auto& pair : data) {
        deleteValue(pair.second);
    }
    data.clear();
}

std::vector<std::string> MapImpl::keys() const {
    std::vector<std::string> result;
    result.reserve(data.size());
    for (const auto& pair : data) {
        result.push_back(pair.first);
    }
    return result;
}

std::vector<void*> MapImpl::values() const {
    std::vector<void*> result;
    result.reserve(data.size());
    for (const auto& pair : data) {
        result.push_back(pair.second);
    }
    return result;
}

size_t MapImpl::size() const {
    return data.size();
}

void MapImpl::copyValue(void* dest, const void* src) const {
    if (valueType == "str") {
        const char* srcStr = static_cast<const char*>(src);
        size_t len = strlen(srcStr);
        char* destStr = new char[len + 1];
        strcpy(destStr, srcStr);
        *static_cast<char**>(dest) = destStr;
    } else {
        *static_cast<void**>(dest) = const_cast<void*>(src);
    }
}

void MapImpl::deleteValue(void* value) const {
    if (!value) return;
    if (valueType == "str") {
        delete[] static_cast<char*>(value);
    }
}

void MapImpl::registerInLLVM(llvm::Module* module, llvm::IRBuilder<>& builder) {
    auto& context = module->getContext();
    auto voidTy = llvm::Type::getVoidTy(context);
    auto int8PtrTy = llvm::Type::getInt8PtrTy(context);
    auto int32Ty = llvm::Type::getInt32Ty(context);
    auto int64Ty = llvm::Type::getInt64Ty(context);
    auto boolTy = llvm::Type::getInt1Ty(context);

    // Create Map struct type
    std::vector<llvm::Type*> mapFields;
    mapFields.push_back(int8PtrTy);  // keyType string
    mapFields.push_back(int8PtrTy);  // valueType string
    mapFields.push_back(int8PtrTy);  // internal map pointer
    auto mapStructTy = llvm::StructType::create(context, mapFields, "struct.pryst.core.Map");

    // Register all Map methods with LLVM
    // The actual implementations are provided through extern "C" functions
    std::vector<llvm::Type*> newParams = {int8PtrTy, int8PtrTy};
    auto newFuncTy = llvm::FunctionType::get(mapStructTy->getPointerTo(), newParams, false);
    auto newFunc = llvm::Function::Create(newFuncTy, llvm::Function::ExternalLinkage, "pryst_core_Map_new", module);

    std::vector<llvm::Type*> getParams = {mapStructTy->getPointerTo(), int8PtrTy};
    auto getFuncTy = llvm::FunctionType::get(int8PtrTy, getParams, false);
    auto getFunc = llvm::Function::Create(getFuncTy, llvm::Function::ExternalLinkage, "pryst_core_Map_get", module);

    std::vector<llvm::Type*> setParams = {mapStructTy->getPointerTo(), int8PtrTy, int8PtrTy};
    auto setFuncTy = llvm::FunctionType::get(voidTy, setParams, false);
    auto setFunc = llvm::Function::Create(setFuncTy, llvm::Function::ExternalLinkage, "pryst_core_Map_set", module);

    std::vector<llvm::Type*> hasParams = {mapStructTy->getPointerTo(), int8PtrTy};
    auto hasFuncTy = llvm::FunctionType::get(boolTy, hasParams, false);
    auto hasFunc = llvm::Function::Create(hasFuncTy, llvm::Function::ExternalLinkage, "pryst_core_Map_has", module);

    std::vector<llvm::Type*> deleteParams = {mapStructTy->getPointerTo(), int8PtrTy};
    auto deleteFuncTy = llvm::FunctionType::get(voidTy, deleteParams, false);
    auto deleteFunc = llvm::Function::Create(deleteFuncTy, llvm::Function::ExternalLinkage, "pryst_core_Map_delete", module);

    std::vector<llvm::Type*> clearParams = {mapStructTy->getPointerTo()};
    auto clearFuncTy = llvm::FunctionType::get(voidTy, clearParams, false);
    auto clearFunc = llvm::Function::Create(clearFuncTy, llvm::Function::ExternalLinkage, "pryst_core_Map_clear", module);

    std::vector<llvm::Type*> keysParams = {mapStructTy->getPointerTo()};
    auto keysFuncTy = llvm::FunctionType::get(int8PtrTy->getPointerTo(), keysParams, false);
    auto keysFunc = llvm::Function::Create(keysFuncTy, llvm::Function::ExternalLinkage, "pryst_core_Map_keys", module);

    std::vector<llvm::Type*> valuesParams = {mapStructTy->getPointerTo()};
    auto valuesFuncTy = llvm::FunctionType::get(int8PtrTy->getPointerTo(), valuesParams, false);
    auto valuesFunc = llvm::Function::Create(valuesFuncTy, llvm::Function::ExternalLinkage, "pryst_core_Map_values", module);

    std::vector<llvm::Type*> sizeParams = {mapStructTy->getPointerTo()};
    auto sizeFuncTy = llvm::FunctionType::get(int32Ty, sizeParams, false);
    auto sizeFunc = llvm::Function::Create(sizeFuncTy, llvm::Function::ExternalLinkage, "pryst_core_Map_size", module);
}

} // namespace core

// Runtime binding implementations
extern "C" {

void* pryst_core_Map_new(const char* keyType, const char* valueType) {
    try {
        return new pryst::core::MapImpl(keyType, valueType);
    } catch (const std::exception&) {
        return nullptr;
    }
}

void* pryst_core_Map_get(void* map, const char* key) {
    if (!map || !key) return nullptr;
    auto* mapImpl = static_cast<pryst::core::MapImpl*>(map);
    try {
        return mapImpl->get(key);
    } catch (const std::exception&) {
        return nullptr;
    }
}

void pryst_core_Map_set(void* map, const char* key, void* value) {
    if (!map || !key) return;
    auto* mapImpl = static_cast<pryst::core::MapImpl*>(map);
    try {
        mapImpl->set(key, value);
    } catch (const std::exception&) {
        // Handle error
    }
}

bool pryst_core_Map_has(void* map, const char* key) {
    if (!map || !key) return false;
    auto* mapImpl = static_cast<pryst::core::MapImpl*>(map);
    try {
        return mapImpl->has(key);
    } catch (const std::exception&) {
        return false;
    }
}

void pryst_core_Map_delete(void* map, const char* key) {
    if (!map || !key) return;
    auto* mapImpl = static_cast<pryst::core::MapImpl*>(map);
    try {
        mapImpl->remove(key);
    } catch (const std::exception&) {
        // Handle error
    }
}

void pryst_core_Map_clear(void* map) {
    if (!map) return;
    auto* mapImpl = static_cast<pryst::core::MapImpl*>(map);
    try {
        mapImpl->clear();
    } catch (const std::exception&) {
        // Handle error
    }
}

char** pryst_core_Map_keys(void* map) {
    if (!map) return nullptr;
    auto* mapImpl = static_cast<pryst::core::MapImpl*>(map);
    try {
        std::vector<std::string> keys = mapImpl->keys();
        size_t size = keys.size();
        char** result = static_cast<char**>(malloc((size + 1) * sizeof(char*)));
        if (!result) return nullptr;

        for (size_t i = 0; i < size; ++i) {
            size_t len = keys[i].length();
            result[i] = static_cast<char*>(malloc(len + 1));
            if (!result[i]) {
                for (size_t j = 0; j < i; ++j) {
                    free(result[j]);
                }
                free(result);
                return nullptr;
            }
            strncpy(result[i], keys[i].c_str(), len);
            result[i][len] = '\0';
        }
        result[size] = nullptr;
        return result;
    } catch (const std::exception&) {
        return nullptr;
    }
}

void** pryst_core_Map_values(void* map) {
    if (!map) return nullptr;
    auto* mapImpl = static_cast<pryst::core::MapImpl*>(map);
    try {
        std::vector<void*> values = mapImpl->values();
        size_t size = values.size();
        void** result = static_cast<void**>(malloc((size + 1) * sizeof(void*)));
        if (!result) return nullptr;

        for (size_t i = 0; i < size; ++i) {
            result[i] = values[i];
        }
        result[size] = nullptr;
        return result;
    } catch (const std::exception&) {
        return nullptr;
    }
}

int pryst_core_Map_size(void* map) {
    if (!map) return 0;
    auto* mapImpl = static_cast<pryst::core::MapImpl*>(map);
    try {
        return static_cast<int>(mapImpl->size());
    } catch (const std::exception&) {
        return 0;
    }
}

} // extern "C"
} // namespace pryst
