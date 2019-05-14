#pragma once

#include <map>
#include <string>
#include <typeinfo>

class TypedPropertyBase;



class TypedProperties
{
public:
	TypedProperties();
	inline ~TypedProperties();

	template <typename t>
	void Set(const std::string& key, const t& value);
	inline void Set(const std::string& key, const char* value);

	template <typename t>
	t Get(const std::string& key, const t& defaultValue);
	inline std::string Get(const std::string& key, const char* defaultValue);



private:
	std::map<std::string, TypedPropertyBase*> m_properties;
};




#include "Engine/Core/TypedPropertiesInlineImplementation.hpp"