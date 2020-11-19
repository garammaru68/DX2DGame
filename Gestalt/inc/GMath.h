#pragma once
#include <cmath>

class Vector2D
{
public:
	float x;
	float y;

	Vector2D() { x = 0, y = 0; }
	Vector2D(float x_in, float y_in) {
		x = x_in, y = y_in;
	}
	float length() const {
		return sqrt(x * x + y * y);
	}
	void Normalize() {
		*this = GetNormalized();
	}
	Vector2D GetNormalized() const {
		float len = length();
		if (len <= 0) return *this;
		return *this * (1.0f / len);
	}

	Vector2D operator+(const Vector2D& rhs) const {
		return Vector2D(x + rhs.x, y + rhs.y);
	}
	Vector2D& operator+=(const Vector2D& rhs) {
		return *this = *this + rhs;
	}
	Vector2D operator-(const Vector2D& rhs) const {
		return Vector2D(x - rhs.x, y - rhs.y);
	}
	Vector2D& operator-=(const Vector2D& rhs) {
		return *this = *this - rhs;
	}
	Vector2D operator*(const float rhs) const {
		return Vector2D(x * rhs, y * rhs);
	}
	Vector2D& operator*=(const float rhs) {
		return *this = *this * rhs;
	}
	Vector2D operator*(const Vector2D& rhs) const {
		return Vector2D(x * rhs.x, y * rhs.y);
	}
	Vector2D& operator*=(const Vector2D& rhs) {
		return *this = *this * rhs;
	}
};