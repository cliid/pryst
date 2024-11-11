#include <cstdlib>
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>
#include <gc/gc.h>
#include <gc/gc_cpp.h>

namespace {
    struct GCInitializer {
        GCInitializer() {
            GC_INIT();
        }
    } gcInit;
}

namespace pryst {

// Runtime structures
struct String {
    char* data;
    size_t length;
};

struct Array {
    void** data;
    size_t length;
    size_t capacity;
};

struct Map {
    std::unordered_map<void*, void*>* data;
};

extern "C" void* GC_malloc(size_t size) {
    return ::GC_MALLOC(size);
}

extern "C" void* String_alloc(size_t length) {
    auto str = static_cast<String*>(GC_malloc(sizeof(String)));
    str->data = static_cast<char*>(GC_malloc(length + 1));
    str->length = length;
    str->data[length] = '\0';
    return str;
}

extern "C" size_t String_length(void* str) {
    return static_cast<String*>(str)->length;
}

extern "C" void* String_concat(void* str1, void* str2) {
    auto s1 = static_cast<String*>(str1);
    auto s2 = static_cast<String*>(str2);
    auto newLength = s1->length + s2->length;
    auto result = static_cast<String*>(String_alloc(newLength));

    memcpy(result->data, s1->data, s1->length);
    memcpy(result->data + s1->length, s2->data, s2->length);

    return result;
}

// Array operations
extern "C" void* Array_alloc(size_t initialSize) {
    auto arr = static_cast<Array*>(GC_malloc(sizeof(Array)));
    arr->length = initialSize;
    arr->capacity = initialSize > 0 ? initialSize * 2 : 8;
    arr->data = static_cast<void**>(GC_malloc(sizeof(void*) * arr->capacity));
    return arr;
}

extern "C" void Array_grow(void* array, size_t minCapacity) {
    auto arr = static_cast<Array*>(array);
    if (minCapacity <= arr->capacity) return;

    size_t newCapacity = arr->capacity * 2;
    while (newCapacity < minCapacity) newCapacity *= 2;

    auto newData = static_cast<void**>(GC_malloc(sizeof(void*) * newCapacity));
    memcpy(newData, arr->data, sizeof(void*) * arr->length);
    arr->data = newData;
    arr->capacity = newCapacity;
}

extern "C" void* Array_get(void* array, size_t index) {
    auto arr = static_cast<Array*>(array);
    if (index >= arr->length) return nullptr;
    return arr->data[index];
}

extern "C" void Array_set(void* array, size_t index, void* value) {
    auto arr = static_cast<Array*>(array);
    if (index >= arr->length) {
        Array_grow(array, index + 1);
        arr->length = index + 1;
    }
    arr->data[index] = value;
}

extern "C" size_t Array_length(void* array) {
    return static_cast<Array*>(array)->length;
}

// Map operations
extern "C" void* Map_alloc() {
    auto map = static_cast<Map*>(GC_malloc(sizeof(Map)));
    map->data = new std::unordered_map<void*, void*>();
    return map;
}

extern "C" void* Map_get(void* map, void* key) {
    auto m = static_cast<Map*>(map);
    auto it = m->data->find(key);
    return it != m->data->end() ? it->second : nullptr;
}

extern "C" void Map_set(void* map, void* key, void* value) {
    auto m = static_cast<Map*>(map);
    (*m->data)[key] = value;
}

extern "C" bool Map_has(void* map, void* key) {
    auto m = static_cast<Map*>(map);
    return m->data->find(key) != m->data->end();
}

extern "C" void Map_remove(void* map, void* key) {
    auto m = static_cast<Map*>(map);
    m->data->erase(key);
}

extern "C" void* Map_keys(void* map) {
    auto m = static_cast<Map*>(map);
    auto keys = Array_alloc(m->data->size());
    size_t i = 0;
    for (const auto& pair : *m->data) {
        Array_set(keys, i++, pair.first);
    }
    return keys;
}

extern "C" void* Map_values(void* map) {
    auto m = static_cast<Map*>(map);
    auto values = Array_alloc(m->data->size());
    size_t i = 0;
    for (const auto& pair : *m->data) {
        Array_set(values, i++, pair.second);
    }
    return values;
}

extern "C" size_t Map_length(void* map) {
    auto m = static_cast<Map*>(map);
    return m->data->size();
}

} // namespace pryst
