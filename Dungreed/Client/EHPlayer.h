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
		, Skill
		, Die
		, End
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
		void Swap();
		void Inventory();
		void Playerlogic();
		void Skill();

		// Acess function
		bool GetDir() { return mIsRight; }
		void ResetJumpStack() { mJumpStack = 0; }

		void SetSlope(bool slope) { mIsSlope = slope; }
		void SetRightSlope(bool right) { mIsRightSlope = right; }

		void SetTrans(bool trans) { Trans = trans; }

		void SetState(eAnimationState state) { mCurState = state; }

	private:
		int mMaxHP;
		UINT mLevel;
		UINT mCurHp;
		UINT mGold;
		UINT mFood;
		UINT mMaxDash;
		UINT mCurDash;

		bool Trans;

		eAnimationState mCurState;
		class BackGround* mHp;
		class Canvas* mCanvas;

		// Weapon, sub
		class Weapon* mWeapon;
		bool mIsSwing;
		enums::eWeapon mActiveWeapon;
		enums::eWeapon mSubWeapon;
		class Weapon* mWeaponCollider;

		bool mIsRight;
		bool mIsDead;
		bool mIsSlope;
		bool mIsJump;
		bool mIsRightSlope;
		bool mIsAttack;

		bool mOnBlock;
		UINT mJumpStack;

		// Attack Delay
		float mCheckTime;

		// Player Sound
		class Sound* mSound;
		class Sound* mOpeninventorysound;
		class Sound* mWandSound;
		class Sound* mGunSound;
		class Sound* mWandSkillSound;
		class Sound* mTwoHandSkillSound;
		class Sound* mSwapSound;

		// Player Inventory
		std::wstring mInventory[3][5];
		bool mOpeninventory;
		bool mClicked;
		std::wstring mClickedName;

		static UINT mCheck1;

		UINT mInventory1;

		// UI
		GameObject* mCurhpImage1;
		GameObject* mCurhpImage2;

		GameObject* mMaxhpImage1;
		GameObject* mMaxhpImage2;

		GameObject* mGoldt;
		GameObject* mGoldh;

		GameObject* mGoldten;
		GameObject* mGoldone;

		// Dust
		GameObject* mDust;

		// Dash Time
		float mDashTime;
	};
}
