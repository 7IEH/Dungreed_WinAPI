#pragma once
#include "EHGameObject.h"
#include "EHBackGround.h"

namespace EH
{
	enum class eAnimationState
	{
		Idle,
		Move,
		Jump,
		Attack,
		Die,
		End
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
		void Die();

	private:
		UINT mLevel;
		UINT mMaxHP;
		UINT mCurHp;
		UINT mGold;
		UINT mFood;
		BackGround* mHp;
		bool mIsRight;
		bool mIsDead;
		eAnimationState mCurState;
		eWeapon mActiveWeapon;
		BackGround* mWeapon;
	};
}
