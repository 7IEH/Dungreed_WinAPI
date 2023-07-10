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
		, pSound(0)
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

		// Sounde Test
		MCI_OPEN_PARMSA Data = {};
		MCIERROR Error = 0;
		std::string pathstr = "";
		std::wstring absPath = Path::GetPath();
		pathstr.assign(absPath.begin(), absPath.end());
		pathstr += "\\Resources\\Sound\\title.wav";

		Data.lpstrDeviceType = "WaveAudio";
		Data.lpstrElementName = pathstr.c_str();
		
		Error = mciSendCommandA(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)&Data);

		pSound = Data.wDeviceID;

		MCI_OPEN_PARMSA Play = {};
		//mciSendCommandA(pSound, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&Play);

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
		SceneManager::Update();
	}

	void Application::Render()
	{
		// 화면 clear
		Rectangle(mHmemdc, -1, -1, mWinSize.x+1, mWinSize.y+1);
		SceneManager::Render(mHmemdc);
		Time::Render(mHmemdc);
		// double buffering
		// memdc를 통해 그린 bitmap을 메인 핸들로 옮기는 과정
		BitBlt(mHdc, 0, 0, 1280, 720, mHmemdc, 0, 0, SRCCOPY);
	}
}
