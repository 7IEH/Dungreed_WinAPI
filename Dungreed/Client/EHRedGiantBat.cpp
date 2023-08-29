#include "EHRedGiantBat.h"
#include "EHDetection.h"
#include "EHObject.h"
#include "EHWeapon.h"
#include "EHCollisionManager.h"
#include "EHBullet.h"
#include "EHPlayer.h"
#include "EHResources.h"
#include "EHDamageEffect.h"
#include "EHImageObject.h"

namespace EH
{
	RedGiantBat::RedGiantBat()
		:
		  mRadian{}
		, mBullet{}
		, mAttack(nullptr)
		, mCheck1(0)
		, mTargetRadian(0.f)
	{
		SetHP(40.f);
		// Transform
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Math::Vector2<float>(256.f, 256.f));

		// Detection
		mDect = object::Instantiate<Detection>(enums::eLayerType::Detect);
		Collider* dectcol = mDect->AddComponent<Collider>();
		dectcol->SetScale(Math::Vector2<float>(600.f, 600.f));

		// Collider
		Collider* col = AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(256.f, 256.f));

		// Animator
		Animator* ani = AddComponent<Animator>();
		Texture* texture = Resources::Load<Texture>(L"RedGiantRightIdle", L"..\\Resources\\Enemy\\JailField\\Bat\\RedGiantBat\\Idle\\Right\\RedBatSheet.bmp");
		ani->CreateAnimation(L"RedGiantRightIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(64.f, 64.f), Math::Vector2<float>(0.f, 0.f), 7, 0.1f);

		texture = Resources::Load<Texture>(L"RedGiantLeftIdle", L"..\\Resources\\Enemy\\JailField\\Bat\\RedGiantBat\\Idle\\Left\\RedGiantBat.bmp");
		ani->CreateAnimation(L"RedGiantLeftIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(64.f, 64.f), Math::Vector2<float>(0.f, 0.f), 7, 0.1f);

		texture = Resources::Load<Texture>(L"RedGiantLeftAttack", L"..\\Resources\\Enemy\\JailField\\Bat\\RedGiantBat\\Attack\\Left\\RedGiantAttack.bmp");
		ani->CreateAnimation(L"RedGiantLeftAttack", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(64.f, 64.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);

		texture = Resources::Load<Texture>(L"RedGiantRightAttack", L"..\\Resources\\Enemy\\JailField\\Bat\\RedGiantBat\\Attack\\Right\\RedGiantAttack.bmp");
		ani->CreateAnimation(L"RedGiantRightAttack", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(64.f, 64.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);

		// Time
		SetDelayTime(4.f);
		SetSubDelayTime(0.1f);

		// Sound
		mAttackSound = Resources::Load<Sound>(L"BatSound", L"..\\Resources\\Sound\\Enemy\\JailField\\Bat\\Bat2.wav");
	}

	RedGiantBat::~RedGiantBat()
	{
		Destroy(mDect);
		mDect = nullptr;
	}

	void RedGiantBat::Initialize()
	{
	}

	void RedGiantBat::Update()
	{
		Enemy::Update();
		switch (GetState())
		{
		case EH::Enemy::eState::Idle:
			Idle();
			break;
		case EH::Enemy::eState::Attack:
			Attack();
			break;
		case EH::Enemy::eState::Dead:
			Dead();
			break;
		default:
			break;
		}
		Transform* tr = GetComponent<Transform>();
		Transform* decttr = mDect->GetComponent<Transform>();
		decttr->SetPos(tr->Getpos());
	}

	void RedGiantBat::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void RedGiantBat::OnCollisionEnter(Collider* other)
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

			GetHpImage()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
			GetHpBaseImage()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);

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

	void RedGiantBat::OnCollisionStay(Collider* other)
	{
	}

	void RedGiantBat::OnCollisionExit(Collider* other)
	{
	}

	void RedGiantBat::Idle()
	{
		if (GetHP() <= 0)
		{
			SetState(eState::Dead);
		}

		if (GetTarget() != nullptr)
		{
			Transform* tr = GetComponent<Transform>();
			Transform* playertr = GetTarget()->GetComponent<Transform>();

			Math::Vector2<float> pos = tr->Getpos();
			Math::Vector2<float> playerpos = playertr->Getpos();

			Animator* ani = GetComponent<Animator>();

			float thinktime = GetCheckTime();
			SetCheckTime(thinktime += Time::GetDeltaTime());
			if (GetDelayTime() < thinktime)
			{
				// 각도 저장
				float radian = Math::Radian(playertr->Getpos(), tr->Getpos());
				mTargetRadian = radian;
				
				for (int i = 0;i < 20;i++)
				{
					mRadian[i] = 20.f * (3.14f / 180.f) * i;
				}

				if (mIsRight)
				{
					ani->PlayAnimation(L"RedGiantRightAttack", false);
				}
				else
				{
					ani->PlayAnimation(L"RedGiantLeftAttack", false);
				}

				SetCheckTime(0.f);
				SetState(eState::Attack);
				mAttackSound->Play(false);
			}
			else
			{
				if (pos.x < playerpos.x)
				{
					ani->PlayAnimation(L"RedGiantRightIdle", true);
					mIsRight = true;
				}
				else
				{
					ani->PlayAnimation(L"RedGiantLeftIdle", true);
					mIsRight = false;
				}
			}
		}
		else
		{
			SetTarget(mDect->passthetarget());
		}
	}

	void RedGiantBat::Attack()
	{
		if (GetHP() <= 0)
		{
			SetState(eState::Dead);
		}

		float chargetime = GetSubCheckTime();
		SetSubCheckTime(chargetime += Time::GetDeltaTime());
		if (GetSubDelayTime() < chargetime)
		{
			Bullet* bullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
			Collider* bulletcol = bullet->AddComponent<Collider>();
			Transform* bullettr = bullet->GetComponent<Transform>();
			bullettr->SetPos(Math::Vector2<float>(128.f * cosf(mRadian[mCheck1]) + GetComponent<Transform>()->Getpos().x
				, 128 * sinf(mRadian[mCheck1])+ GetComponent<Transform>()->Getpos().y));
			bullettr->SetScale(Math::Vector2<float>(56.f, 56.f));
			bulletcol->SetScale(Math::Vector2<float>(56.f, 56.f));
			mBullet[mCheck1] = bullet;
			bullet->SetStop(true);
			bullet->SetDeleteTime(10.f);
			bullet->SetPass(false);

			// animator
			Animator* bulletani = bullet->AddComponent<Animator>();
			Texture* texture = Resources::Load<Texture>(L"RangeBallBullet", L"..\\Resources\\Enemy\\JailField\\Bat\\Attack\\GiantBat\\Idle\\RangeBallBulletSheet.bmp");
			bulletani->CreateAnimation(L"RangeBallBullet", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(14.f, 14.f), Math::Vector2<float>(0.f, 0.f), 5, 0.1f);
			bulletani->PlayAnimation(L"RangeBallBullet", true);

			bullet->SetRadian(mTargetRadian);
			SetSubCheckTime(0.f);
			mCheck1++;
		}

		if (mCheck1 == 20)
		{
			for (int i = 0;i < 20;i++)
			{
				mBullet[i]->SetStop(false);
			}
			mCheck1 = 0;
			SetState(eState::Idle);
		}
	}

	void RedGiantBat::Dead()
	{
		if (mAttack != nullptr)
		{
			CollisionManager::ForceExit(GetComponent<Collider>(), mAttack->GetComponent<Collider>());
		}
		Destroy(this);
	}
}