#pragma once
#include "EHEnemy.h"

namespace EH
{
	class JailDog : public Enemy
	{
	public:
		JailDog();
		virtual ~JailDog();

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
		class Bullet* mBullet;
		class Weapon* mAttack;
		bool mIsRight;

		class Detection* mDect;
		UINT mCheck1;
	};
}


