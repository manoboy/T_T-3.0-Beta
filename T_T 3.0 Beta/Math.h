#pragma once
#include "Globals.h"
class Vector3D
{
public:
	float x;
	float y;
	float z;
	//SwapLines1
	//AddRandomTrash	
	//AddRandomTrash	
	//AddRandomTrash	
	//AddRandomTrash	
	Vector3D(){};

	Vector3D(float r, float s, float t){ x = r; y = s; z = t; };

	Vector3D& Set(float r, float s, float t){ x = r; y = s; z = t; return (*this); };

	float& operator [](long k){ return ((&x)[k]); };

	const float& operator [](long k) const{ return ((&x)[k]); };

	Vector3D& operator +=(const Vector3D& v){ x += v.x; y += v.y; z += v.z; return (*this); };

	Vector3D& operator -=(const Vector3D& v){ x -= v.x; y -= v.y; z -= v.z; return (*this); };

	Vector3D& operator *=(float t){ x *= t; y *= t; z *= t; return (*this); };

	Vector3D& operator /=(float t){ float f = 1.0F / t; x *= f; y *= f; z *= f; return (*this); };

	Vector3D& operator %=(const Vector3D& v){ float r, s; r = y * v.z - z * v.y; s = z * v.x - x * v.z; z = x * v.y - y * v.x; x = r; y = s; return (*this); };

	Vector3D& operator &=(const Vector3D& v){ x *= v.x; y *= v.y; z *= v.z; return (*this); };

	Vector3D operator -(void) const{ return (Vector3D(-x, -y, -z)); };

	Vector3D operator +(const Vector3D& v) const{ return (Vector3D(x + v.x, y + v.y, z + v.z)); };

	Vector3D operator -(const Vector3D& v) const{ return (Vector3D(x - v.x, y - v.y, z - v.z)); };

	Vector3D operator *(float t) const{ return (Vector3D(x * t, y * t, z * t)); };

	Vector3D operator /(float t) const{ float f = 1.0F / t; return (Vector3D(x * f, y * f, z * f)); };

	float operator *(const Vector3D& v) const{ return (x * v.x + y * v.y + z * v.z); };

	Vector3D operator %(const Vector3D& v) const{ return (Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x)); };

	Vector3D operator &(const Vector3D& v) const{ return (Vector3D(x * v.x, y * v.y, z * v.z)); };

	bool operator ==(const Vector3D& v) const{ return ((x == v.x) && (y == v.y) && (z == v.z)); };

	bool operator !=(const Vector3D& v) const{ return ((x != v.x) || (y != v.y) || (z != v.z)); };

	Vector3D& Normalize(void){ return (*this /= sqrtf(x * x + y * y + z * z)); };
	//SwapLines0
};

inline Vector3D operator *(float t, const Vector3D& v)
{
	return (Vector3D(t * v.x, t * v.y, t * v.z));
}

inline float Dot(const Vector3D& v1, const Vector3D& v2)
{
	return (v1 * v2);
}

inline Vector3D Cross(const Vector3D& v1, const Vector3D& v2)
{
	return (v1 % v2);
}

inline float Magnitude(const Vector3D& v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

inline float InverseMag(const Vector3D& v)
{
	return (1.0F / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

inline float SquaredMag(const Vector3D& v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}


class ViewMatrix
{
public:
	float Matrix[4][4];
};

class BoneMatrix
{
public:
	float Matrix[3][4];
};

class Bones
{
public:
	bool IsOnScreen;
	Vector3D PositionInGame;
	Vector3D PositionOnScreen;
};

float Get3dDistance(Vector3D Pos1, Vector3D Pos2);
bool WorldToScreen(Vector3D PositionIn, Vector3D &PositionOut);
void CalcAngle(Vector3D src, Vector3D dst, Vector3D &angles);
Vector3D AngleToDirection(Vector3D angle);

extern ViewMatrix vMatrix;
