#pragma once
#include "Commoninclude.h"
#include "EHInput.h"
#include "EHTime.h"
#include "EHScene.h"
#include "EHPath.h"
using EH::Math::Vector2;

// sound ¿ë
#pragma comment(lib,"winmm.lib")


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

		// double buffering
		HBITMAP mHbit;
		HDC mHmemdc;
		Vector2<int> mWinSize;

		// GDI+
		ULONG_PTR gdiplusToken;
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;

		// Direct Sound
		MCIDEVICEID pSound;
	};
}

