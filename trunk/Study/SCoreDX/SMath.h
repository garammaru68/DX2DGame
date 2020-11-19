#pragma once
#include <d3d11_1.h>
#include <d3dx11.h>
#if !defined(__d3d11_h__) && !defined(__d3d11_x_h__) && !defined(__d3d12_h__) && !defined(__d3d12_x_h__)
#error include d3d11.h or d3d12.h before including SMath.h
#endif

#if !defined(_XBOX_ONE) || !defined(_TITLE)
	#include <dxgi1_2.h>
#endif

#include <functional>
#include <assert.h>
#include <memory.h>

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

#ifndef XM_CONSTEXPR
#define XM_CONSTEXPR
#endif
using namespace DirectX;
namespace SBASIS_EX
{
	struct SVector2;
	struct SVector3;
	struct SVector4;
	struct SDxMatrix;
	struct SQuaternion;
	struct SPlane;

	struct SRectangle
	{
		long x;
		long y;
		long width;
		long height;

		SRectangle() noexcept : x(0), y(0), width(0), height(0) {}
		XM_CONSTEXPR SRectangle(long ix, long iy, long iw, long ih) : x(ix), y(iy), width(iw), height(ih) {}
		explicit SRectangle(const RECT& rct) : x(rct.left), y(rct.top), width(rct.right - rct.left), height(rct.bottom - rct.top) {}

		SRectangle(const SRectangle&) = default;
		SRectangle& operator=(const SRectangle&) = default;

		SRectangle(SRectangle&&) = default;
		SRectangle& operator=(SRectangle&&) = default;

		operator RECT() { RECT rct; rct.left = x; rct.top = y; rct.right = (x + width); rct.bottom = (y + height); return rct; }
#ifdef __cplusplus_winrt
		operator Windows::Foundation::Rect() { return Windows:; Foundation::Rect(float(x), float(y), float(width), float(height)); }
#endif
		bool operator == (const SRectangle& r) const { return (x == r.x) && (y == r.y) && (width == r.width) && (height == r.height); }
		bool operator == (const RECT& rct) const { return (x == rct.left) && (y == rct.top) && (width == (rct.right - rct.left)) && (height == (rct.bottom - rct.top)); }

		bool operator != (const SRectangle& r) const { return (x != r.x) || (y != r.y) || (width != r.width) || (height != r.height); }
		bool operator != (const RECT& rct) const { return (x != rct.left) || (y != rct.top) || (width != (rct.right - rct.left)) || (height != (rct.bottom - rct.top)); }

		SRectangle& operator = (_In_ const RECT& rct) { x = rct.left; y = rct.top; width = (rct.right - rct.left); height = (rct.bottom - rct.top); return *this; }

		SVector2 Location() const;
		SVector2 Center() const;

		bool IsEmpty() const { return (width == 0 && height == 0 && x == 0 && y == 0); }

		bool Contains(long ix, long iy) const { return (x <= ix) && (ix < (x + width)) && (y <= iy) && (iy < (y + height)); }
		bool Contains(const SVector2& point) const;
		bool Contains(const SRectangle& r) const { return (x <= r.x) && ((r.x + r.width) <= (x + width)) && (y <= r.y) && ((r.y + r.height) <= (y + height)); }
		bool Contains(const RECT& rct) const { return (x <= rct.left) && (rct.right <= (x + width)) && (y <= rct.top) && (rct.bottom <= (y + height)); }

		void Inflate(long horizAmount, long vertAmount);

		bool Intersects(const SRectangle& r) const { return (r.x < (x + width)) && (x < (r.x + r.width)) && (r.y < (y + height)) && (y < (r.y + r.height)); }
		bool Intersects(const RECT& rct) const { return (rct.left < (x + width)) && (x < rct.right) && (rct.top < (y + height)) && (y < rct.bottom); }

		void Offset(long ox, long oy) { x += ox; y += oy; }

		static SRectangle Intersect(const SRectangle& ra, const SRectangle& rb);
		static RECT Intersect(const RECT& rcta, const RECT& rctb);

		static SRectangle Union(const SRectangle& ra, const SRectangle& rb);
		static RECT Union(const RECT& rcta, const RECT& rctb);

		// 2D vector
		struct SVector2 : DirectX::XMFLOAT2
		{
			SVector2() noexcept : XMFLOAT2(0.f, 0.f) {}
			XM_CONSTEXPR explicit SVector2(float x) : XMFLOAT2(x, x) {}
			XM_CONSTEXPR SVector2(float _x, float _y) : XMFLOAT2(_x, _y) {}
			explicit SVector2(_In_reads_(2) const float *pArray) : XMFLOAT2(pArray) {}
			SVector2(XMFLOAT2 V) { x = V.x; y = V.y; }
			SVector2(const XMFLOAT2& V) { this->x = V.x; this->y = V.y; }
			explicit SVector2(const DirectX::XMVECTORF32& F) { this->x = F.f[0]; this->y = F.f[1]; }

			SVector2(const SVector2&) = default;
			SVector2& operator = (const SVector2&) = default;

			SVector2(SVector2&&) = default;
			SVector2& operator = (SVector2&&) = default;

			operator DirectX::XMVECTOR() const { return XMLoadFloat2(this); }

			bool operator == (const SVector2& V) const;
			bool operator != (const SVector2& V) const;

			SVector2& operator = (const DirectX::XMVECTORF32& F) { x = F.f[0]; y = F.f[1]; return *this; }
			SVector2& operator+= (const SVector2& V);
			SVector2& operator-= (const SVector2& V);
			SVector2& operator*= (const SVector2& V);
			SVector2& operator*= (float S);
			SVector2& operator/= (float S);

			SVector2 operator+ () const { return *this; }
			SVector2 operator- () const { return SVector2(-x, -y); }

			bool InBounds(const SVector2& Bounds) const;

			float Length() const;
			float LengthSquared() const;

			float Dot(const SVector2& V) const;
			void Cross(const SVector2& V, SVector2& result) const;
			SVector2 Cross(const SVector2& V) const;

			void Normalize();
			void Normalize(Vector2)
		};
	};
};