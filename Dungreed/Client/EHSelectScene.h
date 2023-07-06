#pragma once
#include "EHScene.h"

namespace EH
{
	class SelectScene : public Scene
	{
	public:
		SelectScene();
		virtual ~SelectScene();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void Render(HDC hdc)override;

	private:

	};
}
