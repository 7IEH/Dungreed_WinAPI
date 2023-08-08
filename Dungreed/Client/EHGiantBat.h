#pragma once
#include "EHEnemy.h"

namespace EH
{
	class GiantBat : public Enemy
	{
	public:
		GiantBat();
		virtual ~GiantBat();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Idle();
		void Attack();
		void Dead();

	private:
		class Detection* mDect;
		class Weapon* mAttack;
		
		bool mIsRight;
		float mRadian;

		UINT mCheck1;

		class Sound* mAttackSound;
	};
}

