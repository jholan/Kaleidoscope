#include "Engine/XML/XMLUtils.hpp"

#include "Engine/__Control/__Control.hpp"

#include "Engine/Core/ErrorWarningAssert.hpp"

#include "Engine/Strings/StringUtils.hpp"



// -----------------------------------------------------------------
// Existence
// -----------------------------------------------------------------
static void VerifyElement(const XMLEle* element)
{
// Seriously DBAD this should never need to be turned on
#ifdef VERIFY_XML_ELEMENTS
	GUARANTEE_OR_DIE(element != nullptr, "Invalid xml element");
#endif
}


bool DoesXMLAttributeExist(const XMLEle* element, const char* attributeName)
{
	VerifyElement(element);


	// Check existence
	bool exists = true;

	const char* value = element->Attribute(attributeName);
	if (value == nullptr)
	{
		exists = false;
	}

	return exists;
}



// -----------------------------------------------------------------
// Parsing
// Basic Types
// -----------------------------------------------------------------
int ParseXmlAttribute(const XMLEle* element, const char* attributeName, int defaultValue)
{
	VerifyElement(element);


	// Get value
	int value = defaultValue;

	const char* valueString = element->Attribute(attributeName);
	if (valueString != nullptr)
	{
		value = StringToInt(valueString);
	}

	return value;
}


char ParseXmlAttribute(const XMLEle* element, const char* attributeName, char defaultValue)
{
	VerifyElement(element);


	// Get value
	char value = defaultValue;

	const char* valueString = element->Attribute(attributeName);
	if (valueString != nullptr)
	{
		value = valueString[0];
	}

	return value;
}


bool ParseXmlAttribute(const XMLEle* element, const char* attributeName, bool defaultValue)
{
	VerifyElement(element);


	// Get value
	bool value = defaultValue;

	const char* valueString = element->Attribute(attributeName);
	if (valueString != nullptr)
	{
		value = StringToBool(valueString);
	}

	return value;
}


float ParseXmlAttribute(const XMLEle* element, const char* attributeName, float defaultValue)
{	
	VerifyElement(element);


	// Get value
	float value = defaultValue;

	const char* valueString = element->Attribute(attributeName);
	if (valueString != nullptr)
	{
		value = StringToFloat(valueString);
	}

	return value;
}



// -----------------------------------------------------------------
// Parsing
// Strings
// -----------------------------------------------------------------
std::string ParseXmlAttribute(const XMLEle* element, const char* attributeName, const std::string& defaultValue)
{
	VerifyElement(element);


	// Get value
	std::string value = defaultValue;

	const char* valueString = element->Attribute(attributeName);
	if (valueString != nullptr)
	{
		value = valueString;
	}

	return value;
}


std::string ParseXmlAttribute(const XMLEle* element, const char* attributeName, const char* defaultValue)
{
	VerifyElement(element);


	// Get value
	std::string value = defaultValue;

	const char* valueString = element->Attribute(attributeName);
	if (valueString != nullptr)
	{
		value = valueString;
	}

	return value;
}
