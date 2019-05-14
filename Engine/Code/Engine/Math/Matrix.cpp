#include "Engine/Math/Matrix.hpp"

#include "Engine/__Control/__Control.hpp"
#include "Engine/Math/Vectors.hpp"



// -----------------------------------------------------------------
// Composition
// -----------------------------------------------------------------
mat4::mat4()
{
	Ix = 1.0f;
	Iy = 0.0f;
	Iz = 0.0f;
	Iw = 0.0f;

	Jx = 0.0f;
	Jy = 1.0f;
	Jz = 0.0f;
	Jw = 0.0f;

	Kx = 0.0f;
	Ky = 0.0f;
	Kz = 1.0f;
	Kw = 0.0f;

	Tx = 0.0f;
	Ty = 0.0f;
	Tz = 0.0f;
	Tw = 1.0f;
}


mat4::mat4(const float* sixteenValuesBasisMajor)
{
	Ix = sixteenValuesBasisMajor[0];
	Iy = sixteenValuesBasisMajor[1];
	Iz = sixteenValuesBasisMajor[2];
	Iw = sixteenValuesBasisMajor[3];

	Jx = sixteenValuesBasisMajor[4];
	Jy = sixteenValuesBasisMajor[5];
	Jz = sixteenValuesBasisMajor[6];
	Jw = sixteenValuesBasisMajor[7];

	Kx = sixteenValuesBasisMajor[8];
	Ky = sixteenValuesBasisMajor[9];
	Kz = sixteenValuesBasisMajor[10];
	Kw = sixteenValuesBasisMajor[11];

	Tx = sixteenValuesBasisMajor[12];
	Ty = sixteenValuesBasisMajor[13];
	Tz = sixteenValuesBasisMajor[14];
	Tw = sixteenValuesBasisMajor[15];
}


mat4::mat4(const vec2& iBasis, const vec2& jBasis, const vec2& translation)
{
	Ix = iBasis.x;
	Iy = iBasis.y;
	Iz = 0.0f;
	Iw = 0.0f;

	Jx = jBasis.x;
	Jy = jBasis.y;
	Jz = 0.0f;
	Jw = 0.0f;

	Kx = 0.0f;
	Ky = 0.0f;
	Kz = 1.0f;
	Kw = 0.0f;

	Tx = translation.x;
	Ty = translation.y;
	Tz = 0.0f;
	Tw = 1.0f;
}


mat4::mat4(const vec3& iBasis, const vec3& jBasis, const vec3& kBasis, const vec3& translation)
{
	Ix = iBasis.x;
	Iy = iBasis.y;
	Iz = iBasis.z;
	Iw = 0.0f;

	Jx = jBasis.x;
	Jy = jBasis.y;
	Jz = jBasis.z;
	Jw = 0.0f;

	Kx = kBasis.x;
	Ky = kBasis.y;
	Kz = kBasis.z;
	Kw = 0.0f;

	Tx = translation.x;
	Ty = translation.y;
	Tz = translation.z;
	Tw = 1.0f;
}


mat4::mat4(const vec4& iBasis, const vec4& jBasis, const vec4& kBasis, const vec4& translation)
{
	Ix = iBasis.x;
	Iy = iBasis.y;
	Iz = iBasis.z;
	Iw = iBasis.w;

	Jx = jBasis.x;
	Jy = jBasis.y;
	Jz = jBasis.z;
	Jw = jBasis.w;

	Kx = kBasis.x;
	Ky = kBasis.y;
	Kz = kBasis.z;
	Kw = kBasis.w;

	Tx = translation.x;
	Ty = translation.y;
	Tz = translation.z;
	Tw = translation.w;
}



// -----------------------------------------------------------------
// Basis Vectors
// -----------------------------------------------------------------
vec3 mat4::GetI() const
{
	vec3 iBasisVector = vec3(Ix, Iy, Iz);
	return iBasisVector;
}


vec3 mat4::GetJ() const
{
	vec3 jBasisVector = vec3(Jx, Jy, Jz);
	return jBasisVector;
}


vec3 mat4::GetK() const
{
	vec3 kBasisVector = vec3(Kx, Ky, Kz);
	return kBasisVector;
}


vec3 mat4::GetTranslation() const
{
	vec3 translation = vec3(Tx, Ty, Tz);
	return translation;
}


vec3 mat4::GetEulerAngles() const
{
	float xRad;
	float yRad;
	float zRad;

	float sx = -Ky;
	sx = Clamp(sx, -1.0f, 1.0f);
	xRad = ASin(sx);

	float cx = CosRadians(xRad);
	if (!FloatEquals(cx, 0.0f))
	{
		yRad = ATan2(Kx, Kz);
		zRad = ATan2(Iy, Jy);
	}
	else
	{
		// Gimbal?
		zRad = 0.0f;
		yRad = ATan2(-Iz, Ix);
	}

	vec3 eulerDegrees = vec3(ConvertRadiansToDegrees(xRad), ConvertRadiansToDegrees(yRad), ConvertRadiansToDegrees(zRad));
	return eulerDegrees;
}



// -----------------------------------------------------------------
// Matrix Creation Helpers
// Rotation
// -----------------------------------------------------------------
mat4 mat4::CreateRotation2DDegrees(float rotationDegrees)
{
	mat4 rotationtMatrix = mat4();

	float sinOfRotation = SinDegrees(rotationDegrees);
	float cosOfRotation = CosDegrees(rotationDegrees);

	rotationtMatrix.Ix = cosOfRotation;
	rotationtMatrix.Iy = sinOfRotation;

	rotationtMatrix.Jx = -sinOfRotation;
	rotationtMatrix.Jy = cosOfRotation;

	return rotationtMatrix;
}


mat4 mat4::CreateRotationXDegrees(float rotationDegrees)
{
	float cosDeg = CosDegrees(rotationDegrees);
	float sinDeg = SinDegrees(rotationDegrees);

	mat4 rotationAroundX = mat4(vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, cosDeg, sinDeg), vec3(0.0f, -sinDeg, cosDeg));
	return rotationAroundX;
}


mat4 mat4::CreateRotationYDegrees(float rotationDegrees)
{
	float cosDeg = CosDegrees(rotationDegrees);
	float sinDeg = SinDegrees(rotationDegrees);

	mat4 rotationAroundY = mat4(vec3(cosDeg, 0.0f, -sinDeg), vec3(0.0f, 1.0f, 0.0f), vec3(sinDeg, 0.0f, cosDeg));
	return rotationAroundY;
}


mat4 mat4::CreateRotationZDegrees(float rotationDegrees)
{
	float cosDeg = CosDegrees(rotationDegrees);
	float sinDeg = SinDegrees(rotationDegrees);

	mat4 rotationAroundY = mat4(vec3(cosDeg, sinDeg, 0.0f), vec3(-sinDeg, cosDeg, 0.0f), vec3(0.0f, 0.0f, 1.0f));
	return rotationAroundY;
}


mat4 mat4::CreateRotationEulerDegrees(const vec3& eulerAnglesDegrees)
{
	mat4 zRotation = CreateRotationZDegrees(eulerAnglesDegrees.z);
	mat4 xRotation = CreateRotationXDegrees(eulerAnglesDegrees.x);
	mat4 yRotation = CreateRotationYDegrees(eulerAnglesDegrees.y);

	mat4 eulerTransform = Mul(yRotation, Mul(xRotation, zRotation));
	return eulerTransform;
}



// -----------------------------------------------------------------
// Scale
// -----------------------------------------------------------------
mat4 mat4::CreateScale2D(float scaleX, float scaleY)
{
	mat4 scaleMatrix = mat4();

	scaleMatrix.Ix = scaleX;
	scaleMatrix.Jy = scaleY;

	return scaleMatrix;
}


mat4 mat4::CreateScale(float scaleX, float scaleY, float scaleZ)
{
	mat4 scaleMatrix = mat4();

	scaleMatrix.Ix = scaleX;
	scaleMatrix.Jy = scaleY;
	scaleMatrix.Kz = scaleZ;

	return scaleMatrix;
}


mat4 mat4::CreateUniformScale2D(float scaleXY)
{
	mat4 scaleMatrix = mat4();

	scaleMatrix.Ix = scaleXY;
	scaleMatrix.Jy = scaleXY;

	return scaleMatrix;
}


mat4 mat4::CreateUniformScale(float scaleXYZ)
{
	mat4 uniformScaleMatrix = mat4();

	uniformScaleMatrix.Ix = scaleXYZ;
	uniformScaleMatrix.Jy = scaleXYZ;
	uniformScaleMatrix.Kz = scaleXYZ;

	return uniformScaleMatrix;
}


// -----------------------------------------------------------------
// Translation
// -----------------------------------------------------------------
mat4 mat4::CreateTranslation2D(const vec2& translation)
{
	mat4 translationMatrix = mat4();

	translationMatrix.Tx = translation.x;
	translationMatrix.Ty = translation.y;

	return translationMatrix;
}


mat4 mat4::CreateTranslation(const vec3& translation)
{
	mat4 translationMatrix = mat4();

	translationMatrix.Tx = translation.x;
	translationMatrix.Ty = translation.y;
	translationMatrix.Tz = translation.z;

	return translationMatrix;
}



// -----------------------------------------------------------------
// Projection
// -----------------------------------------------------------------
mat4 mat4::CreateOrthographicProjection2D(const vec2& bottomLeft, const vec2& topRight)
{
	mat4 orthoMatrix = mat4::CreateOrthographicProjection(bottomLeft.x, topRight.x, bottomLeft.y, topRight.y, 0.0f, 1.0f);
	return orthoMatrix;
}


mat4 mat4::CreateOrthographicProjection(float left, float right, float bottom, float top, float near, float far)
{
	float xScale = 2.0f / (right - left);
	float yScale = 2.0f / (top - bottom);
	float zScale = 2.0f / (far - near);

	float xTranslation = -(left + right) / 2.0f;
	float yTranslation = -(bottom + top) / 2.0f;
	float zTranslation = -(near + far) / 2.0f;
	vec3  translation = vec3(xTranslation, yTranslation, zTranslation);

	mat4 orthographicProjection = Mul(CreateScale(xScale, yScale, zScale), CreateTranslation(translation));

#ifdef DIRECT_X
	mat4 openGLtoDirectx = mat4(vec4(1, 0, 0, 0), vec4(0, 1, 0, 0), vec4(0, 0, 0.5, 0), vec4(0, 0, 0.5, 1));
	orthographicProjection = Mul(openGLtoDirectx, orthographicProjection);
#endif

	return orthographicProjection;
}


mat4 mat4::CreatePerspectiveProjection(float verticalFOVdegrees, float aspect, float nz, float fz)
{
	float d = 1.0f / TanDegrees(verticalFOVdegrees);
	float q = 1.0f / (fz - nz); 

#ifdef DIRECT_X
	vec4 i = vec4( d / aspect, 0,    0,                   0 );  
	vec4 j = vec4( 0,          d,    0,                   0 ); 
	vec4 k = vec4( 0,          0,    fz * q,			  1 ); // Negation
	vec4 t = vec4( 0,          0,    -(nz * fz * q),	  0 ); // Negation
#else
	vec4 i = vec4( d / aspect, 0,    0,                   0 );  
	vec4 j = vec4( 0,          d,    0,                   0 ); 
	vec4 k = vec4( 0,          0,    (nz + fz) * q,       1 );
	vec4 t = vec4( 0,          0,    -2.0f * nz * fz * q, 0 ); 
#endif

	return mat4( i, j, k, t ); 
}


// -----------------------------------------------------------------
// Look At
// -----------------------------------------------------------------
mat4 mat4::CreateLookAt(const vec3& observerPosition, const vec3& targetPosition, const vec3& worldUp)
{
	vec3 directionToTarget = targetPosition - observerPosition;
	vec3 forward = Normalize(directionToTarget);

	vec3 wUp = worldUp;
	if(FloatEquals(Dot(forward, worldUp), -1.0f, .01f))
	{
		wUp = vec3(0.0f, 0.0f, 1.0f);
	}
	vec3 right = Cross(wUp, forward);
	right = Normalize(right);

	vec3 up = Cross(forward, right);

	mat4 lookAtMatrix = mat4(right, up, forward, observerPosition);
	return lookAtMatrix;
}


mat4 mat4::CreateLookAtInverse(const vec3& observerPosition, const vec3& targetPosition, const vec3& worldUp)
{
	vec3 directionToTarget = targetPosition - observerPosition;
	vec3 forward = Normalize(directionToTarget);
	vec3 right = Normalize(Cross(worldUp, forward));
	vec3 up = Cross(forward, right);

	// Rigid body inverse
	//	Transpose the rotation
	//	Negate the translation
	vec3 transposedRight	= vec3(right.x, up.x, forward.x);
	vec3 transposedUp		= vec3(right.y, up.y, forward.y);
	vec3 transposedForward	= vec3(right.z, up.z, forward.z);

	mat4 inverseRotation = mat4(transposedRight, transposedUp, transposedForward);
	mat4 inverseTranslation = CreateTranslation(-observerPosition);
	mat4 inverseLookAt = Mul(inverseRotation, inverseTranslation);
	return  inverseLookAt;
}



// -----------------------------------------------------------------
// Utility
// -----------------------------------------------------------------
mat4 Transpose(const mat4& matrix)
{
	mat4 transposed = mat4();

	transposed.Ix = matrix.Ix;
	transposed.Jx = matrix.Iy;
	transposed.Kx = matrix.Iz;
	transposed.Tx = matrix.Iw;

	transposed.Iy = matrix.Jx;
	transposed.Jy = matrix.Jy;
	transposed.Ky = matrix.Jz;
	transposed.Ty = matrix.Jw;

	transposed.Iz = matrix.Kx;
	transposed.Jz = matrix.Ky;
	transposed.Kz = matrix.Kz;
	transposed.Tz = matrix.Kw;

	transposed.Iw = matrix.Tx;
	transposed.Jw = matrix.Ty;
	transposed.Kw = matrix.Tz;
	transposed.Tw = matrix.Tw;

	return transposed;
}


mat4 Invert(const mat4& matrix)
{
	const float* m = &matrix.Ix; // Matrix to invert
	float invOut[16];


	double inv[16];
	double det;
	int i;

	inv[0] = m[5]  * m[10] * m[15] - 
		m[5]  * m[11] * m[14] - 
		m[9]  * m[6]  * m[15] + 
		m[9]  * m[7]  * m[14] +
		m[13] * m[6]  * m[11] - 
		m[13] * m[7]  * m[10];

	inv[4] = -m[4]  * m[10] * m[15] + 
		m[4]  * m[11] * m[14] + 
		m[8]  * m[6]  * m[15] - 
		m[8]  * m[7]  * m[14] - 
		m[12] * m[6]  * m[11] + 
		m[12] * m[7]  * m[10];

	inv[8] = m[4]  * m[9] * m[15] - 
		m[4]  * m[11] * m[13] - 
		m[8]  * m[5] * m[15] + 
		m[8]  * m[7] * m[13] + 
		m[12] * m[5] * m[11] - 
		m[12] * m[7] * m[9];

	inv[12] = -m[4]  * m[9] * m[14] + 
		m[4]  * m[10] * m[13] +
		m[8]  * m[5] * m[14] - 
		m[8]  * m[6] * m[13] - 
		m[12] * m[5] * m[10] + 
		m[12] * m[6] * m[9];

	inv[1] = -m[1]  * m[10] * m[15] + 
		m[1]  * m[11] * m[14] + 
		m[9]  * m[2] * m[15] - 
		m[9]  * m[3] * m[14] - 
		m[13] * m[2] * m[11] + 
		m[13] * m[3] * m[10];

	inv[5] = m[0]  * m[10] * m[15] - 
		m[0]  * m[11] * m[14] - 
		m[8]  * m[2] * m[15] + 
		m[8]  * m[3] * m[14] + 
		m[12] * m[2] * m[11] - 
		m[12] * m[3] * m[10];

	inv[9] = -m[0]  * m[9] * m[15] + 
		m[0]  * m[11] * m[13] + 
		m[8]  * m[1] * m[15] - 
		m[8]  * m[3] * m[13] - 
		m[12] * m[1] * m[11] + 
		m[12] * m[3] * m[9];

	inv[13] = m[0]  * m[9] * m[14] - 
		m[0]  * m[10] * m[13] - 
		m[8]  * m[1] * m[14] + 
		m[8]  * m[2] * m[13] + 
		m[12] * m[1] * m[10] - 
		m[12] * m[2] * m[9];

	inv[2] = m[1]  * m[6] * m[15] - 
		m[1]  * m[7] * m[14] - 
		m[5]  * m[2] * m[15] + 
		m[5]  * m[3] * m[14] + 
		m[13] * m[2] * m[7] - 
		m[13] * m[3] * m[6];

	inv[6] = -m[0]  * m[6] * m[15] + 
		m[0]  * m[7] * m[14] + 
		m[4]  * m[2] * m[15] - 
		m[4]  * m[3] * m[14] - 
		m[12] * m[2] * m[7] + 
		m[12] * m[3] * m[6];

	inv[10] = m[0]  * m[5] * m[15] - 
		m[0]  * m[7] * m[13] - 
		m[4]  * m[1] * m[15] + 
		m[4]  * m[3] * m[13] + 
		m[12] * m[1] * m[7] - 
		m[12] * m[3] * m[5];

	inv[14] = -m[0]  * m[5] * m[14] + 
		m[0]  * m[6] * m[13] + 
		m[4]  * m[1] * m[14] - 
		m[4]  * m[2] * m[13] - 
		m[12] * m[1] * m[6] + 
		m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] + 
		m[1] * m[7] * m[10] + 
		m[5] * m[2] * m[11] - 
		m[5] * m[3] * m[10] - 
		m[9] * m[2] * m[7] + 
		m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] - 
		m[0] * m[7] * m[10] - 
		m[4] * m[2] * m[11] + 
		m[4] * m[3] * m[10] + 
		m[8] * m[2] * m[7] - 
		m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] + 
		m[0] * m[7] * m[9] + 
		m[4] * m[1] * m[11] - 
		m[4] * m[3] * m[9] - 
		m[8] * m[1] * m[7] + 
		m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] - 
		m[0] * m[6] * m[9] - 
		m[4] * m[1] * m[10] + 
		m[4] * m[2] * m[9] + 
		m[8] * m[1] * m[6] - 
		m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	if (det == 0)
	{
		return mat4();
	}

	det = 1.0 / det;

	for (i = 0; i < 16; i++)
	{
		invOut[i] = (float)(inv[i] * det);
	}


	mat4 inverted = mat4(invOut);
	return inverted;
}


mat4 Mul(const mat4& lhs, const mat4& rhs)
{
	mat4 result;

	result.Ix = (lhs.Ix * rhs.Ix) + (lhs.Jx * rhs.Iy) + (lhs.Kx * rhs.Iz) + (lhs.Tx * rhs.Iw);
	result.Iy = (lhs.Iy * rhs.Ix) + (lhs.Jy * rhs.Iy) + (lhs.Ky * rhs.Iz) + (lhs.Ty * rhs.Iw);
	result.Iz = (lhs.Iz * rhs.Ix) + (lhs.Jz * rhs.Iy) + (lhs.Kz * rhs.Iz) + (lhs.Tz * rhs.Iw);
	result.Iw = (lhs.Iw * rhs.Ix) + (lhs.Jw * rhs.Iy) + (lhs.Kw * rhs.Iz) + (lhs.Tw * rhs.Iw);

	result.Jx = (lhs.Ix * rhs.Jx) + (lhs.Jx * rhs.Jy) + (lhs.Kx * rhs.Jz) + (lhs.Tx * rhs.Jw);
	result.Jy = (lhs.Iy * rhs.Jx) + (lhs.Jy * rhs.Jy) + (lhs.Ky * rhs.Jz) + (lhs.Ty * rhs.Jw);
	result.Jz = (lhs.Iz * rhs.Jx) + (lhs.Jz * rhs.Jy) + (lhs.Kz * rhs.Jz) + (lhs.Tz * rhs.Jw);
	result.Jw = (lhs.Iw * rhs.Jx) + (lhs.Jw * rhs.Jy) + (lhs.Kw * rhs.Jz) + (lhs.Tw * rhs.Jw);

	result.Kx = (lhs.Ix * rhs.Kx) + (lhs.Jx * rhs.Ky) + (lhs.Kx * rhs.Kz) + (lhs.Tx * rhs.Kw);
	result.Ky = (lhs.Iy * rhs.Kx) + (lhs.Jy * rhs.Ky) + (lhs.Ky * rhs.Kz) + (lhs.Ty * rhs.Kw);
	result.Kz = (lhs.Iz * rhs.Kx) + (lhs.Jz * rhs.Ky) + (lhs.Kz * rhs.Kz) + (lhs.Tz * rhs.Kw);
	result.Kw = (lhs.Iw * rhs.Kx) + (lhs.Jw * rhs.Ky) + (lhs.Kw * rhs.Kz) + (lhs.Tw * rhs.Kw);

	result.Tx = (lhs.Ix * rhs.Tx) + (lhs.Jx * rhs.Ty) + (lhs.Kx * rhs.Tz) + (lhs.Tx * rhs.Tw);
	result.Ty = (lhs.Iy * rhs.Tx) + (lhs.Jy * rhs.Ty) + (lhs.Ky * rhs.Tz) + (lhs.Ty * rhs.Tw);
	result.Tz = (lhs.Iz * rhs.Tx) + (lhs.Jz * rhs.Ty) + (lhs.Kz * rhs.Tz) + (lhs.Tz * rhs.Tw);
	result.Tw = (lhs.Iw * rhs.Tx) + (lhs.Jw * rhs.Ty) + (lhs.Kw * rhs.Tz) + (lhs.Tw * rhs.Tw);

	return result;
}


vec4 Mul(const mat4& lhs, const vec4& rhs)
{
	vec4 transformedVec;

	transformedVec.x = (lhs.Ix * rhs.x) + (lhs.Jx * rhs.y) + (lhs.Kx * rhs.z) + (lhs.Tx * rhs.w);
	transformedVec.y = (lhs.Iy * rhs.x) + (lhs.Jy * rhs.y) + (lhs.Ky * rhs.z) + (lhs.Ty * rhs.w);
	transformedVec.z = (lhs.Iz * rhs.x) + (lhs.Jz * rhs.y) + (lhs.Kz * rhs.z) + (lhs.Tz * rhs.w);
	transformedVec.w = (lhs.Iw * rhs.x) + (lhs.Jw * rhs.y) + (lhs.Kw * rhs.z) + (lhs.Tw * rhs.w);

	return transformedVec;
}

