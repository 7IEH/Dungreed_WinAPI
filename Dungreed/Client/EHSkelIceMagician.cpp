#include "EHSkelIceMagician.h"
#include "EHDetection.h"
#include "EHWeapon.h"
#include "EHSound.h"
#include "EHCollisionManager.h"
#include "EHObject.h"
#include "EHPlayer.h"
#include "EHBullet.h"
#include "EHResources.h"
#include "EHDamageEffect.h"
#include "EHImageObject.h"	

namespace EH
{
	SkelIceMagician::SkelIceMagician()
		:
		mAttack(nullptr)
		, mIsRight(true)
		, mDect(nullptr)
		, mPlayerPos(Math::Vector2<float>(0.f, 0.f))
		, mMagicCircle(nullptr)
	{
		SetDelayTime(3.f);
		SetSubDelayTime(1.8f);
		SetHP(40.f);
		Player* player = SceneManager::GetCurScene()->GetPlayer();
		if (player != nullptr)
		{
			SetTarget(player);
		}

		// Collider
		Collider* col = AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(128.f, 120.f));

		//Animator
		Animator* ani = AddComponent<Animator>();
		Texture* texture = Resources::Load<Texture>(L"SkelIceMagicianRightIdle", L"..\\Resources\\Enemy\\IceField\\SkelIceMagician\\Idle\\Right\\SkelIceMagicianIdle.bmp");
		ani->CreateAnimation(L"SkelIceMagicianRightIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 30.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);

		texture = Resources::Load<Texture>(L"SkelIceMagicianLeftIdle", L"..\\Resources\\Enemy\\IceField\\SkelIceMagician\\Idle\\Left\\SkelIceMagicianIdle.bmp");
		ani->CreateAnimation(L"SkelIceMagicianLeftIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 30.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);

		texture = Resources::Load<Texture>(L"SkelIceMagicianRightAttack", L"..\\Resources\\Enemy\\IceField\\SkelIceMagician\\Attack\\Right\\SkelIceMagicianAttackSheet.bmp");
		ani->CreateAnimation(L"SkelIceMagicianRightAttack", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 30.f), Math::Vector2<float>(0.f, 0.f), 12, 0.1f);

		texture = Resources::Load<Texture>(L"SkelIceMagicianLeftAttack", L"..\\Resources\\Enemy\\IceField\\SkelIceMagician\\Attack\\Left\\SkelIceMagicianAttackSheet.bmp");
		ani->CreateAnimation(L"SkelIceMagicianLeftAttack", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 30.f), Math::Vector2<float>(0.f, 0.f), 12, 0.1f);

		// Sound
		mCircleSound = Resources::Load<Sound>(L"CircleSound", L"..\\Resources\\Sound\\Enemy\\IceField\\IceMagician\\ice.wav");
		mIceBreakSound = Resources::Load<Sound>(L"IceBreakSound", L"..\\Resources\\Sound\\Enemy\\IceField\\IceMagician\\iceMagicAttack.wav");
	}

	SkelIceMagician::~SkelIceMagician()
	{
	}

	void SkelIceMagician::Initialize()
	{
	}

	void SkelIceMagician::Update()
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

		if(mMagicCircle!=nullptr)
			Destroy(mMagicCircle);


		float thinktime = GetCheckTime();
		SetCheckTime(thinktime += Time::GetDeltaTime());
		Transform* tr = GetComponent<Transform>();
		Transform* playertr = nullptr;
		Animator* ani = GetComponent<Animator>();

		//playanimation
		playertr = GetTarget()->GetComponent<Transform>();
		if (GetDelayTime() < thinktime)
		{
			// playanimation
			if (mIsRight)
			{
				ani->PlayAnimation(L"SkelIceMagicianRightAttack", false);
			}
			else
			{
				ani->PlayAnimation(L"SkelIceMagicianLeftAttack", false);
			}
			// circleanimation
			mMagicCircle = object::Instantiate<GameObject>(enums::eLayerType::BackGround);
			mPlayerPos = playertr->Getpos();
			mMagicCircle->GetComponent<Transform>()->SetPos(mPlayerPos);
			mMagicCircle->GetComponent<Transform>()->SetScale(Math::Vector2<float>(124.f, 144.f));
			Animator* circleani = mMagicCircle->AddComponent<Animator>();
			Texture* texture = Resources::Load<Texture>(L"MagicCircle", L"..\\Resources\\Enemy\\IceField\\SkelIceMagician\\Attack\\AttackFX\\IceMagicianCircle.bmp");
			circleani->CreateAnimation(L"MagicCircle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(31.f, 36.f), Math::Vector2<float>(0.f, 0.f), 36, 0.05f);
			circleani->PlayAnimation(L"MagicCircle", false);
			SetCheckTime(0.f);
			SetState(eState::Attack);
			mCircleSound->Play(false);
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
				ani->PlayAnimation(L"SkelIceMagicianLeftIdle",true);
				mIsRight = false;
			}
			else
			{
				ani->PlayAnimation(L"SkelIceMagicianRightIdle",true);
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
		if (GetSubDelayTime() < chargetime)
		{
			// bullet
			for (int i = 0;i < 6;i++)
			{
				Bullet* bullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
				Transform* bullettr = bullet->GetComponent<Transform>();
				Collider* bulletcol = bullet->AddComponent<Collider>();
				SpriteRenderer* sr = bullet->AddComponent<SpriteRenderer>();
				Texture* texture = Resources::Load<Texture>(L"IceBullet"+std::to_wstring(i), L"..\\Resources\\Enemy\\IceField\\SkelIceMagician\\Attack\\IceBullet.png");
				sr->SetImg(texture);
				bulletcol->SetScale(Math::Vector2<float>(36.f, 36.f));
				bullettr->SetPos(mPlayerPos);
				bullettr->SetScale(Math::Vector2<float>(36.f, 72.f));
				bullet->SetDeleteTime(10.f);
				bullet->SetRadian(1.57f + 1.04f * i);
				texture->SetDegree(60.f * i);
				bullet->SetStop(false);
				SetSubCheckTime(0.f);
			}
			//circle animation delete
			SetState(eState::Idle);
			mIceBreakSound->Play(false);
		}
	}

	void SkelIceMagician::Dead()
	{
		if (mAttack != nullptr)
		{
			CollisionManager::ForceExit(GetComponent<Collider>(), mAttack->GetComponent<Collider>());
		}
		Destroy(this);
	}
}