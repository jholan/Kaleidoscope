#pragma once

#include "Engine/Math/Vectors.hpp"



// COLUMN MAJOR
class mat4
{
public:
	// Composition
	mat4(); // default-construct to Identity matrix (via variable initialization)
	explicit mat4(const float* sixteenValuesBasisMajor); // float[16] array in order Ix, Iy...
	explicit mat4(const vec2& iBasis, const vec2& jBasis, const vec2& translation=vec2(0.f,0.f));
	explicit mat4(const vec3& iBasis, const vec3& jBasis, const vec3& kBasis, const vec3& translation = vec3(0.0f, 0.0f, 0.0f));
	explicit mat4(const vec4& iBasis, const vec4& jBasis, const vec4& kBasis, const vec4& translation = vec4(0.0f, 0.0f, 0.0f, 0.0f));


	// Basis Vectors
	vec3 GetI() const;
	vec3 GetJ() const;
	vec3 GetK() const;
	vec3 GetTranslation() const;

	vec3 GetEulerAngles() const;


	// Matrix Creation Helpers
	// Rotation
	static mat4 CreateRotation2DDegrees(float rotationDegrees);
	static mat4 CreateRotationXDegrees(float rotationDegrees);
	static mat4 CreateRotationYDegrees(float rotationDegrees);
	static mat4 CreateRotationZDegrees(float rotationDegrees);
	static mat4 CreateRotationEulerDegrees(const vec3& eulerAnglesDegrees);

	// Scale
	static mat4 CreateScale2D(float scaleX, float scaleY);
	static mat4 CreateScale(float scaleX, float scaleY, float scaleZ);

	// Uniform Scale
	static mat4 CreateUniformScale2D(float scaleXY);
	static mat4 CreateUniformScale(float scaleXYZ);

	// Translation
	static mat4 CreateTranslation2D(const vec2& translation);
	static mat4 CreateTranslation(const vec3& translation);

	// Projection
	static mat4 CreateOrthographicProjection2D(const vec2& bottomLeft, const vec2& topRight);
	static mat4 CreateOrthographicProjection(float left, float right, float bottom, float top, float near, float far);
	static mat4 CreatePerspectiveProjection(float fov_degrees, float aspect, float nz, float fz);

	// Look at
	static mat4 CreateLookAt(const vec3& observerPosition, const vec3& targetPosition, const vec3& worldUp = vec3(0.0f, 1.0f, 0.0f));
	static mat4 CreateLookAtInverse(const vec3& observerPosition, const vec3& targetPosition, const vec3& worldUp = vec3(0.0f, 1.0f, 0.0f));



public:
	float Ix = 1.0f, Iy = 0.0f, Iz = 0.0f, Iw = 0.0f; // The first 4 floats are the first column
	float Jx = 0.0f, Jy = 1.0f, Jz = 0.0f, Jw = 0.0f;
	float Kx = 0.0f, Ky = 0.0f, Kz = 1.0f, Kw = 0.0f;
	float Tx = 0.0f, Ty = 0.0f, Tz = 0.0f, Tw = 1.0f;
};



mat4 Transpose(const mat4& matrix);
mat4 Invert(const mat4& matrix);
mat4 Mul(const mat4& lhs, const mat4& rhs);
vec4 Mul(const mat4& lhs, const vec4& rhs);