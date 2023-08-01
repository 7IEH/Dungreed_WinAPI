#pragma once
#include "EHGameObject.h"


namespace EH
{
	class Weapon : public GameObject
	{
	public:
		enum class eWeaponType
		{
			  Sword
			, Gun
			, Bow
			, None
		};

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		
		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetWeaponType(eWeaponType type) { mType = type; }
		eWeaponType GetWeaponType() { return mType; }

		void SetDelayTime(float delaytime) { mDelayTime = delaytime; }
		float GetDelayTime() { return mDelayTime; }

	private:
		eWeaponType mType;
		float mDelayTime;
	};
}

