#pragma once
#include "Commoninclude.h"
#include "EHBossHand.h"
#include "EHEnemy.h"

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

	class Boss : public Enemy
	{
	public:
		Boss();
		virtual ~Boss();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		// Boss State(FSM) Function
		void Idle();
		void Attack();
		void Dead();

		// Boss Pattern Function
		void OneLaser();
		void ThreeLaser();
		void Sword();
		void Barrage();

		void SetTarget(class Player* target) { mTarget = target; }

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetStop(bool stop) { mIsStop = stop; }

		void SetCheck(UINT check) { mCheck2 = check; }
		UINT GetCheck() { return mCheck2; }

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
		float mSubCheckTime2;
		float mSubCheckTime3;

		// Check Variable
		UINT mCheck1;
		UINT mCheck2;
		UINT mCheck3;
		UINT mCheck4;

		float mMove;

		// Laser
		bool mRightLaserani;
		bool mLeftLaserani;

		// Right,Left
		float mIsRight;

		// Sword Group
		class Bullet* mSwordNameGroup[6];
		UINT mSwordNumbering;
		UINT mSwordAttack;

		// Sound
		class Sound* mSpawnSword;
		class Sound* mLaserSound;
		class Sound* mDefeatSound;
		class Sound* mExplosion;

		// Weapon Collider
		class Weapon* mAttack;

		// Boss UI
		class Canvas* mCanvas;

		// Back Particle
		GameObject* mBackparticle;

		// Boss Stop
		bool mIsStop;

		// Boss BulletCreator
		class BulletCreator* mBulletct[4];
	};
}

