#pragma once
#include "EHScene.h"

namespace EH
{
	class JailPrevBossScene : public Scene
	{
	public:
		JailPrevBossScene();
		virtual ~JailPrevBossScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
	private:
	};
}
