#include "EHBoss.h"
#include "EHObject.h"
#include "EHSceneManager.h"
#include "EHResources.h"
#include "EHPlayer.h"
#include "EHComponent.h"
#include "EHLaser.h"
#include "EHBullet.h"
#include "EHWeapon.h"
#include "EHCollisionManager.h"
#include "EHCanvas.h"
#include "EHImageObject.h"
#include <time.h>

namespace EH
{
	Boss::Boss()
		:
		mCurState(eBossState::Idle)
		, mCurType(eBossAttack::None)
		, mThinkTime(5.f)
		, mDelayTime(0.f)
		, mCheckTime(0.f)
		, mSubDelayTime(0.f)
		, mSubCheckTime(0.f)
		, mIsRight(true)
		, IsDead(false)
		, mSwordNameGroup{}
		, mSwordNumbering(0)
		, mAttack(nullptr)
		, mCanvas(nullptr)
	{
		SetHP(100.f);

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

		mSpawnSword = Resources::Load<Sound>(L"SpawnSword", L"..\\Resources\\Sound\\Enemy\\JailField\\Belial\\Sword\\SpawnMonster.wav");

		// UI Canvas
		// UI setting
		Canvas* BossUICanvas = object::Instantiate<Canvas>(enums::eLayerType::UI);
		Texture* texture = Resources::Load<Texture>(L"BossLifeBack", L"..\\Resources\\Enemy\\Boss\\UI\\BossLifeBack.png");
		BossUICanvas->AddImageObject(L"BossLifeBack", texture, false, Math::Vector2<float>(640.f, 670.f), Math::Vector2<float>(500.f, 64.f));

		texture = Resources::Load<Texture>(L"BossHP", L"..\\Resources\\Enemy\\Boss\\UI\\BossLife.png");
		BossUICanvas->AddImageObject(L"BossHP", texture, false, Math::Vector2<float>(676.f, 670.f), Math::Vector2<float>(402.f, 56.f));

		texture = Resources::Load<Texture>(L"BossHPBase", L"..\\Resources\\Enemy\\Boss\\UI\\BossLifeBase.png");
		BossUICanvas->AddImageObject(L"BossHPBase", texture, false, Math::Vector2<float>(640.f, 670.f), Math::Vector2<float>(500.f, 64.f));

		texture = Resources::Load<Texture>(L"BossPortrait", L"..\\Resources\\Enemy\\Boss\\UI\\BossSkellPortrait.png");
		BossUICanvas->AddImageObject(L"BossPortrait", texture, false, Math::Vector2<float>(435.f, 670.f), Math::Vector2<float>(68.f, 40.f));

		mCanvas = BossUICanvas;

		// Collider
		Collider* col = AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(280.f, 396.f));
	}

	Boss::~Boss()
	{
		Destroy(mRightHand);
		Destroy(mLeftHand);
	}

	void Boss::Initialize()
	{
	}

	void Boss::Update()
	{
		GameObject::Update();

		switch (mCurState)
		{
		case EH::eBossState::Idle:
			Idle();
			break;
		case EH::eBossState::Attack:
			Attack();
			break;
		case EH::eBossState::Die:
			Dead();
			break;
		case EH::eBossState::None:
			break;
		default:
			break;
		}

		// UI Update
		ImageObject* hp = mCanvas->Find(L"BossHP");
		Transform* tr = hp->GetComponent<Transform>();
		tr->SetPos(Math::Vector2<float>(676.f - ((402.f - 402.f * ((float)GetHP() / (float)100.f)) / 2.f), tr->Getpos().y));
		tr->SetScale(Math::Vector2<float>(402.f * ((float)GetHP() / (float)100.f), tr->GetScale().y));
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

	void Boss::Dead()
	{
		CollisionManager::ForceExit(GetComponent<Collider>(), mAttack->GetComponent<Collider>());
		Destroy(this);
	}

	void Boss::Attack()
	{
		if (GetHP() <= 0)
		{
			mCurState = eBossState::Die;
		}

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
		case EH::eBossAttack::Sword:
			Sword();
			break;
		case EH::eBossAttack::Barrage:
			Barrage();
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
			Laser* test = object::Instantiate<Laser>(enums::eLayerType::UI);
			Transform* tr1 = test->GetComponent<Transform>();
			Transform* tr2 = mRightHand->GetComponent<Transform>();
			tr1->SetPos(Math::Vector2<float>(650.f, tr2->Getpos().y));
			test->AddComponent<Collider>();
			test->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1000.f, 220.f));
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
		mDelayTime = 1.5f;
		mSubDelayTime = 0.5f;
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

	void Boss::Sword()
	{
		mCheckTime += Time::GetDeltaTime();
		mSubCheckTime += Time::GetDeltaTime();
		mDelayTime = 6.f;
		mSubDelayTime = 0.5f;

		// sword 1개씩 생성 총 6개 만들기
		if (mSubDelayTime < mSubCheckTime && mSwordNumbering < 6)
		{
			Transform* playertr = mTarget->GetComponent<Transform>();
			Bullet* sword1 = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
			Transform* Swordtr = sword1->GetComponent<Transform>();
			Transform* Bosstr = GetComponent<Transform>();
			Swordtr->SetPos(Math::Vector2<float>(500.f + mSwordNumbering * 100.f, Bosstr->Getpos().y - 40.f));
			Swordtr->SetScale(Math::Vector2<float>(84.f, 260.f));
			SpriteRenderer* swordsr = sword1->AddComponent<SpriteRenderer>();
			Texture* texture = Resources::Load<Texture>(L"BossSword" + std::to_wstring(mSwordNumbering), L"..\\Resources\\Enemy\\Boss\\SkellBoss\\Sword\\BossSword.png");
			float radian = Math::Radian(playertr->Getpos(), Swordtr->Getpos());
			texture->SetDegree(radian * (180.f / 3.14f) + 90.f);
			swordsr->SetImg(texture);
			Collider* swordcol = sword1->AddComponent<Collider>();
			swordcol->SetScale(Math::Vector2<float>(30.f, 200.f));
			sword1->SetDeleteTime(2.f);
			sword1->SetStop(true);
			mSubCheckTime = 0.f;
			mSwordNameGroup[mSwordNumbering] = sword1;
			mSwordNumbering += 1;
			mSpawnSword->Play(false);
		}

		if (mSwordNumbering == 6)
		{
			for (Bullet* sword : mSwordNameGroup)
			{
				if (sword == nullptr)
					continue;
				sword->SetRadian(Math::Radian(mTarget->GetComponent<Transform>()->Getpos()
					, sword->GetComponent<Transform>()->Getpos()));
				sword->SetStop(false);
			}
			mCurState = eBossState::Idle;
			mCurType = eBossAttack::None;
			mCheckTime = 0.f;
			mSwordNumbering = 0;
		}
		else
		{
			for (UINT i = 0;i < mSwordNumbering;i++)
			{
				Transform* playertr = mTarget->GetComponent<Transform>();	
				float radian = Math::Radian(playertr->Getpos(), mSwordNameGroup[i]->GetComponent<Transform>()->Getpos());
				mSwordNameGroup[i]->GetComponent<SpriteRenderer>()->GetImg()->SetDegree(radian* (180.f / 3.14f) + 90.f);
			}
		}
	}

	void Boss::Barrage()
	{
		mCheckTime += Time::GetDeltaTime();
		mDelayTime = 2.f;
		if (mDelayTime < mCheckTime)
		{
			mCurState = eBossState::Idle;
			mCurType = eBossAttack::None;
			mCheckTime = 0.f;
		}
	}

	void Boss::OnCollisionEnter(Collider* other)
	{
		// 플레이어 오브젝트 충돌
		Weapon* weapon = dynamic_cast<Weapon*>(other->GetOwner());
		if (weapon != nullptr)
		{
			UINT hp = GetHP();
			SetHP(hp -= 20);
			mAttack = weapon;
			GetHitSound()->Play(false);
		}
	}

	void Boss::OnCollisionStay(Collider* other)
	{
	}

	void Boss::OnCollisionExit(Collider* other)
	{
	}
}