#pragma once

class Collision
{
public:
	static bool RectToPoint(const RECT& lhs, const POINT rhs) {
		return lhs.top <= rhs.y&& lhs.top + lhs.bottom >= rhs.y && lhs.left <= rhs.x&& lhs.left + lhs.right >= rhs.x;
	}
	//static bool RectToPoint(const RECT& lhs, const POINT rhs)
	//{
	//	if (lhs.left <= rhs.x && lhs.right >= rhs.x)
	//	{
	//		if (lhs.top <= rhs.y && lhs.bottom >= rhs.y)
	//		{
	//			return true;
	//		}
	//	}
	//	return false;
	//}
	static bool RectToPoint(const RECT& lhs, const Vector2D rhs) {
		return lhs.top <= rhs.y&& lhs.top >= rhs.y && lhs.left <= rhs.x&& lhs.right >= rhs.x;
	}
	static bool RectToHeight(const RECT& lhs, const RECT& rhs) {
		return RectToRect(lhs, rhs) && lhs.top + lhs.bottom <= rhs.top + 7;
	}
	static bool RectToRect(const RECT& lhs, const RECT& rhs) {
		return abs((lhs.left + lhs.right / 2) - (rhs.left + rhs.right / 2)) <= lhs.right / 2 + rhs.right / 2
			&& abs((lhs.top + lhs.bottom / 2) - (rhs.top + rhs.bottom / 2)) <= lhs.bottom / 2 + rhs.bottom / 2;
	}
};