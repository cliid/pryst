#include "io.hpp"
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>

namespace pryst {
namespace io {

// Implementation moved to header file with inline definitions

} // namespace io
} // namespace pryst

extern "C" {

void pryst_print(const char* message) {
    if (!message) return;
    std::cout << message << std::endl;
}

void* pryst_file_open(const char* filename, const char* mode) {
    if (!filename || !mode) return nullptr;
    try {
        auto* file = new pryst::io::File(filename);
        file->open(mode);
        return file;
    } catch (const pryst::io::FileError& e) {
        std::cerr << "File error: " << e.what() << " (code: " << e.code() << ")" << std::endl;
        return nullptr;
    }
}

char* pryst_file_read_to_string(void* file_handle) {
    if (!file_handle) return nullptr;
    try {
        auto* file = static_cast<pryst::io::File*>(file_handle);
        auto content = file->readToString();
        auto* result = new char[content.length() + 1];
        std::strcpy(result, content.c_str());
        return result;
    } catch (const pryst::io::FileError& e) {
        std::cerr << "File error: " << e.what() << " (code: " << e.code() << ")" << std::endl;
        return nullptr;
    }
}

void pryst_file_write_all(void* file_handle, const char* content) {
    if (!file_handle || !content) return;
    try {
        auto* file = static_cast<pryst::io::File*>(file_handle);
        file->writeAll(content);
    } catch (const pryst::io::FileError& e) {
        std::cerr << "File error: " << e.what() << " (code: " << e.code() << ")" << std::endl;
    }
}

void pryst_file_append(void* file_handle, const char* content) {
    if (!file_handle || !content) return;
    try {
        auto* file = static_cast<pryst::io::File*>(file_handle);
        file->append(content);
    } catch (const pryst::io::FileError& e) {
        std::cerr << "File error: " << e.what() << " (code: " << e.code() << ")" << std::endl;
    }
}

char** pryst_file_read_lines(void* file_handle, size_t* line_count) {
    if (!file_handle || !line_count) {
        if (line_count) *line_count = 0;
        return nullptr;
    }
    try {
        auto* file = static_cast<pryst::io::File*>(file_handle);
        auto lines = file->readLines();
        if (lines.empty()) {
            *line_count = 0;
            return nullptr;
        }
        size_t count = lines.size();
        auto* result = new char*[count];
        for (size_t i = 0; i < count; ++i) {
            result[i] = new char[lines[i].length() + 1];
            std::strcpy(result[i], lines[i].c_str());
        }
        *line_count = count;
        return result;
    } catch (const pryst::io::FileError& e) {
        std::cerr << "File error: " << e.what() << " (code: " << e.code() << ")" << std::endl;
        *line_count = 0;
        return nullptr;
    }
}

void pryst_file_close(void* file_handle) {
    if (!file_handle) return;
    try {
        auto* file = static_cast<pryst::io::File*>(file_handle);
        file->close();
        delete file;
    } catch (const pryst::io::FileError& e) {
        std::cerr << "File error: " << e.what() << " (code: " << e.code() << ")" << std::endl;
    }
}

} // extern "C"
