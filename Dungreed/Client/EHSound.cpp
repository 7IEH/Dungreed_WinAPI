#include "EHSound.h"

namespace EH
{
	HRESULT Sound::Load()
	{
		MCI_OPEN_PARMSA Data = {};
		MCIERROR error = 0;
		Data.lpstrDeviceType = "WaveAudio";
		std::string temp = "";
		temp.assign(GetPath().begin(), GetPath().end());
		Data.lpstrElementName = temp.c_str();
		error = mciSendCommandA(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)&Data);
		if (error == 0)
		{
			mSoundBuffer = Data.wDeviceID;
			return S_OK;
		}

		return S_FALSE;
	}

	void Sound::Play()
	{
		MCI_OPEN_PARMSA Play = {};
		mciSendCommandA(mSoundBuffer, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&Play);
	}

	void Sound::Stop()
	{
	}

	void Sound::SetVolume(int volume)
	{
	}
}