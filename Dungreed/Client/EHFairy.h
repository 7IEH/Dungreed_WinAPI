#pragma once
#include "EHGameObject.h"

namespace EH
{
	class Fairy : public GameObject
	{
	public:

		Fairy();
		virtual ~Fairy();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		// Access Function
		void SetHeal(UINT heal) { mHeal = heal; }

	private:
		UINT mHeal;

		class Sound* mEquipSound;
	};
}

