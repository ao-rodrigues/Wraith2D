#pragma once

#include <iostream>
#include <stdlib.h>

constexpr float EPSILON = 0.00001f;

struct Vector2
{
	float x;
	float y;

	/// <summary>
	/// Creates a Vector2 with x and y set to 0
	/// </summary>
	Vector2()
	{
		this->x = 0.f;
		this->y = 0.f;
	}

	/// <summary>
	/// Creates a new Vector2
	/// </summary>
	/// <param name="x">X value</param>
	/// <param name="y">Y value</param>
	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	inline Vector2 operator+(const Vector2& v2) const
	{
		return Vector2(x + v2.x, y + v2.y);
	}

	inline Vector2 operator+(float v) const
	{
		return Vector2(x + v, y + v);
	}

	inline Vector2 operator-(const Vector2& v2) const
	{
		return Vector2(x - v2.x, y - v2.y);
	}

	inline Vector2 operator-(float v) const
	{
		return Vector2(x - v, y - v);
	}

	inline Vector2 operator*(const Vector2& v2) const
	{
		return Vector2(x * v2.x, y * v2.y);
	}

	inline Vector2 operator*(float v) const
	{
		return Vector2(x * v, y * v);
	}

	inline Vector2 operator/(const Vector2& v2) const
	{
		return Vector2(x / v2.x, y / v2.y);
	}

	inline Vector2 operator/(float v) const
	{
		return Vector2(x / v, y / v);
	}

	inline bool operator==(const Vector2& v2) const
	{
		return (abs(x - v2.x) <= EPSILON) && (abs(y - v2.y) <= EPSILON);
	}

	inline bool operator!=(const Vector2& v2) const
	{
		return (abs(x - v2.x) > EPSILON) || (abs(y - v2.y) > EPSILON);
	}

	inline friend Vector2& operator+=(Vector2& v1, const Vector2& v2)
	{
		v1.x += v2.x;
		v1.y += v2.y;
		return v1;
	}

	inline friend Vector2& operator+=(Vector2& v1, float v)
	{
		v1.x += v;
		v1.y += v;
		return v1;
	}

	inline friend Vector2& operator-=(Vector2& v1, const Vector2& v2)
	{
		v1.x -= v2.x;
		v1.y -= v2.y;

		return v1;
	}

	inline friend Vector2& operator-=(Vector2& v1, float v)
	{
		v1.x -= v;
		v1.y -= v;

		return v1;
	}

	inline friend Vector2& operator*=(Vector2& v1, const Vector2& v2)
	{
		v1.x *= v2.x;
		v1.y *= v2.y;
		return v1;
	}

	inline friend Vector2& operator*=(Vector2& v1, float v)
	{
		v1.x *= v;
		v1.y *= v;
		return v1;
	}

	inline friend Vector2& operator/=(Vector2& v1, const Vector2& v2)
	{
		v1.x /= v2.x;
		v1.y /= v2.y;
		return v1;
	}

	inline friend Vector2& operator/=(Vector2& v1, float v)
	{
		v1.x /= v;
		v1.y /= v;
		return v1;
	}

	inline friend std::ostream& operator<<(std::ostream& stream, const Vector2& v)
	{
		stream << "(" << v.x << "," << v.y << ")";
		return stream;
	}

	/// <summary>
	/// Calculates a linearly-interpolated Vector2 between two vectors
	/// </summary>
	/// <param name="start">The initial vector</param>
	/// <param name="dest">The final vector</param>
	/// <param name="t">The interpolation ratio</param>
	/// <returns></returns>
	inline static Vector2 lerp(Vector2 start, Vector2 dest, float t)
	{
		Vector2 result;
		result.x = start.x + (dest.x - start.x) * t;
		result.y = start.y + (dest.y - start.y) * t;

		return result;
	}

	/// <summary>
	/// Returns a unit vector with coordinates (0,1).
	/// </summary>
	/// <returns>Unit vector pointing down.</returns>
	inline static Vector2 down()
	{
		return Vector2(0.f, 1.f);
	}

	/// <summary>
	/// Returns a unit vector with coordinates (0,-1).
	/// </summary>
	/// <returns>Unit vector pointing up.</returns>
	inline static Vector2 up()
	{
		return Vector2(0.f, -1.f);
	}

	/// <summary>
	/// Returns a unit vector with coordinates (-1,0)
	/// </summary>
	/// <returns>Unit vector pointing left.</returns>
	inline static Vector2 left()
	{
		return Vector2(-1.f, 0.f);
	}

	/// <summary>
	/// Returns a unit vector with coordinates (1,0).
	/// </summary>
	/// <returns>Unit vector pointing right.</returns>
	inline static Vector2 right()
	{
		return Vector2(1.f, 0.f);
	}
};