#pragma once
#include "EHScene.h"

namespace EH
{
	class JailAfterBossScene : public Scene
	{
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
	};
}

