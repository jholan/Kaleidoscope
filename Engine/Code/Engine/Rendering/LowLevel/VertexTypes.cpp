#include "Engine/Rendering/LowLevel/VertexTypes.hpp"

#include "Engine/Rendering/LowLevel/VertexAttribute.hpp"
#include "Engine/Rendering/LowLevel/VertexLayout.hpp"



// -----------------------------------------------------------------
// Vertex PCU
// Composition
// -----------------------------------------------------------------
Vertex_PCU::Vertex_PCU()
{

}


Vertex_PCU::Vertex_PCU(const VertexBuilder& builder)
{
	m_position = builder.position;
	m_color = builder.color;
	m_UVs = builder.UVs;
}


Vertex_PCU::Vertex_PCU(const vec3& position, const rgba& color, const vec2& uvs)
{
	m_position = position;
	m_color = color;
	m_UVs = uvs;
}



// -----------------------------------------------------------------
// Layout
// -----------------------------------------------------------------
const VertexLayout* Vertex_PCU::GetLayout()
{
	return &LAYOUT;
}


static void ConvertToPCU(const VertexBuilder* src, void* dst, uint count) 
{
	Vertex_PCU* buffer = (Vertex_PCU*)dst; 
	for (unsigned int i = 0; i < count; ++i)
	{
		const VertexBuilder& vertex = src[i];
		buffer[i] = Vertex_PCU(vertex.position, vertex.color, vertex.UVs);
	}
}


const VertexAttribute Vertex_PCU::LAYOUT_ELEMENTS[] = 
{
	VertexAttribute("POSITION",    VERTEX_ATTRIBUTE_DATA_TYPE_FLOAT, 3, false, offsetof(Vertex_PCU, m_position)),
	VertexAttribute("COLOR",       VERTEX_ATTRIBUTE_DATA_TYPE_FLOAT, 4, true,  offsetof(Vertex_PCU, m_color)),
	VertexAttribute("UV",          VERTEX_ATTRIBUTE_DATA_TYPE_FLOAT, 2, false, offsetof(Vertex_PCU, m_UVs)),
	VertexAttribute::GetTerminatingAttribute()
};
const VertexLayout Vertex_PCU::LAYOUT = VertexLayout(sizeof(Vertex_PCU), LAYOUT_ELEMENTS, ConvertToPCU);



// -----------------------------------------------------------------
// Vertex PCUTBN
// Composition
// -----------------------------------------------------------------
Vertex_PCUTBN::Vertex_PCUTBN() 
{

}


Vertex_PCUTBN::Vertex_PCUTBN(const VertexBuilder& builder)
{
	m_position = builder.position;
	m_color = builder.color;
	m_UVs = builder.UVs;
	m_normal = builder.normal;
	m_tangent = builder.tangent;
}


Vertex_PCUTBN::Vertex_PCUTBN(const vec3& position, const rgba& color, const vec2& uvs, const vec3& normal, const vec4& tangent)
{
	m_position = position;
	m_color = color;
	m_UVs = uvs;
	m_normal = normal;
	m_tangent = tangent;
}



// -----------------------------------------------------------------
// Layout
// -----------------------------------------------------------------
const VertexLayout* Vertex_PCUTBN::GetLayout()
{
	return &LAYOUT;
}


static void ConvertToPCUTBN(const VertexBuilder* src, void* dst, uint count) 
{
	Vertex_PCUTBN* buffer = (Vertex_PCUTBN*)dst; 
	for (unsigned int i = 0; i < count; ++i)
	{
		const VertexBuilder& vertex = src[i];
		buffer[i] = Vertex_PCUTBN(vertex.position, vertex.color, vertex.UVs, vertex.normal, vertex.tangent);
	}
}


const VertexAttribute Vertex_PCUTBN::LAYOUT_ELEMENTS[] = 
{
	VertexAttribute("POSITION",		VERTEX_ATTRIBUTE_DATA_TYPE_FLOAT, 3, false, offsetof(Vertex_PCU,	m_position)),
	VertexAttribute("COLOR",		VERTEX_ATTRIBUTE_DATA_TYPE_FLOAT, 4, true,  offsetof(Vertex_PCU,	m_color)),
	VertexAttribute( "NORMAL",		VERTEX_ATTRIBUTE_DATA_TYPE_FLOAT, 3, false, offsetof(Vertex_PCUTBN, m_normal) ),
	VertexAttribute( "UV",			VERTEX_ATTRIBUTE_DATA_TYPE_FLOAT, 2, false, offsetof(Vertex_PCUTBN, m_UVs) ),
	VertexAttribute( "TANGENT",		VERTEX_ATTRIBUTE_DATA_TYPE_FLOAT, 4, false, offsetof(Vertex_PCUTBN, m_tangent) ),
	VertexAttribute::GetTerminatingAttribute()
};
const VertexLayout Vertex_PCUTBN::LAYOUT = VertexLayout(sizeof(Vertex_PCUTBN), LAYOUT_ELEMENTS, ConvertToPCUTBN);