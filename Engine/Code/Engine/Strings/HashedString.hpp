#pragma once

#include <string>

#include "Engine/Core/Types.hpp"



// This class is a hashed case insensitive string.
// In __Control there is the constant STRING_HASH_SAFETY which adds an additional
//	 comparison for hashes that match. This is useful in a debug setup to help prevent 
//	 collisions but should be turned off in shipping builds.
class HashedString
{
public:
	//Composition
	HashedString();
	HashedString(const std::string& stdString);
	HashedString(const char* cString);

	// Hash
	ulonglong			GetHash() const;

	// Base String
	const char*			GetCString() const;
	const std::string&	GetStdString() const;

	// Operators
	bool operator<(const HashedString& rhs) const;
	bool operator==(const HashedString& rhs) const;



public:
	static ulonglong GenerateHash(const std::string& stdString);
	static ulonglong GenerateHash(const char* cString);



private:
	std::string m_stdString;
	ulonglong	m_hash;
};
