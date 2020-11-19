#pragma once
#include "MDxHelperEx.h"
#include <math.h>
#include <memory.h>
#define MBASIS_EPSILON ((float)0.001f)
#define MBASIS_PI ((float)3.14192654f)
#define DegreeToRadian(degree) ((degree) *(MBASIS_PI/ 180.0f))
#define RadianToDegree(radian) ((radian) *(180.0f/MBASIS_PI))

struct MMatrix;

struct float2
{
	union
	{
		struct { float x, y; };
		float v[2];
	};
};
struct float3
{
	union
	{
		struct { float x, y, z; };
		float v[3];
	};
};
struct float4
{
	union
	{
		struct { float x, y, z, w; };
		float v[4];
	};
};
struct Vector2 : float2
{
	Vector2(const Vector2& v)
	{
		x = v.x; y = v.y;
	}
	Vector2() { x = y = 0; }
	Vector2(float a, float b)
	{
		x = a;
		y = b;
	}
};
struct Vector3 : float3
{
	Vector3();
	Vector3(const Vector3& v);
	Vector3(float a, float b, float c);
	Vector3 operator + (Vector3 const & v0);
	Vector3 operator - (Vector3 const & v0);
	Vector3 operator * (float  const & fScala);
	Vector3 operator + (float  const & fScala);
	Vector3 operator / (float  const & fScala);
	bool operator == (Vector3 const & v);
	float Length();
	float Dot(Vector3 const & v0);
	float operator | (Vector3 const & v);
	Vector3 Cross(Vector3 const & v0);
	Vector3 operator ^ (Vector3 const & v);
	Vector3 Normal();
	float Angle(Vector3& v);
	Vector3 operator * (MMatrix& m);
};
struct Vector4 : float4
{
	Vector4() { x = y = z = w = 0; }
	Vector4(const Vector4& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}
	Vector4(float a, float b, float c, float d)
	{
		x = a;
		y = b;
		z = c;
		w = d;
	}
};

struct float4x4
{
	union {
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
	};
};
struct MMatrix :float4x4
{
	void Identity();
	MMatrix()
	{
		Identity();
	}
	MMatrix(const MMatrix& m)
	{
		_11 = m._11; _12 = m._12; _13 = m._13; _14 = m._14;
		_21 = m._21; _22 = m._22; _23 = m._23; _24 = m._24;
		_31 = m._31; _32 = m._32; _33 = m._33; _34 = m._34;
		_41 = m._41; _42 = m._42; _43 = m._43; _44 = m._44;
	};
	Vector3  mul(Vector3 v);
	MMatrix operator * (MMatrix const &m);
	void Scale(const Vector3& v);
	void Scale(float x, float y, float z);
	void XRotate(float fRadian);
	void YRotate(float fRadian);
	void ZRotate(float fRadian);
	void Translation(const Vector3& v);
	void Translation(float x, float y, float z);
	MMatrix Transpose();
	MMatrix ViewMatrix(Vector3 pos,
		Vector3 target,
		Vector3 up);
	MMatrix PerspectiveFovLH(float fNearPlane,
		float fFarPlane,
		float fovy,
		float Aspect);
	MMatrix Inverse();
};