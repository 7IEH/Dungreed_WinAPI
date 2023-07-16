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
		// vector ������ �����ε�
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

		Vector2<T> operator/(float other)
		{
			Vector2<T> temp;
			temp.x = x / other;
			temp.y = y / other;
			return temp;
		}

		bool operator==(Vector2<T> other)
		{
			return (this->x == other.x) && (this->y == other.y);
		}
	};
}