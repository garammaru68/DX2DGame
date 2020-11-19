#pragma once
#include "MBitmap.h"
struct MPoint
{
	float x;
	float y;
};
struct MSphere
{
	MPoint	vCenter;
	float	fRadius;
};
class MCollision
{
public:
	static bool RectInPt(RECT rt, POINT pt);
	static bool RectInRect(RECT src, RECT dest);
	static bool SphereInPt(MSphere src, POINT pt);
	static bool SphereInSphere(MSphere src, MSphere dest);
};

