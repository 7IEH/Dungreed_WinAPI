#include "EHApplication.h"
#include "EHSceneManager.h"

namespace EH
{
	Application::Application()
		: mHwnd(nullptr)
		, mHdc(nullptr)
		, mWinSize(0, 0)
		, mHbit(nullptr)
		, mHmemdc(nullptr)
		, mHinst(nullptr)
		, gdiplusToken(0)
		, gdiplusStartupInput{}
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
		Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);


		mWinSize.x = 1280;
		mWinSize.y = 720;
		RECT rt = {0,0,mWinSize.x, mWinSize.y };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(hWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(hWnd, true);
		// Time Initialize
		Time::Initialize();
		// Input Initializes
		Input::Initialize();

		// Path Initialize
		Path::Initialize();

		// SceneMgr Initialize
		SceneManager::Initialize();

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
		// Input test
		Time::Update();
		Input::Update();
		SceneManager::Update();
	}

	void Application::Render()
	{
		// ȭ�� clear
		Rectangle(mHmemdc, -1, -1, mWinSize.x+1, mWinSize.y+1);
		SceneManager::Render(mHmemdc);
		Time::Render(mHmemdc);
		// double buffering
		// memdc�� ���� �׸� bitmap�� ���� �ڵ�� �ű�� ����
		BitBlt(mHdc, 0, 0, 1280, 720, mHmemdc, 0, 0, SRCCOPY);
	}
}
