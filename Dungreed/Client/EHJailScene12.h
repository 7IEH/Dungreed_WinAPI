#pragma once
#include "EHScene.h"

namespace EH
{
	class JailScene12 : public Scene
	{
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
