#pragma once
#include "EHScene.h"

namespace EH
{
	class JailScene : public Scene
	{
	public:
		JailScene();
		virtual ~JailScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
