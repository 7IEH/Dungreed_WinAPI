#pragma once
#include "EHEnemy.h"

namespace EH
{
	class Niflheim : public Enemy
	{
	public:
		Niflheim();
		virtual ~Niflheim();

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
		// Enter
		UINT mEnter;

	};
}

