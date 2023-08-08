#pragma once
#include "EHEnemy.h"

namespace EH
{
	class RedGiantBat : public Enemy
	{
	public:
		RedGiantBat();
		virtual ~RedGiantBat();

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

		float mRadian[20];
		float mTargetRadian;
		class Bullet* mBullet[20];
		bool mIsRight;

		UINT mCheck1;

		class Sound* mAttackSound;
	};
}

