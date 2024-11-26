#include "map_impl.hpp"
#include "array_impl.hpp"
#include "string_impl.hpp"
#include <cstring>
#include <vector>

extern "C" {

// Map class bindings
void* pryst_core_Map_new(const char* keyType, const char* valueType);
void pryst_core_Map_set(void* map_ptr, const char* key, void* value);
void* pryst_core_Map_get(void* map_ptr, const char* key);
bool pryst_core_Map_has(void* map_ptr, const char* key);
void pryst_core_Map_delete(void* map_ptr, const char* key);
void pryst_core_Map_clear(void* map_ptr);
char** pryst_core_Map_keys(void* map_ptr);
void** pryst_core_Map_values(void* map_ptr);
int pryst_core_Map_size(void* map_ptr);
void pryst_core_Map_destroy(void* map_ptr);

} // extern "C"
