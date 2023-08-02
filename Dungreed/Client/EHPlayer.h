#pragma once
#include "EHGameObject.h"

namespace EH
{
	enum class eAnimationState
	{
		  Idle
		, Move
		, Jump
		, Attack
		, Dash
		, DownJump
		, Die
		, End
	};

	enum class eWeapon
	{
		  Onehand
		, Twohand
		, Gun
		, None
	};

	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Idle();
		void Move();
		void Jump();
		void Attack();
		void Dash();
		void DownJump();
		void Die();
		void Playerlogic();

		// Acess function
		bool GetDir() { return mIsRight; }
		void ResetJumpStack() { mJumpStack = 0; }

		void SetSlope(bool slope) { mIsSlope = slope; }
		void SetRightSlope(bool right) { mIsRightSlope = right; }

		void SetCanvas(class Canvas* canvas) { mCanvas = canvas; }
		class Canvas* GetCanvas() { return mCanvas; }
	
	private:
		int mMaxHP;
		UINT mLevel;
		UINT mCurHp;
		UINT mGold;
		UINT mFood;
		UINT mMaxDash;
		UINT mCurDash;

		eAnimationState mCurState;
		eWeapon mActiveWeapon;
		class BackGround* mHp;
		class BackGround* mWeapon;
		class Weapon* mWeaponCollider;
		class Canvas* mCanvas;

		bool mIsSwing;
		bool mIsRight;
		bool mIsDead;
		bool mIsJump;
		bool mIsSlope;
		bool mIsRightSlope;
		bool mIsAttack;

		bool mOnBlock;
		UINT mJumpStack;

		// Attack Delay
		float mCheckTime;
	};
}
