#pragma once
#include "EHGameObject.h"

namespace EH
{
	class DamageEffect : public GameObject
	{
	public:
		DamageEffect();
		virtual ~DamageEffect();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetDamage(int damage) { mDamage = damage; }

	private:
		int mDamage;
		UINT mCheck1;
		float mCheckTime;
	};
}


