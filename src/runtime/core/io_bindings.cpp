#include "io_impl.hpp"
#include <cstring>
#include <iostream>
#include <string>

extern "C" {

// File class bindings
void* pryst_io_File_new(const char* path);
char* pryst_io_File_readToString(void* file_ptr);
void pryst_io_File_writeAll(void* file_ptr, const char* content);
void pryst_io_File_close(void* file_ptr);
void pryst_io_File_delete(void* file_ptr);

// IO Function bindings
void pryst_io_print_impl(const char* message);
void pryst_io_println_impl(const char* message);
char* pryst_io_readLine_impl();
char pryst_io_getChar_impl();

} // extern "C"
