#include "array_impl.hpp"
#include <cstring>

extern "C" {

void* pryst_core_Array_new(const char* elementType) {
    try {
        return new pryst::core::ArrayImpl(elementType ? elementType : "any");
    } catch (const std::exception& e) {
        return nullptr;
    }
}

size_t pryst_core_Array_length(void* array_ptr) {
    try {
        auto arr = static_cast<pryst::core::ArrayImpl*>(array_ptr);
        return arr->length();
    } catch (const std::exception& e) {
        return 0;
    }
}

void pryst_core_Array_push(void* array_ptr, void* element) {
    try {
        auto arr = static_cast<pryst::core::ArrayImpl*>(array_ptr);
        arr->push(element);
    } catch (const std::exception& e) {
        // Handle error
    }
}

void* pryst_core_Array_pop(void* array_ptr) {
    try {
        auto arr = static_cast<pryst::core::ArrayImpl*>(array_ptr);
        return arr->pop();
    } catch (const std::exception& e) {
        return nullptr;
    }
}

void* pryst_core_Array_shift(void* array_ptr) {
    try {
        auto arr = static_cast<pryst::core::ArrayImpl*>(array_ptr);
        return arr->shift();
    } catch (const std::exception& e) {
        return nullptr;
    }
}

void pryst_core_Array_unshift(void* array_ptr, void* element) {
    try {
        auto arr = static_cast<pryst::core::ArrayImpl*>(array_ptr);
        arr->unshift(element);
    } catch (const std::exception& e) {
        // Handle error
    }
}

int pryst_core_Array_indexOf(void* array_ptr, void* element) {
    try {
        auto arr = static_cast<pryst::core::ArrayImpl*>(array_ptr);
        return arr->indexOf(element);
    } catch (const std::exception& e) {
        return -1;
    }
}

void* pryst_core_Array_slice(void* array_ptr, size_t start, size_t end) {
    try {
        auto arr = static_cast<pryst::core::ArrayImpl*>(array_ptr);
        return arr->slice(start, end);
    } catch (const std::exception& e) {
        return nullptr;
    }
}

char* pryst_core_Array_join(void* array_ptr, const char* delimiter) {
    try {
        auto arr = static_cast<pryst::core::ArrayImpl*>(array_ptr);
        std::string result = arr->join(delimiter ? delimiter : "");
        char* cstr = new char[result.length() + 1];
        std::strcpy(cstr, result.c_str());
        return cstr;
    } catch (const std::exception& e) {
        return nullptr;
    }
}

void pryst_core_Array_delete(void* array_ptr) {
    if (array_ptr) {
        auto arr = static_cast<pryst::core::ArrayImpl*>(array_ptr);
        delete arr;
    }
}

} // extern "C"
