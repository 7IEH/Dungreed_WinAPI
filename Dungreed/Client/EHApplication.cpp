#include "EHApplication.h"
#include "EHSceneManager.h"
#include "EHCamera.h"
#include "EHCollisionManager.h"
#include "EHSoundManager.h"
#include "EHInput.h"
#include "EHTime.h"
#include "EHScene.h"
#include "EHPath.h"
#include "EHObjdata.h"

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

		// objdata FILE IN & OUT
		Objdata::SetMaxHP(80);
		Objdata::SetHP(80);
		Objdata::SetGold(0);
		Objdata::SetFood(0);
		Objdata::SetLevel(1);
		Objdata::SetDash(5);

		// Time Initialize
		Time::Initialize();
		// Input Initializes
		Input::Initialize();

		// Path Initialize
		Path::Initialize();

		// Sound Initialize
		SoundManager::Initialize();

		// Camera
		Camera::Initialize();

		// SceneMgr Initialize
		SceneManager::Initialize();

		// collision Initialize
		CollisionManager::Initialize();

		mHbit = CreateCompatibleBitmap(mHdc, 1280, 720);
		mHmemdc = CreateCompatibleDC(mHdc);
		HBITMAP hOldBit = (HBITMAP)SelectObject(mHmemdc, mHbit);
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
		Camera::Update();
		CollisionManager::Update();
		SceneManager::Update();
	}

	void Application::Render()
	{
		// 화면 clear
		Rectangle(mHmemdc, -1, -1, mWinSize.x+1, mWinSize.y+1);

		SceneManager::Render(mHmemdc);

		Time::Render(mHmemdc);

		CollisionManager::Render(mHmemdc);
		// double buffering
		// memdc를 통해 그린 bitmap을 메인 핸들로 옮기는 과정
		BitBlt(mHdc, 0, 0, 1280, 720, mHmemdc, 0, 0, SRCCOPY);
	}
}
