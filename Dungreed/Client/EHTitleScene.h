#pragma once
#include "EHScene.h"

namespace EH
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		float mCheck1;

		class BackGround* mFrontcloud1;
		class BackGround* mFrontcloud2;
						  
		class BackGround* mBackcloud1;
		class BackGround* mBackcloud2;
	};
}

