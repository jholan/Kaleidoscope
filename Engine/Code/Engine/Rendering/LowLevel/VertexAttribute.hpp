#pragma once

#include <string>


enum eVertexAttributeDataType
{
	VERTEX_ATTRIBUTE_DATA_TYPE_FLOAT,
	VERTEX_ATTRIBUTE_DATA_TYPE_INT,
	VERTEX_ATTRIBUTE_DATA_TYPE_UINT,
	VERTEX_ATTRIBUTE_DATA_TYPE_BYTE,
};


class VertexAttribute
{
public:
	// Composition
	VertexAttribute();
	VertexAttribute(const std::string name, eVertexAttributeDataType type, int elementCount, bool normalize, size_t offset);
	VertexAttribute(const VertexAttribute& other);
	~VertexAttribute();

	void operator=(const VertexAttribute& other);


	// Comparison
	friend bool operator==(const VertexAttribute& lhs, const VertexAttribute& rhs);
	friend bool operator!=(const VertexAttribute& lhs, const VertexAttribute& rhs);


	// Queries
	const std::string& GetName() const;
	eVertexAttributeDataType GetDataType() const;
	int GetDataElementCount() const;
	bool ShouldNormalize() const;
	int GetOffsetIntoVertexBytes() const;



public:
	static const VertexAttribute GetTerminatingAttribute();



private:
	std::string m_name = ""; // POSITION, COLOR, UV // This is a std::string as its used for its string value

	eVertexAttributeDataType m_type = VERTEX_ATTRIBUTE_DATA_TYPE_FLOAT;
	int m_elementCount = 0; // How many floats, ints, etc
	bool m_isNormalized = false;

	int m_memberOffsetBytes = -1;
};