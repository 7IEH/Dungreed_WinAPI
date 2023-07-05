#pragma once
#include "Commoninclude.h"
#include "EHInput.h"
#include "EHTime.h"
#include "EHScene.h"
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

		void SetPos(int posX,int posY)
		{
			mPlayerPos.x = posX;
			mPlayerPos.y = posY;
		}

	private:
		HWND mHwnd;
		HDC mHdc;
		HINSTANCE mHinst;

		// double buffering
		HBITMAP mHbit;
		HDC mHmemdc;
		Vector2<int> mWinSize;

		// Scene
		std::vector<Scene> mScene;

		// update test
		Vector2<float> mPlayerPos;
		Vector2<float> mBossPos;
		Vector2<float> mAttackPos;

		// GDI+
		ULONG_PTR gdiplusToken;
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	};
}

