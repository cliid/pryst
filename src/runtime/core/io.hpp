#pragma once

#include <string>
#include <fstream>
#include <memory>
#include <vector>
#include <stdexcept>
#include "../error.hpp"

namespace pryst {
namespace io {

class FileError : public std::runtime_error {
private:
    int code_;

public:
    FileError(const std::string& message, int code = 0)
        : std::runtime_error(message)
        , code_(code) {}

    int code() const { return code_; }
};

class File {
private:
    std::shared_ptr<std::fstream> file_;
    std::string filename_;
    bool isOpen_;

public:
    File(const std::string& filename)
        : filename_(filename)
        , isOpen_(false)
        , file_(nullptr) {}

    void open(const std::string& mode = "r") {
        if (isOpen_) {
            throw FileError("File is already open", 1);
        }

        std::ios_base::openmode openMode = std::ios_base::in;
        if (mode == "w") openMode = std::ios_base::out;
        else if (mode == "a") openMode = std::ios_base::app;
        else if (mode == "r+") openMode = std::ios_base::in | std::ios_base::out;
        else if (mode != "r") throw FileError("Invalid file mode: " + mode, 2);

        file_ = std::make_shared<std::fstream>();
        file_->open(filename_, openMode);

        if (!file_->is_open()) {
            throw FileError("Failed to open file: " + filename_, 3);
        }
        isOpen_ = true;
    }

    std::string readToString() {
        if (!isOpen_) {
            throw FileError("File is not open", 4);
        }

        std::string content;
        std::string line;
        while (std::getline(*file_, line)) {
            content += line + "\n";
        }
        return content;
    }

    void writeAll(const std::string& content) {
        if (!isOpen_) {
            throw FileError("File is not open", 4);
        }

        *file_ << content;
        if (file_->fail()) {
            throw FileError("Failed to write to file: " + filename_, 5);
        }
    }

    void append(const std::string& content) {
        if (!isOpen_) {
            throw FileError("File is not open", 4);
        }

        file_->seekp(0, std::ios::end);
        *file_ << content;
        if (file_->fail()) {
            throw FileError("Failed to append to file: " + filename_, 6);
        }
    }

    std::vector<std::string> readLines() {
        if (!isOpen_) {
            throw FileError("File is not open", 4);
        }

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(*file_, line)) {
            lines.push_back(line);
        }
        return lines;
    }

    void close() {
        if (!isOpen_) {
            throw FileError("File is not open", 4);
        }

        file_->close();
        isOpen_ = false;
    }

    ~File() {
        if (isOpen_) {
            close();
        }
    }

    bool isOpen() const { return isOpen_; }
    const std::string& filename() const { return filename_; }
};

} // namespace io
} // namespace pryst

extern "C" {
    void pryst_print(const char* message);
    void* pryst_file_open(const char* filename, const char* mode);
    char* pryst_file_read_to_string(void* file_handle);
    void pryst_file_write_all(void* file_handle, const char* content);
    void pryst_file_append(void* file_handle, const char* content);
    char** pryst_file_read_lines(void* file_handle, size_t* line_count);
    void pryst_file_close(void* file_handle);
}
