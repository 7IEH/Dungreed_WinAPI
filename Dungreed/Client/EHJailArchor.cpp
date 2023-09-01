#include "EHJailArchor.h"
#include "EHPlayer.h"
#include "EHBullet.h"
#include "EHObject.h"
#include "EHCamera.h"
#include "EHWeapon.h"
#include "EHCollisionManager.h"
#include "EHDetection.h"
#include "EHResources.h"
#include "EHDamageEffect.h"
#include "EHImageObject.h"

namespace EH
{
	UINT JailArchor::mBowCount = 0;

	JailArchor::JailArchor()
		:
		  mAttack(nullptr)
		, mIsRight(true)
	{
		SetDelayTime(3.f);
		SetSubDelayTime(1.f);
		SetHP(40.f);
		Transform* tr = GetComponent<Transform>();
		mDect = object::Instantiate<Detection>(enums::eLayerType::Detect);
		Collider* dectcol = mDect->AddComponent<Collider>();
		dectcol->SetScale(Math::Vector2<float>(600.f, 600.f));
		dectcol->SetAffectedCamera(true);

		mBow = object::Instantiate<Weapon>(enums::eLayerType::Sword);
		mBow->GetComponent<Transform>()->SetScale(Math::Vector2<float>(68.f, 52.f));
		Animator* ani = mBow->AddComponent<Animator>();
		Texture* texture = Resources::Load<Texture>(L"BowIdle" + std::to_wstring(mBowCount), L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Archor\\OakBow.png");
		mBowImg = texture;
		ani->CreateAnimation(L"BowIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(17.f, 13.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		texture = Resources::Load<Texture>(L"BowAttack" + std::to_wstring(mBowCount), L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Archor\\OakBowSheet.png");
		mBowAttackImg = texture;
		ani->CreateAnimation(L"BowAttack", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(17.f, 13.f), Math::Vector2<float>(0.f, 0.f), 6, 0.4f);

		mBowDrawSound = Resources::Load<Sound>(L"BowDraw", L"..\\Resources\\Sound\\Enemy\\JailField\\GreySkel\\Archor\\bowdraw.wav");
		mBowAttackSound = Resources::Load<Sound>(L"BowShot", L"..\\Resources\\Sound\\Enemy\\JailField\\GreySkel\\Archor\\bowshot.wav");
		mBowCount++;
	}

	JailArchor::~JailArchor()
	{
		Destroy(mDect);
		Destroy(mBow);
	}

	void JailArchor::Initialize()
	{
	}

	void JailArchor::Update()
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
		mDect->GetComponent<Transform>()->SetPos(tr->Getpos());
	}

	void JailArchor::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void JailArchor::OnCollisionEnter(Collider* other)
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

	void JailArchor::OnCollisionStay(Collider* other)
	{
	}

	void JailArchor::OnCollisionExit(Collider* other)
	{
	}

	void JailArchor::Idle()
	{
		if (GetHP() <= 0.f)
		{
			SetState(eState::Dead);
		}
		
		Transform* tr = GetComponent<Transform>();
		if (GetTarget()!=nullptr)
		{
			float thinktime = GetCheckTime();
			SetCheckTime(thinktime += Time::GetDeltaTime());
			Transform* playertr = GetTarget()->GetComponent<Transform>();
			if (GetDelayTime() < thinktime)
			{
				SetState(eState::Attack);
				// 각도 저장
				float radian = Math::Radian(playertr->Getpos(), tr->Getpos());
				mBowradian = radian;
				// Bow aniamtion play
				Animator* ani = mBow->GetComponent<Animator>();
				if (mIsRight)
				{
					radian *= 180 / 3.14f;
					mBowAttackImg->SetDegree(radian);
					ani->PlayAnimation(L"BowAttack", false);
				}
				else
				{
					radian *= 180 / 3.14f;
					mBowAttackImg->SetDegree(radian);
					ani->PlayAnimation(L"BowAttack", false);
				}
				
				// Bow Sound play
				mBowDrawSound->Play(false);
				
				SetCheckTime(0.f);
			}
			else
			{				
				if (GetTarget() != nullptr)
				{
					Animator* ani = GetComponent<Animator>();
					Math::Vector2<float> pos = tr->Getpos();
					Math::Vector2<float> playerpos = playertr->Getpos();
					// archor 모습 변경
					if (pos.x < playerpos.x)
					{
						mIsRight = true;
						ani->PlayAnimation(L"GreySkelRightIdle", true);
					}
					else
					{
						mIsRight = false;
						ani->PlayAnimation(L"GreySkelLeftIdle", true);
					}

					// Bow 변경
					if (mIsRight)
					{
						mBow->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x + 5.f, tr->Getpos().y+30.f));
						float radian = Math::Radian(playertr->Getpos(), tr->Getpos());
						radian *= 180 / 3.14f;
						mBowImg->SetDegree(radian);
					}
					else
					{
						mBow->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x - 5.f, tr->Getpos().y+30.f));
						float radian = Math::Radian(tr->Getpos(), playertr->Getpos());
						radian *= 180 / 3.14f;
						mBowImg->SetDegree(radian + 180);
					}
					mBow->GetComponent<Animator>()->PlayAnimation(L"BowIdle", true);
				}
			}
		}
		else
		{
			SetTarget(mDect->passthetarget());
			if (mIsRight)
				mBow->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x + 5.f, tr->Getpos().y + 30.f));
			else
				mBow->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x - 5.f, tr->Getpos().y + 30.f));

			mBow->GetComponent<Animator>()->PlayAnimation(L"BowIdle", true);
		}
	}

	void JailArchor::Attack()
	{
		if (GetHP() <= 0.f)
		{
			SetState(eState::Dead);
		}

		float chargetime = GetSubCheckTime();
		SetSubCheckTime(chargetime += Time::GetDeltaTime());
		if (GetSubDelayTime() < chargetime)
		{
			mBowAttackSound->Play(false);
			Bullet* arrow = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
			arrow->SetPass(false);
			Transform* archortr = GetComponent<Transform>();
			Transform* arrowtr = arrow->GetComponent<Transform>();
			Math::Vector2<float> archorpos = archortr->Getpos();
			arrow->SetStop(false);
			arrowtr->SetPos(Math::Vector2<float>(archorpos.x, archorpos.y));
			arrowtr->SetScale(Math::Vector2<float>(20.f, 42.f));
			Texture* texture = Resources::Load<Texture>(L"Arrow", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Archor\\Arrow00.png");
			texture->SetDegree(mBowradian * 180 / 3.14f + 90.f);
			SpriteRenderer* sr = arrow->AddComponent<SpriteRenderer>();
			sr->SetImg(texture);
			arrow->SetRadian(mBowradian);
			arrow->AddComponent<Collider>();
			arrow->GetComponent<Collider>()->SetScale(Math::Vector2<float>(40.f, 40.f));
			arrow->SetDeleteTime(10.f);
			arrow->SetSpeed(3.f);
			SetState(eState::Idle);
			SetSubCheckTime(0.f);
		}
	}

	void JailArchor::Dead()
	{
		if (mAttack != nullptr)
		{
			CollisionManager::ForceExit(GetComponent<Collider>(), mAttack->GetComponent<Collider>());
		}
		Destroy(this);

	}
}

