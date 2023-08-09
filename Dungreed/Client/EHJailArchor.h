#pragma once
#include "EHEnemy.h"

namespace EH
{
	class JailArchor : public Enemy
	{
	public:
		JailArchor();
		virtual ~JailArchor();

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
		class Weapon* mBow;
		Texture* mBowImg;
		Texture* mBowAttackImg;
		class Weapon* mAttack;
		class Detection* mDect;
		
		class Sound* mBowDrawSound;
		class Sound* mBowAttackSound;

		bool mIsRight;
		float mBowradian;

		static UINT mBowCount;
	};
}
