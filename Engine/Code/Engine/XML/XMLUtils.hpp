#pragma once

#include <string>

#include "ThirdParty/TinyXML2/tinyxml2.h"
using XMLDoc = tinyxml2::XMLDocument;
using XMLEle = tinyxml2::XMLElement;



// Tiny XML How To
/*
	XML Documents
		.LoadFile(const char* filepath)							-> Parse XML file
		.Clear()												-> Free memory


	XML Elements
	Traversal
		XMLEle* XMLDoc::FirstChildElement(const char* name)		-> Grab first container element
		XMLEle* XMLEle::FirstChildElement(const char* name)		-> Grab first sub element
		XMLEle* XMLEle::NextSiblingElement(const char* name)	-> Grab next element at same level

	Queries(Only for use in functions in this header)
		const char* XMLEle::Attribute(const char* name)			-> Grab value for attribute with name
*/


// Existence
bool		DoesXMLAttributeExist(const XMLEle* element, const char* attributeName);


// Parsing
// Basic Types
int			ParseXmlAttribute(const XMLEle* element, const char* attributeName, int defaultValue);
float		ParseXmlAttribute(const XMLEle* element, const char* attributeName, float defaultValue);
bool		ParseXmlAttribute(const XMLEle* element, const char* attributeName, bool defaultValue);
char		ParseXmlAttribute(const XMLEle* element, const char* attributeName, char defaultValue);

// Strings
std::string ParseXmlAttribute(const XMLEle* element, const char* attributeName, const std::string& defaultValue);
std::string ParseXmlAttribute(const XMLEle* element, const char* attributeName, const char* defaultValue = nullptr);
