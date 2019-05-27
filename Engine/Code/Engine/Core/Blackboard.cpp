#include "Engine/Core/Blackboard.hpp"

#include "Engine/XML/XMLUtils.hpp"
#include "Engine/Strings/StringUtils.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
Blackboard::Blackboard()
{

}


Blackboard::~Blackboard()
{

}



// -----------------------------------------------------------------
// Parsing
// -----------------------------------------------------------------
void Blackboard::PopulateFromXML(const std::string& filepath)
{
	// Load the XML file
	XMLDoc doc;
	doc.LoadFile(filepath.c_str());


	// Grab the outer element
	const XMLEle* configEle = doc.FirstChildElement();
	while(configEle != nullptr)
	{
		ParseElement("", configEle);

		configEle = configEle->NextSiblingElement();
	}


	// Clean up
	doc.Clear();
}


void Blackboard::ParseElement(const std::string& prevPrefix, const XMLEle* element)
{
	// Get the new prefix
	std::string prefix = prevPrefix + element->Name() + ".";


	// Parse all attributes and add them to the blackboard
	const XMLAttr* attr = element->FirstAttribute();
	while (attr != nullptr)
	{
		// Add the value to the blackboard
		if (CompareStringsCaseInsensitive(attr->Name(), "value"))
		{
			// If the attribute is in the format <EleName value="" /> we want want to access it as EleName
			m_values.Set(prevPrefix + element->Name(), attr->Value());
		}
		else
		{
			m_values.Set(prefix + attr->Name(), attr->Value());
		}
	
		// Grab next attribute
		attr = attr->Next();
	}


	// Parse children elements
	const XMLEle* childEle = element->FirstChildElement();
	while(childEle != nullptr)
	{
		// Parse the element
		ParseElement(prefix, childEle);
	
		// Grab next element
		childEle = childEle->NextSiblingElement();
	}
}



// -----------------------------------------------------------------
// Existence
// -----------------------------------------------------------------
bool Blackboard::DoesKeyExist(const HashedString& key)
{
	bool exists = m_values.DoesPropertyExist(key);
	return exists;
}



// -----------------------------------------------------------------
// Set
// -----------------------------------------------------------------
void Blackboard::SetValue(const HashedString& key, const std::string& value)
{
	m_values.Set(key, value);
}



// -----------------------------------------------------------------
// Access
// Basic Types
// -----------------------------------------------------------------
int Blackboard::GetValue(const HashedString& key, int defaultValue)
{
	std::string valueString = m_values.Get(key, "");
	int value = StringToInt(valueString, defaultValue);
	return value;
}


float Blackboard::GetValue(const HashedString& key, float defaultValue)
{
	std::string valueString = m_values.Get(key, "");
	float value = StringToFloat(valueString, defaultValue);
	return value;
}


bool Blackboard::GetValue(const HashedString& key, bool defaultValue)
{
	std::string valueString = m_values.Get(key, "");
	bool value = StringToBool(valueString, defaultValue);
	return value;
}



// -----------------------------------------------------------------
// Access
// Strings
// -----------------------------------------------------------------
std::string Blackboard::GetValue(const HashedString& key, const char* defaultValue)
{
	std::string value = m_values.Get(key, defaultValue);
	return value;
}


std::string Blackboard::GetValue(const HashedString& key, const std::string& defaultValue)
{
	std::string value = m_values.Get(key, defaultValue);
	return value;
}
