#pragma once
#include "Commoninclude.h"
#include "EHGameObject.h"

namespace EH
{
	enum class eAttack
	{
		  Idle
		, Attack
		, None
	};

	class BossHand : public GameObject
	{
	public:
		BossHand();
		virtual ~BossHand();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void SetRight(bool right) { mIsRight = right; }
		void SetType(eAttack type) { mType = type; }

		void Idle();
		void Attack();

		void SetOwner(class Boss* owner) { mOwner = owner; }

	private:
		bool mIsRight;
		eAttack mType;

		// time
		float mCheck1;
		class Boss* mOwner;
	};
}
