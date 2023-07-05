#include "EHApplication.h"

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

		Scene Enter;
		GameObject* player = new GameObject();
		Enter.SetLayer(enums::eLayerType::Player, player);
		mScene.push_back(Enter);
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

		for (Scene scene : mScene)
		{
			scene.Update();
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
		Rectangle(mHmemdc, -1, -1, mWinSize.x+1, mWinSize.y+1);
		Time::Render(mHmemdc);

		SelectObject(mHmemdc, hOldPen);
		DeleteObject(hNewPen);
		SelectObject(mHmemdc, hOldBrush);
		DeleteObject(hNewBrush);

		for (Scene scene : mScene)
		{
			scene.Render(mHmemdc);
		}

		// double buffering
		// memdc�� ���� �׸� bitmap�� ���� �ڵ�� �ű�� ����
		BitBlt(mHdc, 0, 0, 1280, 720, mHmemdc, 0, 0, SRCCOPY);
		// GDI+
		/*Image* image = Image::FromFile(L"D:\\C++\\API\\Dungreed_API\\Dungreed\\Client\\Resources\\EnterScene\\MainLogo.png");
		::Graphics g(mHmemdc);
		Image* image2 = Image::FromFile(L"D:\\C++\\API\\Dungreed_API\\Dungreed\\Client\\Resources\\EnterScene\\PlayOff_Kor.png");
		Image* image3 = Image::FromFile(L"D:\\C++\\API\\Dungreed_API\\Dungreed\\Client\\Resources\\EnterScene\\OptionOff_Kor.png");
		Image* image4 = Image::FromFile(L"D:\\C++\\API\\Dungreed_API\\Dungreed\\Client\\Resources\\EnterScene\\ExitOff_Kor.png");
		Image* image5 = Image::FromFile(L"D:\\C++\\API\\Dungreed_API\\Dungreed\\Client\\Resources\\EnterScene\\FrontCloud.png");
		Image* image6 = Image::FromFile(L"D:\\C++\\API\\Dungreed_API\\Dungreed\\Client\\Resources\\EnterScene\\BackCloud.png");


		g.DrawImage(image6, Gdiplus::Rect(0, 0, 1280, 720), 160, 0, 300, 180, UnitPixel);
		g.DrawImage(image5, Gdiplus::Rect(0, 0, 1280, 720), 130, 0, 390, 180, UnitPixel);
		g.DrawImage(image, Gdiplus::Rect(320, 140, 635, 310), 0, 0, 156, 75, UnitPixel);
		g.DrawImage(image2, 570, 490,140,42);
		g.DrawImage(image3, 610, 537,62,42);
		g.DrawImage(image4, 610, 586,62,42);*/
		
		//delete image;
	}
}
