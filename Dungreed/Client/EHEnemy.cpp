#include "EHEnemy.h"
#include "EHResources.h"
#include "EHSound.h"

namespace EH
{
	Enemy::Enemy()
		:
		   mDelayTime(0.f)
		 , mCheckTime(0.f)
		 , mSubDelayTime(0.f)
		 , mSubCheckTime(0.f)
		 , mCurState(eState::Idle)
		 , mTarget(nullptr)
	{
		mHitMonster = Resources::Load<Sound>(L"monsterhitsound", L"..\\Resources\\Sound\\Enemy\\public\\Hit_Monster.wav");
	}

	Enemy::~Enemy()
	{
	}

	void Enemy::Initialize()
	{
	}

	void Enemy::Update()
	{
		GameObject::Update();
	}

	void Enemy::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Enemy::OnCollisionEnter(Collider* other)
	{
	}

	void Enemy::OnCollisionStay(Collider* other)
	{
	}

	void Enemy::OnCollisionExit(Collider* other)
	{
	}
}
