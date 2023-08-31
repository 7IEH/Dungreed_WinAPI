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
#include "EHEffect.h"
#include "EHCamera.h"
#include "EHDeadObj.h"
#include "EHTrigger.h"
#include "EHBulletCreator.h"
#include "EHDamageEffect.h"
#include <time.h>

namespace EH
{
	Boss::Boss()
		:
		mCurState(eBossState::Idle)
		, mCurType(eBossAttack::None)
		, mThinkTime(2.f)
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
		, mCheck2(0)
		, mCheck1(0)
		, mRightLaserani(false)
		, mLeftLaserani(false)
		, mIsStop(true)
	{
		SetHP(100.f);

		srand((UINT)time(NULL));

		// HAND
		mLeftHand = object::Instantiate<BossHand>(enums::eLayerType::Enemy);
		mLeftHand->SetOwner(this);
		mLeftHand->SetRight(false);
		Transform* tr = mLeftHand->GetComponent<Transform>();
		tr->SetPos(Math::Vector2<float>(370.f, 822.f));
		tr->SetScale(Math::Vector2<float>(228.f, 276.f));
		Texture* temp = Resources::Load<Texture>(L"BossLeftHandIdle", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\HandleLeft\\SkellBossLeftHandIdleSheet.bmp");
		mLeftHand->AddComponent<Animator>();
		mLeftHand->GetComponent<Animator>()->CreateAnimation(L"BossLeftHandIdle", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(57.f, 69.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		temp = Resources::Load<Texture>(L"BossLeftHandAttack", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\Attack\\Laser\\Left\\SkelBossHandAttack.bmp");
		mLeftHand->GetComponent<Animator>()->CreateAnimation(L"BossLeftHandAttack", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(70.f, 80.f), Math::Vector2<float>(0.f, 0.f), 18, 0.1f);

		temp = Resources::Load<Texture>(L"BossLeftHandDead", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\HandleLeft\\SkellBossLeftHandIdle1.bmp");
		mLeftHand->GetComponent<Animator>()->CreateAnimation(L"BossLeftHandDead", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(57.f, 69.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);

		mLeftHand->GetComponent<Animator>()->PlayAnimation(L"BossLeftHandIdle", true);
		mLeftHand->GetComponent<Animator>()->SetAffectedCamera(true);

		mRightHand = object::Instantiate<BossHand>(enums::eLayerType::Enemy);
		tr = mRightHand->GetComponent<Transform>();
		mRightHand->SetOwner(this);
		tr->SetPos(Math::Vector2<float>(1106.f, 542.f));
		tr->SetScale(Math::Vector2<float>(228.f, 276.f));
		temp = Resources::Load<Texture>(L"BossRightHandIdle", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\HandleRight\\SkellBossRightHandIdleSheet.bmp");
		mRightHand->AddComponent<Animator>();
		mRightHand->GetComponent<Animator>()->CreateAnimation(L"BossRightHandIdle", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(57.f, 69.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);

		temp = Resources::Load<Texture>(L"BossRightHandAttack", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\Attack\\Laser\\Right\\SkelBossHandAttack.bmp");
		mRightHand->GetComponent<Animator>()->CreateAnimation(L"BossRightHandAttack", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(70.f, 80.f), Math::Vector2<float>(0.f, 0.f), 18, 0.1f);

		temp = Resources::Load<Texture>(L"BossRightHandDead", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\HandleRight\\SkellBossLeftHandIdle1.bmp");
		mRightHand->GetComponent<Animator>()->CreateAnimation(L"BossRightHandDead", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(57.f, 69.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);

		mRightHand->GetComponent<Animator>()->PlayAnimation(L"BossRightHandIdle", true);
		mRightHand->GetComponent<Animator>()->SetAffectedCamera(true);

		// Sound
		mSpawnSword = Resources::Load<Sound>(L"SpawnSword", L"..\\Resources\\Sound\\Enemy\\JailField\\Belial\\Sword\\SpawnMonster.wav");
		mLaserSound = Resources::Load<Sound>(L"Laser", L"..\\Resources\\Sound\\Enemy\\JailField\\Belial\\iceball.wav");
		mDefeatSound = Resources::Load<Sound>(L"bossDefeat", L"..\\Resources\\Sound\\Enemy\\JailField\\Belial\\bossDefeat.wav");

		// BackParticle
		mBackparticle = object::Instantiate<GameObject>(enums::eLayerType::BackGround);
		Transform* backparticletr = mBackparticle->GetComponent<Transform>();
		backparticletr->SetPos(Math::Vector2<float>(730.f, 660.f));
		backparticletr->SetScale(Math::Vector2<float>(200.f, 200.f));
		Animator* backparticleani = mBackparticle->AddComponent<Animator>();
		temp = Resources::Load<Texture>(L"SkelBossBackParticle", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\Back\\SkelBossBack.bmp");
		backparticleani->CreateAnimation(L"SkelBossBackParticle", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(50.f, 50.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		backparticleani->PlayAnimation(L"SkelBossBackParticle", true);

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

		for (int i = 0;i < 4;i++)
		{
			mBulletct[i] = object::Instantiate<BulletCreator>(enums::eLayerType::Enemy);
			mBulletct[i]->SetOwner(this);
		}
	}

	Boss::~Boss()
	{
		Destroy(mRightHand);
		Destroy(mLeftHand);
		Destroy(mBackparticle);

		for (int i = 0; i < 4;i++)
		{
			Destroy(mBulletct[i]);
		}
	}

	void Boss::Initialize()
	{
	}

	void Boss::Update()
	{
		GameObject::Update();

		if (mIsStop)
		{
			return;
		}

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
		if (GetHP() <= 0)
		{
			mCurState = eBossState::Die;
		}

		mCheck2 = 0;
		mCheckTime += Time::GetDeltaTime();
		if (mCheckTime > mThinkTime)
		{
			mCurState = eBossState::Attack;
			mCheckTime = 0.f;
		}
	}

	void Boss::Dead()
	{
		float timecheck = GetCheckTime();
		float subtimecheck = GetSubCheckTime();
		SetCheckTime(timecheck += Time::GetDeltaTime());
		SetSubCheckTime(subtimecheck += Time::GetDeltaTime());
		Transform* tr = GetComponent<Transform>();
		Math::Vector2<float> pos = tr->Getpos();

		if (mCheck3 == 0)
		{
			Animator* ani = GetComponent<Animator>();
			ani->PlayAnimation(L"BossDead", false);
			mDefeatSound->Play(false);
			SceneManager::GetCurScene()->GetBGM()->Stop(true);
			mRightHand->GetComponent<Animator>()->PlayAnimation(L"BossRightHandDead", true);
			mLeftHand->GetComponent<Animator>()->PlayAnimation(L"BossLeftHandDead", true);
			mCheck3++;
		}
		// 슬로우 모션

		// effect

		if (2.f < timecheck)
		{
			if (0.2f < subtimecheck)
			{
				for (int j = 0;j < 10;j++)
				{
					Effect* effect = object::Instantiate<Effect>(enums::eLayerType::UI);
					Transform* effecttr = effect->GetComponent<Transform>();
					effecttr->SetPos(Math::Vector2<float>(32.f * (mCheck3 - 1) * cosf(1.57 + 0.628 * j) + pos.x + 20.f, 32.f * (mCheck3 - 1) * sinf(1.57 + 0.628 * j) + pos.y));
					effecttr->SetScale(Math::Vector2<float>(256.f, 256.f));

					Animator* effectani = effect->AddComponent<Animator>();
					Texture* texture = Resources::Load<Texture>(L"DieEffect", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\Dead\\Effect\\Die.bmp");
					effectani->CreateAnimation(L"DieEffect", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(64.f, 64.f), Math::Vector2<float>(0.f, 0.f), 11, 0.1f);
					effectani->PlayAnimation(L"DieEffect", false);
					Sound* explosion = Resources::Load<Sound>(L"explosion", L"..\\Resources\\Sound\\Enemy\\JailField\\Belial\\Explosion.wav");
					explosion->Play(false);
				}
				mCheck3++;
				SetSubCheckTime(0.f);
			}
		}

		if (mCheck3 == 16)
		{
			if (mAttack != nullptr)
			{
				CollisionManager::ForceExit(GetComponent<Collider>(), mAttack->GetComponent<Collider>());
			}
			Destroy(this);

			// 죽는거 떨굼
			DeadObj* deaddown = object::Instantiate<DeadObj>(enums::eLayerType::Item);
			Transform* objtr = deaddown->GetComponent<Transform>();
			Collider* objcol = deaddown->AddComponent<Collider>();
			SpriteRenderer* objsr = deaddown->AddComponent<SpriteRenderer>();
			Rigidbody* objrigid = deaddown->AddComponent<Rigidbody>();
			Texture* texture = Resources::Load<Texture>(L"BossDeadDown", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\Dead\\SkellBossDeadDown.bmp");
			objsr->SetImg(texture);
			objtr->SetPos(Math::Vector2<float>(pos));
			objtr->SetScale(Math::Vector2<float>(280.f, 132.f));
			objcol->SetScale(Math::Vector2<float>(280.f, 132.f));

			DeadObj* deadmid = object::Instantiate<DeadObj>(enums::eLayerType::Item);
			objtr = deadmid->GetComponent<Transform>();
			objcol = deadmid->AddComponent<Collider>();
			objsr = deadmid->AddComponent<SpriteRenderer>();
			objrigid = deadmid->AddComponent<Rigidbody>();
			texture = Resources::Load<Texture>(L"BossDeadMid", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\Dead\\SkellBossDeadMid.bmp");
			objsr->SetImg(texture);
			objtr->SetPos(Math::Vector2<float>(pos));
			objtr->SetScale(Math::Vector2<float>(280.f, 48.f));
			objcol->SetScale(Math::Vector2<float>(280.f, 48.f));

			DeadObj* deadupper = object::Instantiate<DeadObj>(enums::eLayerType::Item);
			objtr = deadupper->GetComponent<Transform>();
			objcol = deadupper->AddComponent<Collider>();
			objsr = deadupper->AddComponent<SpriteRenderer>();
			objrigid = deadupper->AddComponent<Rigidbody>();
			texture = Resources::Load<Texture>(L"BossDeadUpper", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\Dead\\SkellBossDeadUpper.bmp");
			objsr->SetImg(texture);
			objtr->SetPos(Math::Vector2<float>(pos));
			objtr->SetScale(Math::Vector2<float>(280.f, 308.f));
			objcol->SetScale(Math::Vector2<float>(280.f, 308.f));

			Trigger* trigger2 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
			trigger2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(Math::Vector2<float>(pos.x, pos.y + 500.f)));
			trigger2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(84.f, 64.f));
			trigger2->AddComponent<Collider>();
			trigger2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(84.f, 64.f));
			trigger2->SetType(Trigger::eTriggertype::Tresure);
			Animator* ani = trigger2->AddComponent<Animator>();
			texture = Resources::Load<Texture>(L"OpenTresure", L"..\\Resources\\Item\\Chest\\GoldTresureOpened.bmp");
			ani->CreateAnimation(L"OpenTresure", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(21.f, 16.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
			texture = Resources::Load<Texture>(L"CloseTresure", L"..\\Resources\\Item\\Chest\\GoldTresureClosed.bmp");
			ani->CreateAnimation(L"CloseTresure", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(21.f, 16.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
			ani->PlayAnimation(L"CloseTresure", false);
			trigger2->SetWeaponName(L"TwoHand");
		}
	}

	void Boss::Attack()
	{
		if (GetHP() <= 0)
		{
			mCurState = eBossState::Die;
		}

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
		mSubDelayTime = 2.3f;
		Transform* RightHandTr = mRightHand->GetComponent<Transform>();
		Transform* PlayerTr = mTarget->GetComponent<Transform>();

		Animator* RightHandani = mRightHand->GetComponent<Animator>();
		if (mSubDelayTime < mCheckTime)
		{
			RightHandTr->SetScale(Math::Vector2<float>(228.f, 276.f));
			RightHandani->PlayAnimation(L"BossRightHandIdle", true);
			mCheckTime = 0.f;
			mCurType = eBossAttack::None;
			mCurState = eBossState::Idle;
			mCheck1 = 0;
			return;
		}

		if (mDelayTime < mCheckTime && mCheck1 == 0)
		{
			RightHandTr->SetScale(Math::Vector2<float>(280.f, 320.f));
			RightHandani->PlayAnimation(L"BossRightHandAttack", false);
			mCheck1++;
			Laser* rightlaser = object::Instantiate<Laser>(enums::eLayerType::UI);
			Transform* tr1 = rightlaser->GetComponent<Transform>();
			Transform* tr2 = mRightHand->GetComponent<Transform>();
			rightlaser->SetRight(true);
			rightlaser->SetLaserPos(Math::Vector2<float>(420.f, tr2->Getpos().y));
			tr1->SetPos(Math::Vector2<float>(420.f, tr2->Getpos().y));
			rightlaser->AddComponent<Collider>();
			rightlaser->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1280.f, 220.f));
			mLaserSound->Play(false);
		}
		else if (mCheck1 == 0)
		{
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
		mSubCheckTime2 += Time::GetDeltaTime();
		mSubCheckTime3 += Time::GetDeltaTime();

		mDelayTime = 1.5f;
		mSubDelayTime = 1.f;

		Transform* RightHandTr = mRightHand->GetComponent<Transform>();
		Transform* PlayerTr = mTarget->GetComponent<Transform>();

		Animator* RightHandani = mRightHand->GetComponent<Animator>();
		Transform* LeftHandTr = mLeftHand->GetComponent<Transform>();

		Animator* LeftHandani = mLeftHand->GetComponent<Animator>();

		if (mCheck2 == 3)
		{
			mCheck1 = 0;
			mCheck2 = 0;
			mCurType = eBossAttack::None;
			mCurState = eBossState::Idle;
			mCheckTime = 0.f;
			mSubCheckTime = 0.f;
			mIsRight = true;
		}
		else if (mCheck1 < 3)
		{
			mCurType = eBossAttack::ThreeLaser;
			if (mSubDelayTime < mSubCheckTime)
			{
				if (mIsRight)
				{
					RightHandTr->SetScale(Math::Vector2<float>(280.f, 320.f));
					RightHandani->PlayAnimation(L"BossRightHandAttack", false);
					mRightLaserani = true;
					Laser* rightlaser = object::Instantiate<Laser>(enums::eLayerType::UI);
					Transform* tr1 = rightlaser->GetComponent<Transform>();
					Transform* tr2 = mRightHand->GetComponent<Transform>();
					rightlaser->SetRight(true);
					rightlaser->SetLaserPos(Math::Vector2<float>(420.f, tr2->Getpos().y));
					tr1->SetPos(Math::Vector2<float>(420.f, tr2->Getpos().y));
					rightlaser->AddComponent<Collider>();
					rightlaser->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1280.f, 220.f));
					mLaserSound->Play(false);
					mRightHand->SetType(eAttack::Attack);
				}
				else
				{
					LeftHandTr->SetScale(Math::Vector2<float>(280.f, 320.f));
					LeftHandani->PlayAnimation(L"BossLeftHandAttack", false);
					mLeftLaserani = true;
					Laser* leftlaser = object::Instantiate<Laser>(enums::eLayerType::UI);
					Transform* tr1 = leftlaser->GetComponent<Transform>();
					Transform* tr2 = mLeftHand->GetComponent<Transform>();
					leftlaser->SetRight(false);
					leftlaser->SetLaserPos(Math::Vector2<float>(1000.f, tr2->Getpos().y));
					tr1->SetPos(Math::Vector2<float>(1000.f, tr2->Getpos().y));
					leftlaser->AddComponent<Collider>();
					leftlaser->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1280.f, 220.f));
					mLaserSound->Play(false);
					mLeftHand->SetType(eAttack::Attack);
				}
				mSubCheckTime = 0.f;
				mIsRight = !mIsRight;
				mCheck1++;
			}
			else
			{
				if (mIsRight)
				{
					float dir = PlayerTr->Getpos().y - RightHandTr->Getpos().y;
					Math::Vector2<float> pos = RightHandTr->Getpos();
					pos.y += dir * Time::GetDeltaTime() * 10.f;
					RightHandTr->SetPos(pos);
				}
				else
				{
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
				mSwordNameGroup[i]->GetComponent<SpriteRenderer>()->GetImg()->SetDegree(radian * (180.f / 3.14f) + 90.f);
			}
		}
	}

	void Boss::Barrage()
	{
		float movetime = GetCheckTime();
		SetCheckTime(movetime += Time::GetDeltaTime());
		Transform* tr = GetComponent<Transform>();
		Animator* ani = GetComponent<Animator>();

		if (mCheck4 == 0)
		{
			Transform* tr = GetComponent<Transform>();
			tr->SetScale(Math::Vector2<float>(280.f, 512.f));
			ani->PlayAnimation(L"BossAttack", false);
			mCheck4 = 1;
		}

		if (mCheck2 == 4)
		{
			SetCheckTime(0.f);
			mCurState = eBossState::Idle;
			mCurType = eBossAttack::None;
			mCheck2 = 0;
			mCheck3 = 0;
			tr->SetScale(Math::Vector2<float>(280.f, 396.f));
			ani->PlayAnimation(L"BossIdle", true);
			mCheck4 = 0;
			return;
		}

		if (2.f < movetime)
		{
			if (mCheck3 == 0)
			{
				for (int i = 0;i < 4;i++)
				{
					mBulletct[i]->SetType(AttackType::Barrage);
				}
				mCheck3++;
			}
		}

		mMove += 0.003f;
		for (int i = 0;i < 4;i++)
		{
			Transform* bulletcttr = mBulletct[i]->GetComponent<Transform>();
			mBulletct[i]->SetDegree((70.f * mMove + 90.f * i));
			bulletcttr->SetPos(Math::Vector2<float>(tr->Getpos().x+ 50.f + 40.f * cosf((mMove + 90.f * i) * (3.14f / 180.f)), tr->Getpos().y + 50.f + 50.f * sinf((mMove + 90.f * i) * (3.14f / 180.f))));
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

			Transform* tr = GetComponent<Transform>();

			DamageEffect* damageef = object::Instantiate<DamageEffect>(enums::eLayerType::UI);
			Transform* eftr = damageef->GetComponent<Transform>();
			eftr->SetPos(tr->Getpos());
			eftr->SetScale(Math::Vector2<float>(14.f, 22.f));
			damageef->SetDamage(2);

			DamageEffect* damageef2 = object::Instantiate<DamageEffect>(enums::eLayerType::UI);
			eftr = damageef2->GetComponent<Transform>();
			eftr->SetPos(Math::Vector2<float>(tr->Getpos().x + 14.f, tr->Getpos().y));
			eftr->SetScale(Math::Vector2<float>(14.f, 22.f));
			damageef2->SetDamage(0);
		}
	}

	void Boss::OnCollisionStay(Collider* other)
	{
	}

	void Boss::OnCollisionExit(Collider* other)
	{
	}
}