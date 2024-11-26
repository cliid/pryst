#pragma once

#include <string>

extern "C" {
    // Check if an object is an instance of a given type
    bool pryst_runtime_instanceof(void* obj, const char* type_name);

    // Get the runtime type of an object as a string
    const char* pryst_runtime_typeof(void* obj);
}
