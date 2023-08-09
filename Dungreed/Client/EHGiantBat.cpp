#include "EHGiantBat.h"
#include "EHDetection.h"
#include "EHObject.h"
#include "EHWeapon.h"
#include "EHResources.h"
#include "EHPlayer.h"
#include "EHCollisionManager.h"
#include "EHBullet.h"

namespace EH
{
	GiantBat::GiantBat()
		:
		  mRadian(0.f)
		, mAttack(nullptr)
		, mIsRight(true)
		, mCheck1(0)
	{
		SetHP(40.f);
		SetDelayTime(4.f);
		SetSubDelayTime(0.2f);
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Math::Vector2<float>(256.f, 256.f));

		// Detection
		mDect = object::Instantiate<Detection>(enums::eLayerType::Detect);
		Collider* dectcol = mDect->AddComponent<Collider>();
		dectcol->SetScale(Math::Vector2<float>(300.f, 300.f));
		 
		// Collider
		Collider* col = AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(256.f, 256.f));

		// Animator
		Animator* ani = AddComponent<Animator>();
		Texture* texture = Resources::Load<Texture>(L"GiantRightIdle", L"..\\Resources\\Enemy\\JailField\\Bat\\GiantBat\\Idle\\Right\\GiantBatSheet.bmp");
		ani->CreateAnimation(L"GiantRightIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(64.f, 64.f), Math::Vector2<float>(0.f, 0.f), 7, 0.1f);

		texture = Resources::Load<Texture>(L"GiantLeftIdle", L"..\\Resources\\Enemy\\JailField\\Bat\\GiantBat\\Idle\\Left\\GiantBat.bmp");
		ani->CreateAnimation(L"GiantLeftIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(64.f, 64.f), Math::Vector2<float>(0.f, 0.f), 7, 0.1f);

		texture = Resources::Load<Texture>(L"GiantLeftAttack", L"..\\Resources\\Enemy\\JailField\\Bat\\GiantBat\\Attack\\Left\\GiantAttack.bmp");
		ani->CreateAnimation(L"GiantLeftAttack", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(64.f, 64.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);

		texture = Resources::Load<Texture>(L"GiantRightAttack", L"..\\Resources\\Enemy\\JailField\\Bat\\GiantBat\\Attack\\Right\\GiantAttack.bmp");
		ani->CreateAnimation(L"GiantRightAttack", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(64.f, 64.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);

		// Sound
		mAttackSound = Resources::Load<Sound>(L"BatSound", L"..\\Resources\\Sound\\Enemy\\JailField\\Bat\\Bat2.wav");
	}

	GiantBat::~GiantBat()
	{
	}

	void GiantBat::Initialize()
	{
	}

	void GiantBat::Update()
	{
		GameObject::Update();
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

	void GiantBat::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void GiantBat::OnCollisionEnter(Collider* other)
	{
		// 플레이어 오브젝트 충돌
		Weapon* weapon = dynamic_cast<Weapon*>(other->GetOwner());
		if (weapon != nullptr)
		{
			UINT hp = GetHP();
			SetHP(hp -= 20);
			mAttack = weapon;
		}
	}

	void GiantBat::OnCollisionStay(Collider* other)
	{
	}

	void GiantBat::OnCollisionExit(Collider* other)
	{
	}

	void GiantBat::Idle()
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
				mRadian = radian;

				if (mIsRight)
				{
					ani->PlayAnimation(L"GiantRightAttack", false);
				}
				else
				{
					ani->PlayAnimation(L"GiantLeftAttack", false);
				}

				SetCheckTime(0.f);
				SetState(eState::Attack);
				mAttackSound->Play(false);
			}
			else
			{
				if (pos.x < playerpos.x)
				{
					ani->PlayAnimation(L"GiantRightIdle", true);
					mIsRight = true;
				}
				else
				{
					ani->PlayAnimation(L"GiantLeftIdle", true);
					mIsRight = false;
				}
			}
		}
		else
		{
			SetTarget(mDect->passthetarget());
		}
	}

	void GiantBat::Attack()
	{
		if (GetHP() <= 0)
		{
			SetState(eState::Dead);
		}

		float chargetime = GetSubCheckTime();
		SetSubCheckTime(chargetime += Time::GetDeltaTime());
		if (GetSubDelayTime() < chargetime)
		{
			for (int i = -1;i <= 1;i++)
			{
				Bullet* bullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
				Transform* tr = GetComponent<Transform>();
				Transform* bullettr = bullet->GetComponent<Transform>();
				Math::Vector2<float> pos = tr->Getpos();
				bullet->SetStop(false);
				bullettr->SetPos(Math::Vector2<float>(pos.x, pos.y));
				bullettr->SetScale(Math::Vector2<float>(56.f, 56.f));
				bullet->SetRadian(mRadian + i * 0.34);
				bullet->AddComponent<Collider>();
				bullet->GetComponent<Collider>()->SetScale(Math::Vector2<float>(56.f, 56.f));
				bullet->SetDeleteTime(10.f);
				bullet->SetPass(false);

				// animator
				Animator* bulletani = bullet->AddComponent<Animator>();
				Texture* texture = Resources::Load<Texture>(L"RangeBallBullet", L"..\\Resources\\Enemy\\JailField\\Bat\\Attack\\GiantBat\\Idle\\RangeBallBulletSheet.bmp");
				bulletani->CreateAnimation(L"RangeBallBullet", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(14.f, 14.f), Math::Vector2<float>(0.f, 0.f), 5, 0.1f);
				bulletani->PlayAnimation(L"RangeBallBullet", true);
			}
			
			SetSubCheckTime(0.f);
			mCheck1++;
		}

		if (mCheck1 == 3)
		{
			mCheck1 = 0;
			SetState(eState::Idle);
		}
	}

	void GiantBat::Dead()
	{
		CollisionManager::ForceExit(GetComponent<Collider>(), mAttack->GetComponent<Collider>());
		Destroy(this);
	}
}