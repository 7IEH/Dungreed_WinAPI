#pragma once
#include "EHEnemy.h"

namespace EH
{
	class BigGrayIceSkel : public Enemy
	{
	public:
		BigGrayIceSkel();
		virtual ~BigGrayIceSkel();

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
		class Bullet* mBullet;

		bool mIsRight;
		bool mIsSkill;

		UINT mCheck1;
	};
}


