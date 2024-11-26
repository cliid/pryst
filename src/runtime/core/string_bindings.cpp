#include "string_impl.hpp"
#include <cstring>
#include <vector>

extern "C" {

void* pryst_core_String_new(const char* value) {
    try {
        return new pryst::core::StringImpl(value ? value : "");
    } catch (const std::exception& e) {
        return nullptr;
    }
}

size_t pryst_core_String_length(void* string_ptr) {
    try {
        auto str = static_cast<pryst::core::StringImpl*>(string_ptr);
        return str->length();
    } catch (const std::exception& e) {
        return 0;
    }
}

void* pryst_core_String_substring(void* string_ptr, size_t start, size_t length) {
    try {
        auto str = static_cast<pryst::core::StringImpl*>(string_ptr);
        std::string result = str->substring(start, length);
        return new pryst::core::StringImpl(result);
    } catch (const std::exception& e) {
        return nullptr;
    }
}

int pryst_core_String_indexOf(void* string_ptr, const char* search_str) {
    try {
        auto str = static_cast<pryst::core::StringImpl*>(string_ptr);
        return str->indexOf(search_str ? search_str : "");
    } catch (const std::exception& e) {
        return -1;
    }
}

int pryst_core_String_lastIndexOf(void* string_ptr, const char* search_str) {
    try {
        auto str = static_cast<pryst::core::StringImpl*>(string_ptr);
        return str->lastIndexOf(search_str ? search_str : "");
    } catch (const std::exception& e) {
        return -1;
    }
}

void* pryst_core_String_replace(void* string_ptr, const char* from, const char* to) {
    try {
        auto str = static_cast<pryst::core::StringImpl*>(string_ptr);
        std::string result = str->replace(from ? from : "", to ? to : "");
        return new pryst::core::StringImpl(result);
    } catch (const std::exception& e) {
        return nullptr;
    }
}

void* pryst_core_String_split(void* string_ptr, const char* delimiter) {
    try {
        auto str = static_cast<pryst::core::StringImpl*>(string_ptr);
        std::vector<std::string> parts = str->split(delimiter ? delimiter : "");
        // Convert vector to array and return it
        // Note: This needs to be handled by the Array implementation
        // For now, return nullptr to indicate not implemented
        return nullptr;
    } catch (const std::exception& e) {
        return nullptr;
    }
}

void* pryst_core_String_trim(void* string_ptr) {
    try {
        auto str = static_cast<pryst::core::StringImpl*>(string_ptr);
        std::string result = str->trim();
        return new pryst::core::StringImpl(result);
    } catch (const std::exception& e) {
        return nullptr;
    }
}

char* pryst_core_String_toString(void* string_ptr) {
    try {
        auto str = static_cast<pryst::core::StringImpl*>(string_ptr);
        std::string result = str->toString();
        char* cstr = new char[result.length() + 1];
        std::strcpy(cstr, result.c_str());
        return cstr;
    } catch (const std::exception& e) {
        return nullptr;
    }
}

void pryst_core_String_delete(void* string_ptr) {
    if (string_ptr) {
        auto str = static_cast<pryst::core::StringImpl*>(string_ptr);
        delete str;
    }
}

} // extern "C"
