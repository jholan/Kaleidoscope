#include "Engine/Strings/HashedString.hpp"

#include <cctype>

#include "Engine/__Control/__Control.hpp"
#include "Engine/Core/ErrorWarningAssert.hpp"
#include "Engine/Strings/StringUtils.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
HashedString::HashedString()
{
	m_stdString = "";
	m_hash = 0;
}


HashedString::HashedString(const std::string& stdString)
{
	m_stdString = stdString;
	m_hash = GenerateHash(m_stdString);
}


HashedString::HashedString(const char* cString)
{
	m_stdString = cString;
	m_hash = GenerateHash(m_stdString);
}



// -----------------------------------------------------------------
// Hash
// -----------------------------------------------------------------
ulonglong HashedString::GetHash() const
{
	return m_hash;
}



// -----------------------------------------------------------------
// Base String
// -----------------------------------------------------------------
const char* HashedString::GetCString() const
{
	return m_stdString.c_str();
}


const std::string& HashedString::GetStdString() const
{
	return m_stdString;
}



// -----------------------------------------------------------------
// Operators
// -----------------------------------------------------------------
bool HashedString::operator<(const HashedString& rhs) const
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


bool HashedString::operator==(const HashedString& rhs) const
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
ulonglong HashedString::GenerateHash(const std::string& stdString)
{
	ulonglong hash = GenerateHash(stdString.c_str());
	return hash;
}


ulonglong HashedString::GenerateHash(const char* cString)
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
