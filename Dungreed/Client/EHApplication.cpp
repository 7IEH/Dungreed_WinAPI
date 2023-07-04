#include "EHApplication.h"

namespace EH
{
	Application::Application()
		: mHwnd(nullptr)
		, mHdc(nullptr)
		, mWinSize(0.f, 0.f)
		, mHbit(nullptr)
		, mHmemdc(nullptr)
		, mHinst(nullptr)
		, mPlayerPos(100.f, 500.f)
		, mBossPos(640.f, 300.f)
		, mAttackPos(940.f, 300.f)
	{
	}

	Application::~Application()
	{
		ReleaseDC(mHwnd, mHdc);
		DeleteDC(mHmemdc);
	}

	void Application::Initialize(HWND hWnd,HINSTANCE hInst)
	{
		mHwnd = hWnd;
		mHinst = hInst;
		mHdc = GetDC(hWnd);

		mWinSize.x = 1280.f;
		mWinSize.y = 720.f;
		RECT rt = {0,0,mWinSize.x, mWinSize.y };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(hWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(hWnd, true);
		// Time Initialize
		Time::Initialize();
		// Input Initialize
		Input::Initialize();

		// Double buffering을 위한 bitmap과 여분의 DC
		// 새로운 bitmap 조성
		mHbit = CreateCompatibleBitmap(mHdc, 1280, 720);
		// DC는 만들어질때 DEFAULT 값으로 1pixel의 bitmap을 가짐
		// 현재 window의 dc가 활용하는 cpu, gpu를 활용하는 다른 dc를 만듬
		// 이는 현재 window의 handle dc가 아니기 때문에 이 dc를 통해 그려도 화면상에 보이지 않음
		// 이는 window의 main dc와 다르게 releasedc가 아닌 deletedc를 통해서만 해제가 가능
		mHmemdc = CreateCompatibleDC(mHdc);

		// 만든 bitmap 위에서 dc를 활용할 수 있게 설정
		// brush, pen 을 설정할때와 마찬가지로 기존에 dc가 가지고 있던 bitmap은 뱉어낸다.
		HBITMAP hOldBit = (HBITMAP)SelectObject(mHmemdc, mHbit);
		// 아까말한 1pixel bitmap 파괴
		DeleteObject(hOldBit);
	}

	void Application::Run()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		// Input test
		Time::Update();
		Input::Update();
		if (Input::Getkey(eKeyCode::A).state == eKeyState::PRESSED)
		{
			mPlayerPos.x -= 300.f * Time::GetDeltaTime();
		}

		if (Input::Getkey(eKeyCode::S).state == eKeyState::PRESSED)
		{
			mPlayerPos.y += 300.f * Time::GetDeltaTime();
		}

		if (Input::Getkey(eKeyCode::W).state == eKeyState::PRESSED)
		{
			mPlayerPos.y -= 300.f * Time::GetDeltaTime();
		}

		if (Input::Getkey(eKeyCode::D).state == eKeyState::PRESSED)
		{
			mPlayerPos.x += 300.f * Time::GetDeltaTime();
		}		


		/*if(mAttackPos.x>=340.f&&mAttackPos.y >= 300.f)
		{
			double temp = (double)90000.f - (double)((mAttackPos.x - 640.f) * (mAttackPos.x - 640.f));
			if (temp < 0)
			{
				temp *= -1;
			}
			mAttackPos.y = (double)sqrt(temp) + 300.f;
			mAttackPos.x -= 0.5f;
		}
		else if (mAttackPos.x >= 339.5f&& mAttackPos.y <= 300.f)
		{
			mAttackPos.x += 0.5f;
			if (mAttackPos.x == 940.5f)
			{
				mAttackPos.x -= 0.5f;
			}
			mAttackPos.y = -1 * (double)sqrt((double)90000.f - (double)((mAttackPos.x - 640.f) * (mAttackPos.x - 640.f))) + 300.f;
			if (mAttackPos.x == 940.f)
			{
				mAttackPos.y = 300.5f;
			}
			mAttackPos.y -= 0.1f;
		}*/
	}

	void Application::Render()
	{
		// BackGround Color
		HPEN hNewPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(121, 185, 255));
		HPEN hOldPen = (HPEN)SelectObject(mHmemdc, hNewPen);

		HBRUSH hNewBrush = (HBRUSH)CreateSolidBrush(RGB(121, 185, 255));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(mHmemdc, hNewBrush);

		// 화면 clear
		Rectangle(mHmemdc, -1, -1, mWinSize.x+1, mWinSize.y+1);
		Time::Render(mHmemdc);

		SelectObject(mHmemdc, hOldPen);
		DeleteObject(hNewPen);
		SelectObject(mHmemdc, hOldBrush);
		DeleteObject(hNewBrush);

		//// 위치는 중점으로 생각하고 크기를 뺌 
		//// 즉, 만들어진 사각형은 중점을 mPlayerPos로 잡은 크기가 가로 30 세로 30 짜리 사각형
		///*Rectangle(mHmemdc, mPlayerPos.x - 15.f, mPlayerPos.y - 15.f, mPlayerPos.x + 15.f, mPlayerPos.y + 15.f);*/
		//
		//// MAIN LOGO, PLAY, OPTION, EXIT 1280 760
		Rectangle(mHmemdc, 320, 140, 955, 450);
		CreateWindow(L"button", L"Start", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 570, 490, 140, 42, mHwnd, (HMENU)0, mHinst, NULL);
		CreateWindow(L"button", L"Option", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 610, 537, 62, 42, mHwnd, (HMENU)0, mHinst, NULL);
		CreateWindow(L"button", L"Exit", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 610, 586, 62, 42, mHwnd, (HMENU)0, mHinst, NULL);

		//Rectangle(mHmemdc, (int)mPlayerPos.x, (int)mPlayerPos.y, (int)(mPlayerPos.x+100.f), (int)(mPlayerPos.y + 100.f));


		//Ellipse(mHmemdc, (int)(mBossPos.x - 150.f), (int)(mBossPos.y - 150.f), (int)(mBossPos.x + 150.f), (int)(mBossPos.y + 150.f));

		//Ellipse(mHmemdc, (int)(mAttackPos.x - 30), (int)(mAttackPos.y - 30.f), (int)(mAttackPos.x + 30.f), (int)(mAttackPos.y + 30.f));

		// double buffering
		// memdc를 통해 그린 bitmap을 메인 핸들로 옮기는 과정
		BitBlt(mHdc, 0, 0, 1280, 720, mHmemdc, 0, 0, SRCCOPY);
	}
}
