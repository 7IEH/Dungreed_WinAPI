#pragma once
#include "EHGameObject.h"

namespace EH
{
	class Npc : public GameObject
	{
	public:
		Npc();
		virtual ~Npc();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
	private:

	};
}
