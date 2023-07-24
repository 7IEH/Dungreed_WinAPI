#include "EHTime.h"

namespace EH
{
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};
	float Time::mDeltaTime = 0.f;

	void Time::Initialize()
	{
		// 현재 컴퓨터의 cpu 주기를 가져옴 -> 1초에 몇번 카운팅하는지 가져옴
		QueryPerformanceFrequency(&mCpuFrequency);

		// 프로그램이 작동하고 몇번 카운팅 했는지 셈
		QueryPerformanceCounter(&mPrevFrequency);
	}
	void Time::Update()
	{
		// 1번 frame이 지나갔을때 몇번 카운팅 했는지 셈
		QueryPerformanceCounter(&mCurFrequency);

		// 현재 카운팅과 전에 센 카운팅을 빼면 -> 1프레임이 지나갔을때 얼마나 카운팅 했는지 확인 가능
		float Difference = static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);

		// 카운팅된 수는 1frame동안 카운팅한 수임
		// mCpuFrequency는 현재 컴퓨터의 cpu의 1초 동안 몇번 카운팅하는지를 세놓은거임
		// 즉, 역수를 취하면 1카운팅 동안 몇초가 지났는지 알 수 있음
		// 즉, 1frame동안 카운팅한 수 * 1.f/mCpuFrequncy 하면 1frame 동안 지나간 초를 알 수 있게됨
		mDeltaTime = Difference / static_cast<float>(mCpuFrequency.QuadPart);

		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}
	void Time::Render(HDC hdc)
	{
		static float TimeCheck = 0.f;
		TimeCheck += mDeltaTime;

		if (TimeCheck >= 1.f)
		{
			wchar_t szFloat[50] = {};
			float fps = 1.0f / mDeltaTime;

			swprintf_s(szFloat, 50, L"FPS : %f", fps);
			int strLen = wcsnlen_s(szFloat, 50);


			TextOut(hdc, 10, 10, szFloat, strLen);
			TimeCheck = 0.f;
		}
	}
}