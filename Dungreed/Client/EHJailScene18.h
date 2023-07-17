#pragma once
#include "EHScene.h"

namespace EH
{
	class JailScene18 : public Scene
	{
	public:
		JailScene18();
		virtual ~JailScene18();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}
