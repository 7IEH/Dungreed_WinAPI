#pragma once
#include "EHScene.h"

namespace EH
{
	class JailBossScene : public Scene
	{
	public:
		JailBossScene();
		virtual ~JailBossScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		UINT mIntro;

		float mCheckTime;
		class Sound* mBelialLaugh;
	};
}

