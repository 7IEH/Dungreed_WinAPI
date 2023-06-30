#pragma once
#include "Commoninclude.h"
#include "EHInput.h"
#include "EHTime.h"
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

		// double buffering test
		HBITMAP mHbit;
		HDC mHmemdc;

		// update test
		Vector2 mPlayerPos;
		Vector2 mBossPos;
		Vector2 mAttackPos;
	};
}

