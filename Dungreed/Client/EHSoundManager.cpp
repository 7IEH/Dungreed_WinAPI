#include "EHSoundManager.h"
#include "EHApplication.h"

extern EH::Application application;


namespace EH	
{
	LPDIRECTSOUND8 SoundManager::mSoundDevice;

	bool SoundManager::Initialize()
	{
		if (FAILED(DirectSoundCreate8(NULL, &mSoundDevice, NULL)))
		{
			MessageBox(NULL, L"�������̽���������", L"SYSTEM ERROR", MB_OK);
			return false;
		}

		// ���� ����̽� �������� ����.
		HWND hWnd = application.GetHWND();
		if (FAILED(mSoundDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag�� ����
		{
			MessageBox(NULL, L"�������̽� �������� ����", L"SYSTEM ERROR", MB_OK);
			return false;
		}

		return true;
	}
}