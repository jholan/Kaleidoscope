#include "Engine/Strings/StringUtils.hpp"

#include <stdarg.h>

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Core/EngineCommon.hpp"

static const int STRINGF_STACK_LOCAL_TEMP_LENGTH = 2048;
static const int WCHAR_MAX_CONVERSION_LENGTH = 2048;



// -----------------------------------------------------------------
// Formatting
// -----------------------------------------------------------------
std::string Stringf( const char* format, ... )
{
	char textLiteral[ STRINGF_STACK_LOCAL_TEMP_LENGTH ];
	va_list variableArgumentList;
	va_start( variableArgumentList, format );
	vsnprintf_s( textLiteral, STRINGF_STACK_LOCAL_TEMP_LENGTH, _TRUNCATE, format, variableArgumentList );	
	va_end( variableArgumentList );
	textLiteral[ STRINGF_STACK_LOCAL_TEMP_LENGTH - 1 ] = '\0'; // In case vsnprintf overran (doesn't auto-terminate)

	return std::string( textLiteral );
}


std::string Stringf( const int maxLength, const char* format, ... )
{
	char textLiteralSmall[ STRINGF_STACK_LOCAL_TEMP_LENGTH ];
	char* textLiteral = textLiteralSmall;
	if( maxLength > STRINGF_STACK_LOCAL_TEMP_LENGTH )
		textLiteral = new char[ maxLength ];

	va_list variableArgumentList;
	va_start( variableArgumentList, format );
	vsnprintf_s( textLiteral, maxLength, _TRUNCATE, format, variableArgumentList );	
	va_end( variableArgumentList );
	textLiteral[ maxLength - 1 ] = '\0'; // In case vsnprintf overran (doesn't auto-terminate)

	std::string returnValue( textLiteral );
	if( maxLength > STRINGF_STACK_LOCAL_TEMP_LENGTH )
		delete[] textLiteral;

	return returnValue;
}


std::string Stringf_va( const char* format, va_list variableArgumentList)
{
	char textLiteral[ STRINGF_STACK_LOCAL_TEMP_LENGTH ];
	vsnprintf_s( textLiteral, STRINGF_STACK_LOCAL_TEMP_LENGTH, _TRUNCATE, format, variableArgumentList );	
	textLiteral[ STRINGF_STACK_LOCAL_TEMP_LENGTH - 1 ] = '\0'; // In case vsnprintf overran (doesn't auto-terminate)

	return std::string( textLiteral );
}



// -----------------------------------------------------------------
// Case
// -----------------------------------------------------------------
std::string TrimWhitespaceFromFront(const std::string& string)
{
	std::string trimmedString = string;

	for (int i = 0; i < (int)string.length(); ++i)
	{
		if (!IsWhitespace(string[i]))
		{
			trimmedString.erase(0, i);
			break;
		}
	}

	return trimmedString;
}


std::string TrimWhitespaceFromBack(const std::string& string)
{
	std::string trimmedString = string;

	int count = 0;
	for (int i = (int)string.length() - 1; i >= 0 ; --i)
	{
		if (!IsWhitespace(string[i]))
		{
			trimmedString.erase(i + 1, count);
			break;
		}

		++count;
	}

	return trimmedString;
}


std::string TrimWhitespaceFromFrontAndBack(const std::string& string)
{
	std::string trimmedString;

	trimmedString = TrimWhitespaceFromFront(string);
	trimmedString = TrimWhitespaceFromBack(trimmedString);

	return trimmedString;
}


std::string RemoveAllWhitespace(const std::string& string)
{
	std::string trimmedString;
	trimmedString.reserve(string.size());

	for (int i = 0; i < (int)string.length(); ++i)
	{
		if (!IsWhitespace(string[i]))
		{
			trimmedString.push_back(string[i]);
		}
	}

	return trimmedString;
}


bool IsWhitespace(char c)
{
	bool isWhitespace = false;

	if (c == ' '  ||
		c == '\t' ||
		c == '\n' ||
		c == '\v' ||
		c == '\f' ||
		c == '\r')
	{
		isWhitespace = true;
	}

	return isWhitespace;
}



// -----------------------------------------------------------------
// Case
// -----------------------------------------------------------------
char ToLower(char c)
{
	char lower = (char)tolower(c);
	return lower;
}


std::string ToLower(const std::string& string)
{
	std::string lowerString;
	lowerString.reserve(string.size());

	for (int i = 0; i < (int)string.size(); ++i)
	{
		lowerString.push_back(ToLower(string[i]));
	}

	return lowerString;
}



// -----------------------------------------------------------------
// X to String
// -----------------------------------------------------------------
std::string ToString(int value)
{
	return std::to_string(value);
}


std::string ToString(uint value)
{
	return std::to_string(value);
}


std::string ToString(ulonglong value)
{
	return std::to_string(value);
}


std::string ToString(float value, uint decimalPlaces)
{
	std::string formattedString = Stringf("%.*f", decimalPlaces, value);
	return formattedString;
}



// -----------------------------------------------------------------
// String to X
// -----------------------------------------------------------------
bool StringToBool(const std::string& string, bool defaultValue)
{
	bool value = defaultValue;

	const char* firstCharacter = FindFirstCharacterInString(string.c_str(), "tTfF");
	if (CompareStringsCaseInsensitive(firstCharacter, "true"))
	{
		value = true;
	}
	else if (CompareStringsCaseInsensitive(firstCharacter, "false"))
	{
		value = false;
	}

	return value;
}


float StringToFloat(const std::string& string, float defaultValue)
{
	try
	{
		return std::stof(string);
	}
	catch (...)
	{
		return defaultValue;
	}
}


int StringToInt(const std::string& string, int defaultValue)
{
	try
	{
		return std::stoi(string);
	}
	catch (...)
	{
		return defaultValue;
	}
}



// -----------------------------------------------------------------
// Comparison
// -----------------------------------------------------------------
bool CompareStringsCaseInsensitive(const std::string& lhs, const std::string& rhs)
{
	return CompareStringsCaseInsensitive(lhs.c_str(), rhs.c_str());
}


bool CompareStringsCaseInsensitive(const char* lhs, const char* rhs)
{
	bool stringsAreTheSame = true;

	const char* string1Iter = lhs;
	const char* string2Iter = rhs;
	while( (*string1Iter != 0) && (*string2Iter != 0) )
	{
		char lowerChar1 = (char)tolower(*string1Iter);
		char lowerChar2 = (char)tolower(*string2Iter);
		if (lowerChar1 != lowerChar2)
		{
			stringsAreTheSame = false;
			break;
		}

		++string1Iter;
		++string2Iter;
	}

	return stringsAreTheSame;
}


bool CompareStrings(const std::string& string1, const std::string& string2)
{
	bool stringsAreTheSame = false;

	if (string1 == string2)
	{
		stringsAreTheSame = true;
	}

	return stringsAreTheSame;
}


bool CompareStrings(const char* string1, const char* string2)
{
	bool stringsAreTheSame = false;

	if (strcmp(string1, string2) == 0)
	{
		stringsAreTheSame = true;
	}

	return stringsAreTheSame;
}



// -----------------------------------------------------------------
// Tokenization
// -----------------------------------------------------------------
std::vector<int> ParseCSVtoInts(const std::string& string)
{
	// Remove all white space and split the string on commas
	std::string dataString = RemoveAllWhitespace(string);
	std::vector<std::string> stringTokens = TokenizeString(dataString, ",");


	// Convert each value to int
	std::vector<int> tokens;

	for (int i = 0; i < (int)stringTokens.size(); ++i)
	{
		int intToken = StringToInt(stringTokens[i]);
		tokens.push_back(intToken);
	}

	return tokens;
}


std::vector<float> ParseCSVtoFloats(const std::string& string)
{
	// Remove all white space and split the string on commas
	std::string dataString = RemoveAllWhitespace(string);
	std::vector<std::string> stringTokens = TokenizeString(dataString, ",");


	// Convert each value to float
	std::vector<float> tokens;

	for (int i = 0; i < (int)stringTokens.size(); ++i)
	{
		float floatToken = StringToFloat(stringTokens[i]);
		tokens.push_back(floatToken);
	}

	return tokens;
}


std::vector<bool> ParseCSVtoBools(const std::string& string)
{
	// Remove all white space and split the string on commas
	std::string dataString = RemoveAllWhitespace(string);
	std::vector<std::string> stringTokens = TokenizeString(dataString, ",");


	// Convert each value to bool
	std::vector<bool> tokens;

	for (int i = 0; i < (int)stringTokens.size(); ++i)
	{
		int boolToken = StringToBool(stringTokens[i]);
		tokens.push_back(boolToken);
	}

	return tokens;
}


std::vector<std::string> TokenizeString(const std::string& string, const std::string& delimiters)
{
	std::vector<std::string> tokens;

	char* editableString = CopyString(string);
	std::vector<char*> rawValueList = TokenizeStringInplace(editableString, delimiters.c_str());
	for (auto listIter = rawValueList.begin(); listIter != rawValueList.end(); ++listIter)
	{
		tokens.push_back(RemoveAllWhitespace(*listIter));
	}
	delete editableString;

	return tokens;
}


std::vector<char*> TokenizeStringInplace(char* editableString, const char* delimiters)
{
	std::vector<char*> lines;
	char* tokContext = nullptr;
	char* line = strtok_s(editableString, delimiters, &tokContext);
	while(line != nullptr)
	{
		lines.push_back(line);
		line = strtok_s(nullptr, delimiters, &tokContext);
	}
	return lines;
}



// -----------------------------------------------------------------
// Search
// -----------------------------------------------------------------
const char* FindFirstCharacterInString(const char* string, const char* charsToFind)
{
	const char* first = strpbrk(string, charsToFind);
	return first;
}



// -----------------------------------------------------------------
// Copy
// -----------------------------------------------------------------
char* CopyString(const std::string& string)
{
	char* editableText = new char[string.length() + 1];
	strcpy_s(editableText, string.length() + 1, string.c_str());
	return editableText;
}



// -----------------------------------------------------------------
// WChar
// -----------------------------------------------------------------
std::string ConvertWideCharStringToString(const wchar_t* wideString, unsigned int length)
{
	GUARANTEE_OR_DIE(length < WCHAR_MAX_CONVERSION_LENGTH, "Wide string is too long to convert");

	// Grr wchar
	size_t i;
	char string[WCHAR_MAX_CONVERSION_LENGTH];
	wcstombs_s(&i, string, WCHAR_MAX_CONVERSION_LENGTH, wideString, WCHAR_MAX_CONVERSION_LENGTH);

	std::string stringstring = string;
	return stringstring;
}
