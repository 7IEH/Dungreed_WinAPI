#include "EHApplication.h"

namespace EH
{
	Application::Application()
		: mHwnd(nullptr)
		, mHdc(nullptr)
		, mPlayerPos(100.f,100.f)
		, mHbit(nullptr)
		, mHmemdc(nullptr)
		, mHinst(nullptr)
	{
	}

	Application::~Application()
	{
	}

	void Application::Initialize(HWND hWnd,HINSTANCE hInst)
	{
		mHwnd = hWnd;
		mHinst = hInst;
		mHdc = GetDC(hWnd);

		// Double buffering�� ���� bitmap�� ������ DC
		// ���ο� bitmap ����
		mHbit = CreateCompatibleBitmap(mHdc, 1280, 720);
		// DC�� ��������� DEFAULT ������ 1pixel�� bitmap�� ����
		// ���� window�� dc�� Ȱ���ϴ� cpu, gpu�� Ȱ���ϴ� �ٸ� dc�� ����
		// �̴� ���� window�� handle dc�� �ƴϱ� ������ �� dc�� ���� �׷��� ȭ��� ������ ����
		// �̴� window�� main dc�� �ٸ��� releasedc�� �ƴ� deletedc�� ���ؼ��� ������ ����
		mHmemdc = CreateCompatibleDC(mHdc);

		// ���� bitmap ������ dc�� Ȱ���� �� �ְ� ����
		// brush, pen �� �����Ҷ��� ���������� ������ dc�� ������ �ִ� bitmap�� ����.
		HBITMAP hOldBit = (HBITMAP)SelectObject(mHmemdc, mHbit);
		// �Ʊ�� 1pixel bitmap �ı�
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

		// ȭ�� clear
		Rectangle(mHmemdc, 0, 0, 1280, 760);

		SelectObject(mHmemdc, hOldPen);
		DeleteObject(hNewPen);
		SelectObject(mHmemdc, hOldBrush);
		DeleteObject(hNewBrush);

		// ��ġ�� �������� �����ϰ� ũ�⸦ �� 
		// ��, ������� �簢���� ������ mPlayerPos�� ���� ũ�Ⱑ ���� 30 ���� 30 ¥�� �簢��
		/*Rectangle(mHmemdc, mPlayerPos.x - 15.f, mPlayerPos.y - 15.f, mPlayerPos.x + 15.f, mPlayerPos.y + 15.f);*/
		
		// MAIN LOGO, PLAY, OPTION, EXIT 1280 760
		Rectangle(mHmemdc, 320, 140, 955, 450);
		CreateWindow(L"button", L"Start", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 570, 490, 140, 42, mHwnd, (HMENU)0, mHinst, NULL);
		CreateWindow(L"button", L"Option", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 610, 537, 62, 42, mHwnd, (HMENU)0, mHinst, NULL);
		CreateWindow(L"button", L"Exit", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 610, 586, 62, 42, mHwnd, (HMENU)0, mHinst, NULL);

		// double buffering
		// memdc�� ���� �׸� bitmap�� ���� �ڵ�� �ű�� ����
		BitBlt(mHdc, 0, 0, 1280, 720, mHmemdc, 0, 0, SRCCOPY);
	}
}
