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

	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;


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
	};
}
