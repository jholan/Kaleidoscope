#pragma once

#include <string>

#include "Engine/Core/Types.hpp"



// This class is a hashed case insensitive string.
// In __Control there is the constant STRING_HASH_SAFETY which adds an additional
//	 comparison for hashes that match. This is useful in a debug setup to help prevent 
//	 collisions but should be turned off in shipping builds.
class String
{
public:
	//Composition
	String();
	String(const std::string& stdString);
	String(const char* cString);

	// Hash
	ulonglong			GetHash() const;

	// Base String
	const char*			GetCString() const;
	const std::string&	GetStdString() const;

	// Operators
	bool operator<(const String& rhs) const;
	bool operator==(const String& rhs) const;



public:
	static ulonglong GenerateHash(const std::string& stdString);
	static ulonglong GenerateHash(const char* cString);



private:
	std::string m_stdString;
	ulonglong	m_hash;
};



char		ToLower(char c);
std::string ToLower(const std::string& string);

bool		CompareStringsCaseInsensitive(const std::string& lhs, const std::string& rhs);
bool		CompareStringsCaseInsensitive(const char* lhs, const char* rhs);