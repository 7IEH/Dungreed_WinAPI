#pragma once
#include "Commoninclude.h"
#include "EHGameObject.h"

namespace EH
{
	class BossHand : public GameObject
	{
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
	};
}
