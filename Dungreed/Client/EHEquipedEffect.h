#pragma once
#include "EHGameObject.h"

namespace EH
{
	class EquipedEffect : public GameObject
	{
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetDeleteTime(float deletetime) { mDeletetime = deletetime; }

	private:
		float mDeletetime;
		float mCheckTime;
	};
}


