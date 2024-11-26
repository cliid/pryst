#include "error_impl.hpp"
#include <cstring>

extern "C" {

void* pryst_core_Error_new(const char* message, int code) {
    try {
        return new pryst::core::ErrorImpl(message, code);
    } catch (const std::exception& e) {
        return nullptr;
    }
}

char* pryst_core_Error_getMessage(void* error_ptr) {
    try {
        auto error = static_cast<pryst::core::ErrorImpl*>(error_ptr);
        std::string message = error->getMessage();
        char* result = new char[message.length() + 1];
        std::strcpy(result, message.c_str());
        return result;
    } catch (const std::exception& e) {
        return nullptr;
    }
}

int pryst_core_Error_getCode(void* error_ptr) {
    try {
        auto error = static_cast<pryst::core::ErrorImpl*>(error_ptr);
        return error->getCode();
    } catch (const std::exception& e) {
        return -1;
    }
}

char* pryst_core_Error_toString(void* error_ptr) {
    try {
        auto error = static_cast<pryst::core::ErrorImpl*>(error_ptr);
        std::string str = error->toString();
        char* result = new char[str.length() + 1];
        std::strcpy(result, str.c_str());
        return result;
    } catch (const std::exception& e) {
        return nullptr;
    }
}

void pryst_core_Error_delete(void* error_ptr) {
    if (error_ptr) {
        auto error = static_cast<pryst::core::ErrorImpl*>(error_ptr);
        delete error;
    }
}

} // extern "C"
