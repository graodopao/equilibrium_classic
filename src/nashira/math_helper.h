#pragma once
#include <cmath>

namespace nashira {
	#define PI 3.14159265f
	#define DEG_TO_RAD (PI / 180.0f)

	struct Vector2
	{
		float x;
		float y;

		Vector2(float _x = 0.0f, float _y = 0.0f)
			: x(_x), y(_y) {}

		[[nodiscard]] float magnitude_squared() const {
			return x * x + y * y;
		}

		[[nodiscard]] float magnitude() const {
			return std::sqrt(x * x + y * y);
		}

		[[nodiscard]] Vector2 normalized() const {
			const float mag = magnitude();
			return {x / mag, y / mag};
		}

		Vector2& operator +=(const Vector2& rhs)
		{
			x += rhs.x;
			y += rhs.y;

			return *this;
		}

		Vector2& operator -=(const Vector2& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;

			return *this;
		}

	};

	inline Vector2 operator + (const Vector2& lhs, const Vector2& rhs)
	{
		return {lhs.x + rhs.x, lhs.y + rhs.y};
	}

	inline Vector2 operator - (const Vector2& lhs, const Vector2& rhs)
	{
		return {lhs.x - rhs.x, lhs.y - rhs.y};
	}

	inline Vector2 operator * (const Vector2& lhs, const float& rhs)
	{
		return {lhs.x * rhs, lhs.y * rhs};
	}

	inline Vector2 RotateVector(const Vector2& vec, const float angle)
	{
		const float rad_angle{ (float)(angle * DEG_TO_RAD) };
		return {static_cast<float>(vec.x * std::cos(rad_angle) - vec.y * std::sin(rad_angle)), static_cast<float>(vec.x * std::sin(rad_angle) + vec.y * std::cos(rad_angle))};
	}

	const Vector2 ZERO = { 0.0f, 0.0f };
	const Vector2 ONE = { 1.0f, 1.0f };
	const Vector2 UP = { 0.0f, 1.0f };
	const Vector2 DOWN = { 0.0f, -1.0f };
	const Vector2 RIGHT = { 1.0f, 0.0f };
}
