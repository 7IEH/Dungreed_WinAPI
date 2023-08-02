#pragma once
#include "Commoninclude.h"
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

		HDC GetMainDC() { return mHdc; }
		Vector2<int> GetWinSize(){ return mWinSize; }

		HWND GetHWND() { return mHwnd; }

		// Player UI Access Funtion
		void SetActiveUI(bool active) { mbActiveUI = active; }

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

		// Player UI
		bool mbActiveUI;
	};
}

