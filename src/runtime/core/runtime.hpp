#ifndef PRYST_RUNTIME_HPP
#define PRYST_RUNTIME_HPP

#include <string>
#include <vector>
#include <unordered_map>

namespace pryst {
    // GC initialization function
    void initialize_gc();

    // Runtime types
    struct String;
    struct Array;
    struct Map;

    // Runtime functions declarations
    size_t String_length(const String* str);
    void Array_grow(Array* arr);
    void Array_set(Array* arr, size_t index, void* value);
    size_t Array_length(const Array* arr);
    void Map_set(Map* map, void* key, void* value);
    bool Map_has(const Map* map, void* key);
    void Map_remove(Map* map, void* key);
    size_t Map_length(const Map* map);
}

#endif // PRYST_RUNTIME_HPP
