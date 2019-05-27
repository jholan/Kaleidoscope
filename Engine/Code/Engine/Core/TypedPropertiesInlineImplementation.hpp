#include "Engine/Core/TypedProperties.hpp"

#include "Engine/Strings/HashedString.hpp"



// -----------------------------------------------------------------
// TypedProperty Classes
// -----------------------------------------------------------------
class TypedPropertyBase
{
public:
	TypedPropertyBase() {};
	virtual ~TypedPropertyBase() {};

	virtual TypedPropertyBase* Clone() const = 0;

	virtual size_t GetHashCode() const = 0;
};


template <typename t>
class TypedProperty : public TypedPropertyBase
{
public:
	TypedProperty(t value)							: m_value(value), m_hashCode(typeid(t).hash_code()) {};
	virtual size_t GetHashCode() const override		{return m_hashCode;};
	t GetValue() const								{return m_value;};
	inline virtual TypedPropertyBase* Clone() const override;


private:
	t		m_value;
	size_t	m_hashCode;
};


template <typename t>
TypedPropertyBase* TypedProperty<t>::Clone() const
{
	TypedProperty<t>* cloned = new TypedProperty<t>(GetValue());
	return (TypedPropertyBase*)cloned;
}



// -----------------------------------------------------------------
// TypedProperties Implementation
// Composition
// -----------------------------------------------------------------
TypedProperties::TypedProperties()
{

}


TypedProperties::TypedProperties(const TypedProperties& other)
{
	for (auto iter = other.m_properties.begin(); iter != other.m_properties.end(); ++iter)
	{
		TypedPropertyBase* property = iter->second;
		m_properties[iter->first] = property->Clone();
	}
}


TypedProperties::~TypedProperties()
{
	for (auto iter = m_properties.begin(); iter != m_properties.end(); ++iter)
	{
		delete iter->second;
	}
	m_properties.clear();
}


void TypedProperties::operator=(const TypedProperties& copyFrom)
{
	for (auto iter = copyFrom.m_properties.begin(); iter != copyFrom.m_properties.end(); ++iter)
	{
		TypedPropertyBase* property = iter->second;
		m_properties[iter->first] = property->Clone();
	}
}



// -----------------------------------------------------------------
// Existence
// -----------------------------------------------------------------
bool TypedProperties::DoesPropertyExist(const HashedString& key) const
{
	bool exists = false;

	auto searchIter = m_properties.find(key);
	if (searchIter != m_properties.end())
	{
		exists = true;
	}
	
	return exists;
}



// -----------------------------------------------------------------
// Set
// -----------------------------------------------------------------
template <typename t>
void TypedProperties::Set(const HashedString& key, const t& value)
{
	auto searchIter = m_properties.find(key);
	if (searchIter != m_properties.end())
	{
		delete searchIter->second;
	}
	TypedProperty<t>* prop = new TypedProperty<t>(value);
	m_properties[key] = (TypedPropertyBase*)prop;
}


void TypedProperties::Set(const HashedString& key, const char* value)
{
	Set(key, std::string(value));
}



// -----------------------------------------------------------------
// Get
// -----------------------------------------------------------------
template <typename t>
t TypedProperties::Get(const HashedString& key, const t& defaultValue)
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


std::string TypedProperties::Get(const HashedString& key, const char* defaultValue)
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