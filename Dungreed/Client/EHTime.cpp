#include "EHTime.h"

namespace EH
{
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};
	float Time::mDeltaTime = 0.f;

	void Time::Initialize()
	{
		// ���� ��ǻ���� cpu �ֱ⸦ ������ -> 1�ʿ� ��� ī�����ϴ��� ������
		QueryPerformanceFrequency(&mCpuFrequency);

		// ���α׷��� �۵��ϰ� ��� ī���� �ߴ��� ��
		QueryPerformanceCounter(&mPrevFrequency);
	}
	void Time::Update()
	{
		// 1�� frame�� ���������� ��� ī���� �ߴ��� ��
		QueryPerformanceCounter(&mCurFrequency);

		// ���� ī���ð� ���� �� ī������ ���� -> 1�������� ���������� �󸶳� ī���� �ߴ��� Ȯ�� ����
		float Difference = static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);

		// ī���õ� ���� 1frame���� ī������ ����
		// mCpuFrequency�� ���� ��ǻ���� cpu�� 1�� ���� ��� ī�����ϴ����� ����������
		// ��, ������ ���ϸ� 1ī���� ���� ���ʰ� �������� �� �� ����
		// ��, 1frame���� ī������ �� * 1.f/mCpuFrequncy �ϸ� 1frame ���� ������ �ʸ� �� �� �ְԵ�
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