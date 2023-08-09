#pragma once
#include "EHEnemy.h"

namespace EH
{
	class Banshee : public Enemy
	{
	public:
		Banshee();
		virtual ~Banshee();

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
		class Weapon* mAttack;
		class Sound* mprevAttackSound;
		class Sound* mAttackSound;

		UINT mCheck1;
	};
}

