#pragma once

namespace EH::Math
{
	struct Vector2
	{
		float x;
		float y;

		Vector2()
			: x(0.f)
			, y(0.f)
		{

		}


		Vector2(float x, float y)
			: x(x)
			, y(y)
		{

		}


		// vector 연산자 오버로딩
		Vector2 operator+(Vector2 other)
		{
			Vector2 temp;
			temp.x = x + other.x;
			temp.y = y + other.y;
			return temp;
		}

		Vector2 operator-(Vector2 other)
		{
			Vector2 temp;
			temp.x = x - other.x;
			temp.y = y - other.y;
			return temp;
		}

		void operator+=(Vector2 other)
		{
			x += other.x;
			y += other.y;
		}

		void operator-=(Vector2 other)
		{
			x -= other.x;
			y -= other.y;
		}
	};
}