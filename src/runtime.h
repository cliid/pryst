// Built-in functions for the Pryst language runtime
#ifndef PRYST_RUNTIME_H
#define PRYST_RUNTIME_H

extern "C" {
    void print(const char* str);
    size_t length(const void* collection);
    void* keys(const void* map);
    void* values(const void* map);
    bool has(const void* map, const void* key);
    void* get(const void* map, const void* key);
    void set(void* map, const void* key, void* value);
}

#endif // PRYST_RUNTIME_H
