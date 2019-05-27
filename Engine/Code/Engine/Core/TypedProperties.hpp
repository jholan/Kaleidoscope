#pragma once

#include <map>
#include <string>
#include <typeinfo>

class HashedString;
class TypedPropertyBase;



class TypedProperties
{
public:
	// Composition
	inline TypedProperties();
	inline TypedProperties(const TypedProperties& other);
	inline ~TypedProperties();

	inline void operator=(const TypedProperties& copyFrom);


	// Existence
	inline bool DoesPropertyExist(const HashedString& key) const;


	// Set value
	template <typename t>
	void Set(const HashedString& key, const t& value);
	inline void Set(const HashedString& key, const char* value); // We want c strings to parse to strings


	// Get Value
	template <typename t>
	t Get(const HashedString& key, const t& defaultValue);
	inline std::string Get(const HashedString& key, const char* defaultValue); // We want c strings to parse to strings



private:
	std::map<HashedString, TypedPropertyBase*> m_properties;
};




#include "Engine/Core/TypedPropertiesInlineImplementation.hpp"