#include "EHApplication.h"

namespace EH
{
	Application::Application()
		: mHwnd(nullptr)
		, mHdc(nullptr)
		, mPlayerPos(100.f,100.f)
	{
	}

	Application::~Application()
	{
	}

	void Application::Initialize(HWND hWnd)
	{
		mHwnd = hWnd;
		mHdc = GetDC(hWnd);
	}

	void Application::Run()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			mPlayerPos -= Vector2(5.f, 0.f);
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			mPlayerPos += Vector2(5.f, 0.f);
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			mPlayerPos -= Vector2(0.f, 5.f);
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			mPlayerPos += Vector2(0.f, 5.f);
		}
	}

	void Application::Render()
	{
		// 위치는 중점으로 생각하고 크기를 뺌 
		// 즉, 만들어진 사각형은 중점을 mPlayerPos로 잡은 크기가 가로 30 세로 30 짜리 사각형
		/*Rectangle(mHdc, mPlayerPos.x - 15.f, mPlayerPos.y - 15.f, mPlayerPos.x+15.f, mPlayerPos.y+15.f);*/

		// BackGround Color
		HPEN hNewPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(121, 185, 255));
		HPEN hOldPen = (HPEN)SelectObject(mHdc, hNewPen);

		HBRUSH hNewBrush = (HBRUSH)CreateSolidBrush(RGB(121, 185, 255));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(mHdc, hNewBrush);
		Rectangle(mHdc, 0, 0, 1920, 1080);

		SelectObject(mHdc, hOldPen);
		DeleteObject(hNewPen);
		SelectObject(mHdc, hOldBrush);
		DeleteObject(hNewBrush);
	}
}
