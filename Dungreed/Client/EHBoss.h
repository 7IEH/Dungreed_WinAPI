#pragma once
#include "Commoninclude.h"
#include "EHBossHand.h"

namespace EH
{
	enum class eBossState
	{
		 Idle
		,Attack
		,Die
		,None
	};

	enum class eBossAttack
	{
		OneLaser,
		ThreeLaser,
		None,
	};

	class Boss : public GameObject
	{
	public:
		Boss();
		virtual ~Boss();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void Idle();
		void Attack();
		void Die();

		void OneLaser();
		void ThreeLaser();

		void SetTarget(class Player* target) { mTarget = target; }

	private:
		// Boss Parameter 
		BossHand* mLeftHand;
		BossHand* mRightHand;
		eBossState mCurState;
		eBossAttack mCurType;
		bool IsDead;

		// Target
		class Player* mTarget;

		// Test
		float mThinkTime;
		float mDelayTime;
		float mSubDelayTime;
		float mCheckTime;
	};
}

