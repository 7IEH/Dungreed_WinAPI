#pragma once

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
		Vector2<T> operator+(Vector2<T> other)
		{
			Vector2 temp;
			temp.x = x + other.x;
			temp.y = y + other.y;
			return temp;
		}

		Vector2<T> operator-(Vector2<T> other)
		{
			Vector2 temp;
			temp.x = x - other.x;
			temp.y = y - other.y;
			return temp;
		}

		void operator+=(Vector2<T> other)
		{
			x += other.x;
			y += other.y;
		}

		void operator-=(Vector2<T> other)
		{
			x -= other.x;
			y -= other.y;
		}
	};
}