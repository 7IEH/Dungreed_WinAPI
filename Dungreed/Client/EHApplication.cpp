#include "EHApplication.h"

namespace EH
{
	Application::Application()
		: mHwnd(nullptr)
		, mHdc(nullptr)
		, mPlayerPos(100.f,100.f)
		, mHbit(nullptr)
		, mHmemdc(nullptr)
	{
	}

	Application::~Application()
	{
	}

	void Application::Initialize(HWND hWnd)
	{
		mHwnd = hWnd;
		mHdc = GetDC(hWnd);

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
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			mPlayerPos -= Vector2(1.f, 0.f);
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			mPlayerPos += Vector2(1.f, 0.f);
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			mPlayerPos -= Vector2(0.f, 1.f);
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			mPlayerPos += Vector2(0.f, 1.f);
		}
	}

	void Application::Render()
	{
		// BackGround Color
		HPEN hNewPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(121, 185, 255));
		HPEN hOldPen = (HPEN)SelectObject(mHmemdc, hNewPen);

		HBRUSH hNewBrush = (HBRUSH)CreateSolidBrush(RGB(121, 185, 255));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(mHmemdc, hNewBrush);

		// 화면 clear
		Rectangle(mHmemdc, 0, 0, 1280, 720);

		SelectObject(mHmemdc, hOldPen);
		DeleteObject(hNewPen);
		SelectObject(mHmemdc, hOldBrush);
		DeleteObject(hNewBrush);

		// 위치는 중점으로 생각하고 크기를 뺌 
		// 즉, 만들어진 사각형은 중점을 mPlayerPos로 잡은 크기가 가로 30 세로 30 짜리 사각형
		Rectangle(mHmemdc, mPlayerPos.x - 15.f, mPlayerPos.y - 15.f, mPlayerPos.x + 15.f, mPlayerPos.y + 15.f);

		// double buffering
		// memdc를 통해 그린 bitmap을 메인 핸들로 옮기는 과정
		BitBlt(mHdc, 0, 0, 1280, 720, mHmemdc, 0, 0, SRCCOPY);
	}
}
