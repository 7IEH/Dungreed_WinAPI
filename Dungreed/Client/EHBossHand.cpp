#include "EHBossHand.h"
#include "EHBoss.h"

namespace EH
{
	BossHand::BossHand()
		:
		  mType(eAttack::None)
		, mIsRight(true)
		, mOwner(nullptr)
	{

	}

	BossHand::~BossHand()
	{

	}

	void BossHand::Initialize()
	{
	}

	void BossHand::Update()
	{
		GameObject::Update();

		switch (mType)
		{
		case EH::eAttack::Idle:
			Idle();
			break;
		case EH::eAttack::Attack:
			Attack();
			break;
		case EH::eAttack::None:
			break;
		default:
			break;
		}
	}

	void BossHand::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BossHand::Idle()
	{
		Transform* tr = GetComponent<Transform>();
		Animator* ani = GetComponent<Animator>();
		tr->SetScale(Math::Vector2<float>(228.f, 276.f));
		if (mIsRight)
		{
			ani->PlayAnimation(L"BossRightHandIdle",true);
		}
		else
		{
			ani->PlayAnimation(L"BossLeftHandIdle",true);
		}
		mType = eAttack::None;
	}

	void BossHand::Attack()
	{
		mCheck1 += Time::GetDeltaTime();

		if (2.f < mCheck1)
		{
			mOwner->SetCheck(mOwner->GetCheck() + 1);
			mType = eAttack::Idle;
			mCheck1 = 0.f;
		}
	}
}