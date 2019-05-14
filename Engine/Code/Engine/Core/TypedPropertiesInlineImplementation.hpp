#include "Engine/Core/TypedProperties.hpp"



// -----------------------------------------------------------------
// TypedProperty Classes
// -----------------------------------------------------------------
class TypedPropertyBase
{
public:
	TypedPropertyBase() {};
	virtual ~TypedPropertyBase() {};

	virtual size_t GetHashCode() const = 0;
};


template <typename t>
class TypedProperty : public TypedPropertyBase
{
public:
	TypedProperty(t value)							: m_value(value), m_hashCode(typeid(t).hash_code()) {};
	virtual size_t GetHashCode() const override		{return m_hashCode;};
	t GetValue() const								{return m_value;};



private:
	t		m_value;
	size_t	m_hashCode;
};



// -----------------------------------------------------------------
// TypedProperties Implementation
// Composition
// -----------------------------------------------------------------
TypedProperties::TypedProperties()
{

}


TypedProperties::~TypedProperties()
{
	for (auto iter = m_properties.begin(); iter != m_properties.end(); ++iter)
	{
		delete iter->second;
	}
	m_properties.clear();
}



// -----------------------------------------------------------------
// Set
// -----------------------------------------------------------------
template <typename t>
void TypedProperties::Set(const std::string& key, const t& value)
{
	auto searchIter = m_properties.find(key);
	if (searchIter != m_properties.end())
	{
		delete searchIter->second;
	}
	TypedProperty<t>* prop = new TypedProperty<t>(value);
	m_properties[key] = (TypedPropertyBase*)prop;
}


void TypedProperties::Set(const std::string& key, const char* value)
{
	Set(key, std::string(value));
}



// -----------------------------------------------------------------
// Get
// -----------------------------------------------------------------
template <typename t>
t TypedProperties::Get(const std::string& key, const t& defaultValue)
{
	// SHORT CIRCUIT
	auto searchIter = m_properties.find(key);
	if (searchIter == m_properties.end())
	{
		return defaultValue;
	}


	size_t tHashCode = typeid(t).hash_code();
	size_t foundHashCode = searchIter->second->GetHashCode();
	if (tHashCode == foundHashCode)
	{
		return ((TypedProperty<t>*)searchIter->second)->GetValue();
	}
	else
	{
		return defaultValue;
	}
}


std::string TypedProperties::Get(const std::string& key, const char* defaultValue)
{
	// SHORT CIRCUIT
	auto searchIter = m_properties.find(key);
	if (searchIter == m_properties.end())
	{
		return defaultValue;
	}


	size_t tHashCode = typeid(std::string).hash_code();
	size_t foundHashCode = searchIter->second->GetHashCode();
	if (tHashCode == foundHashCode)
	{
		return ((TypedProperty<std::string>*)searchIter->second)->GetValue();
	}
	else
	{
		return defaultValue;
	}
}