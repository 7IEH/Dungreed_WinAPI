#include "EHSkelIceMagician.h"
#include "EHDetection.h"
#include "EHWeapon.h"
#include "EHSound.h"
#include "EHCollisionManager.h"
#include "EHObject.h"
#include "EHPlayer.h"
#include "EHBullet.h"

namespace EH
{
	SkelIceMagician::SkelIceMagician()
		:
		  mAttack(nullptr)
		, mIsRight(true)
		, mDect(nullptr)
		, mPlayerPos(Math::Vector2<float>(0.f,0.f))
		, mMagicCircle(nullptr)
	{
		SetDelayTime(4.0f);
		SetSubDelayTime(3.0f);
		SetHP(40.f);
		Player* player = SceneManager::GetCurScene()->GetPlayer();
		if (player != nullptr)
		{
			SetTarget(player);
		}

		Collider* col = AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(50.f, 50.f));
	}

	SkelIceMagician::~SkelIceMagician()
	{
	}

	void SkelIceMagician::Initialize()
	{
	}

	void SkelIceMagician::Update()
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
	}

	void SkelIceMagician::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void SkelIceMagician::OnCollisionEnter(Collider* other)
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

	void SkelIceMagician::OnCollisionStay(Collider* other)
	{
	}

	void SkelIceMagician::OnCollisionExit(Collider* other)
	{
	}

	void SkelIceMagician::Idle()
	{
		if (GetHP() <= 0)
		{
			SetState(eState::Dead);
		}

		float thinktime = GetCheckTime();
		SetCheckTime(thinktime += Time::GetDeltaTime());
		Transform* tr = GetComponent<Transform>();
		Transform* playertr = nullptr;
		Animator* ani = GetComponent<Animator>();
		if (GetTarget() != nullptr)
		{
			//playanimation


			playertr = GetTarget()->GetComponent<Transform>();
		}

		if (GetDelayTime() < thinktime)
		{
			// playanimation
			if (mIsRight)
			{

			}
			else
			{

			}
			// circleanimation

			mPlayerPos = playertr->Getpos();
			SetCheckTime(0.f);
			SetState(eState::Attack);
		}
		else
		{
			Math::Vector2<float> playerpos;
			Math::Vector2<float> pos = tr->Getpos();
			if (playertr != nullptr)
			{
				playerpos = playertr->Getpos();
			}

			if (playerpos.x < pos.x)
			{
				//ani->PlayAnimation(L"IceMagicianLeftIdle",true);
				mIsRight = false;
			}
			else
			{
				//ani->PlayAnimation(L"IceMagicianRightIdle",true);
				mIsRight = true;
			}
		}
	}

	void SkelIceMagician::Attack()
	{
		if (GetHP() <= 0)
		{
			SetState(eState::Dead);
		}

		float chargetime = GetSubCheckTime();
		SetSubCheckTime(chargetime += Time::GetDeltaTime());
		if(GetSubDelayTime()<chargetime)
		{
			// bullet
			for (int i = 0;i < 6;i++)
			{
				Bullet* bullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
				Transform* bullettr = bullet->GetComponent<Transform>();
				Collider* bulletcol = bullet->AddComponent<Collider>();
				bulletcol->SetScale(Math::Vector2<float>(40.f, 40.f));
				bullettr->SetPos(mPlayerPos);
				bullettr->SetScale(Math::Vector2<float>(0.f,0.f));
				bullet->SetDeleteTime(10.f);
				bullet->SetRadian(0.52f + 1.04f * i);
				bullet->SetStop(false);
				SetSubCheckTime(0.f);
				SetState(eState::Idle);
			}
			//circle animation delete
		}
	}

	void SkelIceMagician::Dead()
	{
		CollisionManager::ForceExit(GetComponent<Collider>(), mAttack->GetComponent<Collider>());
		Destroy(this);
	}
}