#pragma once
#include "EHScene.h"

namespace EH
{
	class IceBossScene : public Scene
	{
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		float mCheckTime;
		UINT mIntro;
		UINT mCheck1;
		UINT mCheck3;
		Math::Vector2<float> mCheck2;
	};
}


