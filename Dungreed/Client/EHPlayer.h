#pragma once
#include "EHGameObject.h"
#include "EHBackGround.h"

namespace EH
{
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		UINT mLevel;
		UINT mMaxHP;
		UINT mCurHp;
		UINT mGold;
		UINT mFood;
		BackGround* mHp;
		bool mIsRight;
		bool mIsDead;
	};
}
