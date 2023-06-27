#pragma once
#include "Commoninclude.h"
using EH::Math::Vector2;

namespace EH
{
	class Application
	{
	public:
		Application();
		~Application();
		void Initialize(HWND hWnd);
		void Run();
		void Update();
		void Render();

	private:
		HWND mHwnd;
		HDC mHdc;

		// double buffering test
		HBITMAP mHbit;
		HDC mHmemdc;

		// update test
		Vector2 mPlayerPos;
	};
}

