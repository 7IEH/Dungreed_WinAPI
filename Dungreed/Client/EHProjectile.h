#pragma once
#include "EHGameObject.h"

namespace EH
{
	class Projectile : public GameObject
	{
	public:
		Projectile();
		virtual ~Projectile();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetRadian(float radian) { mRadian = radian; }
		float GetRadian() { return mRadian; }

		void SetDamage(UINT damage) { mDamage = damage; }
		UINT GetDamage() { return mDamage; }

	private:
		float mRadian;
		UINT mDamage;
	};
}
