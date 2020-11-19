#include "MMath.h"

Vector3::Vector3()
{
	x = y = z = 0;
}
Vector3::Vector3(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}
Vector3::Vector3(const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}
bool Vector3::operator == (Vector3 const & v0)
{
	if (fabs(x - v0.x) < MBASIS_EPSILON)
	{
		if (fabs(y - v0.y) < MBASIS_EPSILON)
		{
			if (fabs(z - v0.z) < MBASIS_EPSILON)
			{
				return true;
			}
		}
	}
	return false;
}
Vector3 Vector3::operator + (Vector3 const & v0)
{
	return Vector3(v0.x + x, v0.y + y, v0.z + z);
}
Vector3 Vector3::operator - (Vector3 const & v0)
{
	return Vector3(x - v0.x, y - v0.y, z - v0.z);
}
Vector3 Vector3::operator * (float  const & fScala)
{
	return Vector3(x *fScala, y *fScala, z *fScala);
}
Vector3 Vector3::operator + (float  const & fScala)
{
	return Vector3(x + fScala, y + fScala, z + fScala);
}
Vector3 Vector3::operator / (float  const & fScala)
{
	return Vector3(x / fScala, y / fScala, z / fScala);
}

float Vector3::Length()
{
	return (float)sqrt(x*x + y * y + z * z);
}
// 벡터의 정규화 -> 벡터의 크기를 1로 만드는 것을 말함.
Vector3 Vector3::Normal()
{
	float fInvert = 1.0f / Length();
	x = x * fInvert;
	y = y * fInvert;
	z = z * fInvert;
	return Vector3(x, y, z);
}
float Vector3::Dot(Vector3 const&  v)
{
	return (x*v.x + y * v.y + z * v.z);
}
float Vector3::operator|(Vector3 const & v)
{
	return (x*v.x + y * v.y + z * v.z);
}
Vector3 Vector3::Cross(Vector3 const & v)
{
	return Vector3(y*v.z - z * v.y,
		z*v.x - x * v.z,
		x*v.y - y * v.x);
}
Vector3 Vector3::operator^(Vector3 const & v)
{
	return Vector3(y*v.z - z * v.y,
		z*v.x - x * v.z,
		x*v.y - y * v.x);
}
float Vector3::Angle(Vector3& v)
{
	Vector3 A = Normal();
	Vector3 B = v.Normal();
	float fCosAngle = A.Dot(B);
	float fRadian = acos(fCosAngle);
	return (float)RadianToDegree(fRadian);
}

Vector3 Vector3::operator * (MMatrix& m)
{
	Vector3 v;
	v.x = x * m._11 + y * m._21 + z * m._31 + m._41;
	v.y = x * m._12 + y * m._22 + z * m._32 + m._42;
	v.z = x * m._13 + y * m._23 + z * m._33 + m._43;
	return v;
}

void MMatrix::Identity()
{
	_12 = _13 = _14 = 0.0f;
	_21 = _23 = _24 = 0.0f;
	_31 = _32 = _34 = 0.0f;
	_41 = _42 = _43 = 0.0f;
	_11 = _22 = _33 = _44 = 1.0f;
}

MMatrix MMatrix::operator * (MMatrix const &matrix)
{
	MMatrix ret;
	for (int iColumn = 0; iColumn < 4; iColumn++)
	{
		for (int iRow = 0; iRow < 4; iRow++)
		{
			ret.m[iRow][iColumn] =
				m[iRow][0] * matrix.m[0][iColumn] +
				m[iRow][1] * matrix.m[1][iColumn] +
				m[iRow][2] * matrix.m[2][iColumn] +
				m[iRow][3] * matrix.m[3][iColumn];
		}
	}
	return ret;
}
void MMatrix::Scale(const Vector3& v)
{
	_11 = v.x; _22 = v.y; _33 = v.z;
}
void MMatrix::Scale(float x, float y, float z)
{
	_11 = x; _22 = y; _33 = z;
}
void MMatrix::XRotate(float fRadian)
{
	float fCos = cos(fRadian);
	float fSin = sin(fRadian);
	_22 = fCos; _23 = fSin;
	_32 = -fSin; _33 = fCos;
}
void MMatrix::YRotate(float fRadian)
{
	float fCos = cos(fRadian);
	float fSin = sin(fRadian);
	_11 = fCos; _13 = -fSin;
	_31 = fSin; _33 = fCos;
}
void MMatrix::ZRotate(float fRadian)
{
	float fCos = cos(fRadian);
	float fSin = sin(fRadian);
	_11 = fCos; _12 = fSin;
	_21 = -fSin; _22 = fCos;
}
void MMatrix::Translation(const Vector3& v)
{
	_41 = v.x; _42 = v.y; _43 = v.z;
}
void MMatrix::Translation(float x, float y, float z)
{
	_41 = x; _42 = y; _43 = z;
};
MMatrix MMatrix::Transpose()
{
	MMatrix ret;
	ret._11 = _11; ret._12 = _21; ret._13 = _31; ret._14 = _41;
	ret._21 = _12; ret._22 = _22; ret._23 = _32; ret._24 = _42;
	ret._31 = _13; ret._32 = _23; ret._33 = _33; ret._34 = _43;
	ret._41 = _14; ret._42 = _24; ret._43 = _34; ret._44 = _44;
	return ret;
}
Vector3  MMatrix::mul(Vector3 v)
{
	Vector3 ret;
	ret.x = v.x * m[0][0] + v.y * m[1][0] +
		v.z * m[2][0] + m[3][0];
	ret.y = v.x * m[0][1] + v.y * m[1][1] +
		v.z * m[2][1] + m[3][1];
	ret.z = v.x * m[0][2] + v.y * m[1][2] +
		v.z * m[2][2] + m[3][2];
	return ret;
}
MMatrix MMatrix::ViewMatrix(Vector3 pos,
	Vector3 target,
	Vector3 up)
{
	MMatrix ret;
	Vector3 zAxis = (target - pos).Normal();
	Vector3 xAxis = (up ^ zAxis).Normal();
	Vector3 yAxis = (zAxis ^ xAxis).Normal();

	_11 = xAxis.x; _12 = yAxis.x; _13 = zAxis.x;
	_21 = xAxis.y; _22 = yAxis.y; _23 = zAxis.y;
	_31 = xAxis.z; _32 = yAxis.z; _33 = zAxis.z;

	_41 = -(pos | xAxis);
	_42 = -(pos | yAxis);
	_43 = -(pos | zAxis);

	ret = *this;
	return ret;
}
MMatrix MMatrix::PerspectiveFovLH(float fNearPlane,
	float fFarPlane,
	float fovy,
	float Aspect) // width / heght
{
	float    h, w, Q;

	h = 1 / tan(fovy*0.5f);
	w = h / Aspect;

	Q = fFarPlane / (fFarPlane - fNearPlane);

	MMatrix ret;
	memset(this, 0, sizeof(MMatrix));

	_11 = w;
	_22 = h;
	_33 = Q;
	_43 = -Q * fNearPlane;
	_34 = 1;

	memcpy(&ret, this, 16 * sizeof(float));
	return ret;
}
MMatrix MMatrix::Inverse()
{
	MMatrix ret;
	return ret;
}