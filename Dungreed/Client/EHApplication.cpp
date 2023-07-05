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

		Scene Enter;
		// Main Logo
		GameObject* MainLogo = new GameObject();
		MainLogo->GetComponent<Transform>()->SetPos(Math::Vector2<float>(320.f,140.f));
		MainLogo->GetComponent<Transform>()->SetScale(Math::Vector2<float>(635.f, 310.f));
		MainLogo->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
		MainLogo->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(156.f, 75.f));
		MainLogo->SetImagePath(L"D:\\C++\\API\\Dungreed_API\\Dungreed\\Client\\Resources\\EnterScene\\MainLogo.png");

		// Start
		GameObject* Start = new GameObject();
		Start->GetComponent<Transform>()->SetPos(Math::Vector2<float>(570.f, 490.f));
		Start->GetComponent<Transform>()->SetScale(Math::Vector2<float>(140.f, 42.f));
		Start->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
		Start->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(36.f, 12.f));
		Start->SetImagePath(L"D:\\C++\\API\\Dungreed_API\\Dungreed\\Client\\Resources\\EnterScene\\PlayOff_Kor.png");

		// Option
		GameObject* Option = new GameObject();
		Option->GetComponent<Transform>()->SetPos(Math::Vector2<float>(610.f, 537.f));
		Option->GetComponent<Transform>()->SetScale(Math::Vector2<float>(62.f, 42.f));
		Option->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
		Option->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(20.f, 12.f));
		Option->SetImagePath(L"D:\\C++\\API\\Dungreed_API\\Dungreed\\Client\\Resources\\EnterScene\\OptionOff_Kor.png");

		// Exit
		GameObject* Exit = new GameObject();
		Exit->GetComponent<Transform>()->SetPos(Math::Vector2<float>(610.f, 586.f));
		Exit->GetComponent<Transform>()->SetScale(Math::Vector2<float>(62.f, 42.f));
		Exit->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
		Exit->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(21.f, 12.f));
		Exit->SetImagePath(L"D:\\C++\\API\\Dungreed_API\\Dungreed\\Client\\Resources\\EnterScene\\ExitOff_Kor.png");

		// BackCloud
		GameObject* BackCloud = new GameObject();
		BackCloud->GetComponent<Transform>()->SetPos(Math::Vector2<float>(0.f, 0.f));
		BackCloud->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		BackCloud->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(160.f, 0.f));
		BackCloud->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(300.f, 180.f));
		BackCloud->SetImagePath(L"D:\\C++\\API\\Dungreed_API\\Dungreed\\Client\\Resources\\EnterScene\\BackCloud.png");

		// FrontCloud
		GameObject* FrontCloud = new GameObject();
		FrontCloud->GetComponent<Transform>()->SetPos(Math::Vector2<float>(0.f, 0.f));
		FrontCloud->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		FrontCloud->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(130.f, 0.f));
		FrontCloud->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(390.f, 180.f));
		FrontCloud->SetImagePath(L"D:\\C++\\API\\Dungreed_API\\Dungreed\\Client\\Resources\\EnterScene\\FrontCloud.png");

		Enter.SetLayer(enums::eLayerType::UI, BackCloud);
		Enter.SetLayer(enums::eLayerType::UI, FrontCloud);
		Enter.SetLayer(enums::eLayerType::UI, MainLogo);
		Enter.SetLayer(enums::eLayerType::UI, Start);
		Enter.SetLayer(enums::eLayerType::UI, Option);
		Enter.SetLayer(enums::eLayerType::UI, Exit);

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

		// 화면 clear
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
		// memdc를 통해 그린 bitmap을 메인 핸들로 옮기는 과정
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
