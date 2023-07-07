#pragma once
#include "EHScene.h"
#include "EHImage.h"

namespace EH
{
	class TownScene : public Scene
	{
	public:
		TownScene();
		virtual ~TownScene();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;

	private:
	};
}

