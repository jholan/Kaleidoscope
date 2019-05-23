#pragma once

#include <string>
#include <vector>

#include "Engine/Core/Types.hpp"



// Formatting
std::string					Stringf(const char* format, ...);
std::string					Stringf(const int maxLength, const char* format, ...);
std::string					Stringf_va(const char* format, va_list variableArgumentList);


// Whitespace
std::string					TrimWhitespaceFromFront(const std::string& string);
std::string					TrimWhitespaceFromBack(const std::string& string);
std::string					TrimWhitespaceFromFrontAndBack(const std::string& string);
std::string					RemoveAllWhitespace(const std::string& string);
bool						IsWhitespace(char c);


// Case
char						ToLower(char c);
std::string					ToLower(const std::string& string);


// X To String
std::string					ToString(int value);
std::string					ToString(uint value);
std::string					ToString(ulonglong value);
std::string					ToString(float value, uint decimalPlaces);


// String to X
bool						StringToBool(const std::string& string);
float						StringToFloat(const std::string& string, float defaultValue = 0.0f);
int							StringToInt(const std::string& string, int defaultValue = 0);


// Comparison
bool						CompareStringsCaseInsensitive(const std::string& lhs, const std::string& rhs);
bool						CompareStringsCaseInsensitive(const char* lhs, const char* rhs);
bool						CompareStrings(const std::string& string1, const std::string& string2);
bool						CompareStrings(const char* string1, const char* string2);


// Tokenization
std::vector<int>			ParseCSVtoInts(const std::string& string);
std::vector<float>			ParseCSVtoFloats(const std::string& string);
std::vector<bool>			ParseCSVtoBools(const std::string& string);
std::vector<std::string>	TokenizeString(const std::string& string, const std::string& delimiters);
std::vector<char*>			TokenizeStringInplace(char* editableString, const char* delimiters);


// Search
const char*					FindFirstCharacterInString(const char* string, const char* charsToFind);


// Copy	
char*						CopyString(const std::string& string);