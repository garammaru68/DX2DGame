#include "MCollision.h"

bool MCollision::RectInPt(RECT rt, POINT pt)
{
	if (rt.left <= pt.x && rt.right >= pt.x)
	{
		if (rt.top <= pt.y && rt.bottom >= pt.y)
		{
			return true;
		}
	}
	return false;
}

bool MCollision::RectInRect(RECT src, RECT dest)
{
	POINT cSrcCenter, cDestCenter;
	cSrcCenter.x = (src.left + src.right) / 2;
	cSrcCenter.y = (src.top + src.bottom) / 2;
	cDestCenter.x = (dest.left + dest.right) / 2;
	cDestCenter.y = (dest.top + dest.bottom) / 2;

	POINT Distance;
	Distance.x = abs(cSrcCenter.x - cDestCenter.x);
	Distance.y = abs(cSrcCenter.y - cDestCenter.y);
	POINT RadiusSrc;
	POINT RadiusDest;
	RadiusSrc.x = src.right - cSrcCenter.x;
	RadiusSrc.y = src.bottom - cSrcCenter.y;
	RadiusDest.x = dest.right - cDestCenter.x;
	RadiusDest.y = dest.bottom - cDestCenter.y;
	if (Distance.x <= (RadiusSrc.x + RadiusDest.x) &&
		Distance.y <= (RadiusSrc.y + RadiusDest.y))
	{
		return true;
	}
	return false;
}

bool MCollision::SphereInPt(MSphere src, POINT pt)
{
	float fDistance = sqrt((src.vCenter.x - pt.x)*(src.vCenter.x - pt.x) +
							(src.vCenter.y - pt.y)*(src.vCenter.y - pt.y));
	if (src.fRadius < fDistance)
	{
		return false;
	}
	return true;
}

bool MCollision::SphereInSphere(MSphere src, MSphere dest)
{
	float fDistance = sqrt((src.vCenter.x - dest.vCenter.x)*(src.vCenter.x - dest.vCenter.x) +
							(src.vCenter.y - dest.vCenter.y)*(src.vCenter.y - dest.vCenter.y));
	if (src.fRadius + dest.fRadius < fDistance)
	{
		return false;
	}
	return true;
}
