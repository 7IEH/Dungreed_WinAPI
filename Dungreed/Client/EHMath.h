#pragma once
#include <cmath>

namespace EH::Math
{
	template <typename T>
	struct Vector2
	{
		T x;
		T y;

		Vector2(T x = 0,T y = 0)
			: x(x)
			, y(y)
		{
		}

		template <typename T>
		// vector 연산자 오버로딩
		Vector2<T>& normalized()
		{
			x /= sqrt((float)x * (float)x + (float)y * (float)y);
			y /= sqrt((float)x * (float)x + (float)y * (float)y);
			return *this;
		}

		T lengh()
		{
			return sqrt(x * x + y * y);
		}

		Vector2<T> operator+(Vector2<T> other)
		{
			Vector2<T> temp;
			temp.x = x + other.x;
			temp.y = y + other.y;
			return temp;
		}

		Vector2<T> operator-(Vector2<T> other)
		{
			Vector2<T> temp;
			temp.x = x - other.x;
			temp.y = y - other.y;
			return temp;
		}

		Vector2<T>& operator+=(Vector2<T> other)
		{
			x += other.x;
			y += other.y;

			return *this;
		}

		Vector2<T>& operator-=(Vector2<T> other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}

		Vector2<T> operator/(float other)
		{
			Vector2<T> temp;
			temp.x = x / other;
			temp.y = y / other;
			return temp;
		}

		Vector2<T>& operator*(float other)
		{
			x *= other;
			y *= other;
			return *this;
		}

		Vector2<T> operator-()
		{
			Vector2<T> temp;
			temp.x = x * -1;
			temp.y = y * -1;
			return temp;
		}

		bool operator==(Vector2<T> other)
		{
			return (this->x == other.x) && (this->y == other.y);
		}
	};
}