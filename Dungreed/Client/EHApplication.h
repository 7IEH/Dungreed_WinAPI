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
		void Initialize(HWND hWnd,HINSTANCE hInst);
		void Run();
		void Update();
		void Render();

	private:
		HWND mHwnd;
		HDC mHdc;
		HINSTANCE mHinst;

		// double buffering test
		HBITMAP mHbit;
		HDC mHmemdc;

		// update test
		Vector2 mPlayerPos;
	};
}

