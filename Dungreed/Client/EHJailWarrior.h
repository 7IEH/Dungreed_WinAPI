#pragma once
#include "EHEnemy.h"

namespace EH
{
	class JailWarrior : public Enemy
	{
	public:
		JailWarrior();
		virtual ~JailWarrior();

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

		class Weapon* mSword;
		class Bullet* mBullet;
		class Weapon* mAttack;

		bool mIsRight;
	};
}


