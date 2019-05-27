#pragma once

#include "Engine/Core/TypedProperties.hpp"
#include "Engine/XML/XMLUtils.hpp"



class Blackboard
{
public:
	// Composition
	Blackboard();
	~Blackboard();


	// Parsing
	void PopulateFromXML(const std::string& filepath);
		void ParseElement(const std::string& prefix, const XMLEle* element);


	// Existence
	bool DoesKeyExist(const HashedString& key);


	// Set
	void SetValue(const HashedString& key, const std::string& value);


	// Access
	// Basic Types
	int GetValue(const HashedString& key, int defaultValue);
	float GetValue(const HashedString& key, float defaultValue);
	bool GetValue(const HashedString& key, bool defaultValue);

	// Strings
	std::string GetValue(const HashedString& key, const char* defaultValue);
	std::string GetValue(const HashedString& key, const std::string& defaultValue);



private:
	TypedProperties m_values;
};