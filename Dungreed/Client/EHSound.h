#pragma once
#include "EHResource.h"

namespace EH
{
	class Sound : public Resource
	{
	public:
		virtual HRESULT Load() override;

		void Play();
		void Stop();
		void SetVolume(int volume);

	private:
		MCIDEVICEID  mSoundBuffer;
	};
}

