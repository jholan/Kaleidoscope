#pragma once

#include <string>



// Formatting
std::string	Stringf(const char* format, ...);
std::string	Stringf(const int maxLength, const char* format, ...);
std::string	Stringf_va(const char* format, va_list variableArgumentList);