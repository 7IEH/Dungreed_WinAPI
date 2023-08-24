#pragma once
#include "EHScene.h"

namespace EH
{
	class EndingScene : public Scene
	{
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		class BackGround* mMount1;
		class BackGround* mMount2;

		class BackGround* mBG1;
		class BackGround* mBG2;

		class BackGround* mLogo;
		float mCheck1;

		BackGround* mBG3;
		BackGround* mThankyou;

		float mCheck2;
		float mCheck3;
	};
}


