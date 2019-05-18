#include "Engine/Core/String.hpp"

#include <cctype>

#include "Engine/__Control/__Control.hpp"
#include "Engine/Core/ErrorWarningAssert.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
String::String()
{
	m_stdString = "";
	m_hash = 0;
}


String::String(const std::string& stdString)
{
	m_stdString = stdString;
	m_hash = GenerateHash(m_stdString);
}


String::String(const char* cString)
{
	m_stdString = cString;
	m_hash = GenerateHash(m_stdString);
}



// -----------------------------------------------------------------
// Hash
// -----------------------------------------------------------------
ulonglong String::GetHash() const
{
	return m_hash;
}



// -----------------------------------------------------------------
// Base String
// -----------------------------------------------------------------
const char* String::GetCString() const
{
	return m_stdString.c_str();
}


const std::string& String::GetStdString() const
{
	return m_stdString;
}



// -----------------------------------------------------------------
// Operators
// -----------------------------------------------------------------
bool String::operator<(const String& rhs) const
{
	ulonglong lhsHash = GetHash();
	ulonglong rhsHash = rhs.GetHash();

	if (lhsHash < rhsHash)
	{
		return true;
	}
	else
	{
#ifdef STRING_HASH_SAFETY
	if (lhsHash == rhsHash)
	{
		GUARANTEE_OR_DIE(CompareStringsCaseInsensitive(GetCString(), rhs.GetCString()) == true, "Bad string hash");
	}
#endif
		return false;
	}
}


bool String::operator==(const String& rhs) const
{
	ulonglong lhsHash = GetHash();
	ulonglong rhsHash = rhs.GetHash();

	if (lhsHash == rhsHash)
	{
#ifdef STRING_HASH_SAFETY
		GUARANTEE_OR_DIE(CompareStringsCaseInsensitive(GetCString(), rhs.GetCString()) == true, "Bad string hash");
#endif
		return true;
	}
	else
	{
		return false;
	}
}



// -----------------------------------------------------------------
// Hash Generation
// -----------------------------------------------------------------
ulonglong String::GenerateHash(const std::string& stdString)
{
	ulonglong hash = GenerateHash(stdString.c_str());
	return hash;
}


ulonglong String::GenerateHash(const char* cString)
{
	ulonglong hash = 0;

	const char* nextChar = cString;
	while(*nextChar != 0)
	{
		hash *= 31;
		hash += (ulonglong)ToLower(*nextChar);

		++nextChar;
	}

	return hash;
}



// -----------------------------------------------------------------
// String Utils
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