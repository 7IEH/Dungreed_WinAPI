#pragma once
#include "Commoninclude.h"

namespace EH
{
	class GameManager
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

	private:
		static Canvas* mPlayerUI;
	};
}


