#pragma once

#include <string>
#include <unordered_map>
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Function.h"

// Function declarations for runtime bindings
extern "C" {
    void* pryst_core_Map_new(const char* keyType, const char* valueType);
    void* pryst_core_Map_get(void* map, const char* key);
    void pryst_core_Map_set(void* map, const char* key, void* value);
    bool pryst_core_Map_has(void* map, const char* key);
    void pryst_core_Map_delete(void* map, const char* key);
    void pryst_core_Map_clear(void* map);
    char** pryst_core_Map_keys(void* map);
    void** pryst_core_Map_values(void* map);
    int pryst_core_Map_size(void* map);
}

namespace pryst {
namespace core {

class MapImpl {
private:
    std::unordered_map<std::string, void*> data;
    std::string keyType;
    std::string valueType;

public:
    MapImpl(const std::string& keyType, const std::string& valueType);
    ~MapImpl();

    // Core map operations
    void set(const std::string& key, void* value);
    void* get(const std::string& key) const;
    bool has(const std::string& key) const;
    void remove(const std::string& key);
    void clear();
    std::vector<std::string> keys() const;
    std::vector<void*> values() const;
    size_t size() const;

    // Type information
    const std::string& getKeyType() const { return keyType; }
    const std::string& getValueType() const { return valueType; }

    // Internal helpers
    void copyValue(void* dest, const void* src) const;
    void deleteValue(void* value) const;

    // Static LLVM registration
    static void registerInLLVM(llvm::Module* module, llvm::IRBuilder<>& builder);
};

} // namespace core
} // namespace pryst
