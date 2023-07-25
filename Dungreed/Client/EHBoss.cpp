#include "EHBoss.h"
#include "EHObject.h"
#include "EHSceneManager.h"
#include "EHResources.h"
#include "EHPlayer.h"
#include "EHComponent.h"
#include <time.h>


namespace EH
{
	Boss::Boss()
		:
		  mCurState(eBossState::Idle)
		, mCurType(eBossAttack::None)
		, mThinkTime(4.f)
		, mDelayTime(0.f)
		, mCheckTime(0.f)
		, mSubDelayTime(0.f)
		, mSubCheckTime(0.f)
		, mIsRight(true)
		, IsDead(false)
	{
		mLeftHand = object::Instantiate<BossHand>(enums::eLayerType::Enemy);
		Transform* tr = mLeftHand->GetComponent<Transform>();
		tr->SetPos(Math::Vector2<float>(370.f, 822.f));
		tr->SetScale(Math::Vector2<float>(228.f, 276.f));
		Texture* temp = Resources::Load<Texture>(L"BossLeftHandIdle", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\HandleLeft\\SkellBossLeftHandIdleSheet.bmp");
		mLeftHand->AddComponent<Animator>();
		mLeftHand->GetComponent<Animator>()->CreateAnimation(L"BossLeftHandIdle", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(57.f, 69.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		mLeftHand->GetComponent<Animator>()->PlayAnimation(L"BossLeftHandIdle", true);
		mLeftHand->GetComponent<Animator>()->SetAffectedCamera(true);

		mRightHand = object::Instantiate<BossHand>(enums::eLayerType::Enemy);
		tr = mRightHand->GetComponent<Transform>();
		tr->SetPos(Math::Vector2<float>(1106.f, 542.f));
		tr->SetScale(Math::Vector2<float>(228.f, 276.f));
		temp = Resources::Load<Texture>(L"BossRightHand", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\HandleRight\\SkellBossRightHandIdleSheet.bmp");
		mRightHand->AddComponent<Animator>();
		mRightHand->GetComponent<Animator>()->CreateAnimation(L"BossRightHand", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(57.f, 69.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		mRightHand->GetComponent<Animator>()->PlayAnimation(L"BossRightHand", true);
		mRightHand->GetComponent<Animator>()->SetAffectedCamera(true);

		SceneManager::GetCurScene()->SetLayer(enums::eLayerType::Enemy, mLeftHand);
		SceneManager::GetCurScene()->SetLayer(enums::eLayerType::Enemy, mRightHand);
	}

	Boss::~Boss()
	{
	}

	void Boss::Initialize()
	{
	}

	void Boss::Update()
	{
		GameObject::Update();

		// Hand Move
		switch (mCurState)
		{
		case EH::eBossState::Idle:
			Idle();
			break;
		case EH::eBossState::Attack:
			Attack();
			break;
		case EH::eBossState::Die:
			break;
		case EH::eBossState::None:
			break;
		default:
			break;
		}
	}
	
	void Boss::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Boss::Idle()
	{
		mCheckTime += Time::GetDeltaTime();
		if (mCheckTime > mThinkTime)
		{
			mCurState = eBossState::Attack;
			mCheckTime = 0.f;
		}
	}

	void Boss::Die()
	{
		IsDead = true;
	}

	void Boss::Attack()
	{
		srand((UINT)time(NULL));
		if (mCurType == eBossAttack::None)
			mCurType = eBossAttack(rand() % ((UINT)eBossAttack::None));

		switch (mCurType)
		{
		case EH::eBossAttack::OneLaser:
			OneLaser();
			break;
		case EH::eBossAttack::ThreeLaser:
			ThreeLaser();
			break;
		case EH::eBossAttack::None:
			break;
		default:
			break;
		}
	}
	void Boss::OneLaser()
	{
		mCheckTime += Time::GetDeltaTime();
		mDelayTime = 1.f;
		if (mDelayTime < mCheckTime)
		{
			mCurType = eBossAttack::None;
			mCurState = eBossState::Idle;
			mCheckTime = 0.f;
			BackGround* test = object::Instantiate<BackGround>(enums::eLayerType::UI);
			Transform* tr1 = test->GetComponent<Transform>();
			Transform* tr2 = mRightHand->GetComponent<Transform>();
			tr1->SetPos(Math::Vector2<float>(650.f, tr2->Getpos().y));
			test->AddComponent<Collider>();
			test->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1000.f, 220.f));
			SceneManager::GetCurScene()->SetLayer(enums::eLayerType::UI, test);
		}
		else
		{
			Transform* RightHandTr = mRightHand->GetComponent<Transform>();
			Transform* PlayerTr = mTarget->GetComponent<Transform>();
			mCurType = eBossAttack::OneLaser;
			float dir = PlayerTr->Getpos().y - RightHandTr->Getpos().y;
			Math::Vector2<float> pos = RightHandTr->Getpos();
			pos.y += dir * Time::GetDeltaTime() * 10.f;
			RightHandTr->SetPos(pos);
		}
	}

	void Boss::ThreeLaser()
	{
		mCheckTime += Time::GetDeltaTime();
		mSubCheckTime += Time::GetDeltaTime();
		mDelayTime = 3.f;
		mSubDelayTime = 1.f;
		if (mDelayTime < mCheckTime)
		{
			mCurType = eBossAttack::None;
			mCurState = eBossState::Idle;
			mCheckTime = 0.f;
			mIsRight = true;
		}
		else
		{
			mCurType = eBossAttack::ThreeLaser;
			if (mSubDelayTime < mSubCheckTime)
			{
				mSubCheckTime = 0.f;
				mIsRight = !mIsRight;
			}
			else
			{
				if (mIsRight)
				{
					Transform* RightHandTr = mRightHand->GetComponent<Transform>();
					Transform* PlayerTr = mTarget->GetComponent<Transform>();

					float dir = PlayerTr->Getpos().y - RightHandTr->Getpos().y;
					Math::Vector2<float> pos = RightHandTr->Getpos();
					pos.y += dir * Time::GetDeltaTime() * 10.f;
					RightHandTr->SetPos(pos);
				}
				else
				{
					Transform* LeftHandTr = mLeftHand->GetComponent<Transform>();
					Transform* PlayerTr = mTarget->GetComponent<Transform>();

					float dir = PlayerTr->Getpos().y - LeftHandTr->Getpos().y;
					Math::Vector2<float> pos = LeftHandTr->Getpos();
					pos.y += dir * Time::GetDeltaTime() * 10.f;
					LeftHandTr->SetPos(pos);
				}
			}
			
		}
	}
}