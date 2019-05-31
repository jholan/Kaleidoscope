#include "Engine/Rendering/LowLevel/VertexAttribute.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
VertexAttribute::VertexAttribute()
{

}


VertexAttribute::VertexAttribute(const std::string name, eVertexAttributeDataType type, int elementCount, bool normalize, size_t offset)
{
	m_name = name;
	m_type = type;
	m_elementCount = elementCount;
	m_isNormalized = normalize;
	m_memberOffsetBytes = (int)offset;
}


VertexAttribute::~VertexAttribute()
{

}



// -----------------------------------------------------------------
// Comparison
// -----------------------------------------------------------------
bool operator==(const VertexAttribute& lhs, const VertexAttribute& rhs)
{
	bool areEqual = true;

	if (lhs.GetName() != rhs.GetName())
	{
		areEqual = false;
	}
	else if (lhs.GetDataType() != rhs.GetDataType())
	{
		areEqual = false;
	}
	else if (lhs.GetDataElementCount() != rhs.GetDataElementCount())
	{
		areEqual = false;
	}
	else if (lhs.ShouldNormalize() != rhs.ShouldNormalize())
	{
		areEqual = false;
	}
	else if (lhs.GetOffsetIntoVertexBytes() != rhs.GetOffsetIntoVertexBytes())
	{
		areEqual = false;
	}

	return areEqual;
}


bool operator!=(const VertexAttribute& lhs, const VertexAttribute& rhs)
{
	return !(lhs == rhs);
}



// -----------------------------------------------------------------
// Queries
// -----------------------------------------------------------------
const std::string& VertexAttribute::GetName() const
{
	return m_name;
}


eVertexAttributeDataType VertexAttribute::GetDataType() const
{
	return m_type;
}


int VertexAttribute::GetDataElementCount() const
{
	return m_elementCount;
}


bool VertexAttribute::ShouldNormalize() const
{
	return m_isNormalized;
}


int VertexAttribute::GetOffsetIntoVertexBytes() const
{
	return m_memberOffsetBytes;
}



// -----------------------------------------------------------------
// Invalid Member/ Terminating Member
// -----------------------------------------------------------------
const VertexAttribute VertexAttribute::GetTerminatingAttribute()
{
	return VertexAttribute();
}
