#pragma once
#include "Commoninclude.h"
#include "EHBossHand.h"

namespace EH
{
	enum class eBossState
	{
		  Idle
		, Attack
		, Die
		, None
	};

	enum class eBossAttack
	{
		  OneLaser
		, ThreeLaser
		, Sword
		, Barrage
		, None
	};

	class Boss : public GameObject
	{
	public:
		Boss();
		virtual ~Boss();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		// Boss State(FSM) Function
		void Idle();
		void Attack();
		void Die();

		// Boss Pattern Function
		void OneLaser();
		void ThreeLaser();
		void Sword();
		void Barrage();

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
		float mSubCheckTime;

		// Right,Left
		float mIsRight;

		// Sword Group
		class Bullet* mSwordNameGroup[6];
		UINT mSwordNumbering;

		// Sound
		class Sound* mSpawnSword;
	};
}

