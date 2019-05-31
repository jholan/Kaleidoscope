#pragma once

#include "Engine/Math/Vectors.hpp"
#include "Engine/Rendering/RGBA.hpp"

class VertexLayout;
class VertexAttribute;



// -----------------------------------------------------------------
// Vertex Builder
// -----------------------------------------------------------------
class VertexBuilder
{
public:
	VertexBuilder() {};
	~VertexBuilder() {};



public:
	vec3 position = vec3(0.0f, 0.0f, 0.0f); 
	rgba color = rgba(1.0f, 1.0f, 1.0f); 
	vec2 UVs = vec2(0.0f, 0.0f);
	vec3 normal = vec3(0.0f, 1.0f, 0.0f);
	vec4 tangent = vec4(1.0f, 0.0f, 0.0f, 1.0f); // xyz tangent, w cotangent sign(+1,-1)
};



// -----------------------------------------------------------------
// Vertex PCU
// -----------------------------------------------------------------
class Vertex_PCU
{
public:
	// Composition
	Vertex_PCU();
	Vertex_PCU(const VertexBuilder& builder);
	Vertex_PCU(const vec3& position, const rgba& color, const vec2& uvs);



public:
	// Vertex Description
	static const VertexLayout* GetLayout();



public:
	vec3 m_position = vec3(0.0f, 0.0f, 0.0f); 
	rgba m_color = rgba(1.0f, 1.0f, 1.0f); 
	vec2 m_UVs = vec2(0.0f, 0.0f);



public: 
	static const VertexLayout LAYOUT;
	static const VertexAttribute LAYOUT_ELEMENTS[];
};



// -----------------------------------------------------------------
// Vertex PCUTBN
// -----------------------------------------------------------------
class Vertex_PCUTBN
{
public:
	// Composition
	Vertex_PCUTBN();
	Vertex_PCUTBN(const VertexBuilder& builder);
	Vertex_PCUTBN(const vec3& position, const rgba& color, const vec2& uvs, const vec3& normal, const vec4& tangent = vec4(1.0f, 0.0f, 0.0f, 1.0f));



public:
	// Vertex Description
	static const VertexLayout* GetLayout();



public:
	vec3 m_position = vec3(0.0f, 0.0f, 0.0f); 
	rgba m_color = rgba(1.0f, 1.0f, 1.0f); 
	vec2 m_UVs = vec2(0.0f, 0.0f);
	vec3 m_normal = vec3(0.0f, 1.0f, 0.0f);
	vec4 m_tangent = vec4(1.0f, 0.0f, 0.0f, 1.0f); // xyz tangent, w cotangent sign(+1,-1)



public: 
	static const VertexLayout LAYOUT;
	static const VertexAttribute LAYOUT_ELEMENTS[];
};