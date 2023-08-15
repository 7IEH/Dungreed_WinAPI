#include "EHBigGrayIceSkel.h"
#include "EHDetection.h"
#include "EHWeapon.h"
#include "EHSound.h"
#include "EHCollisionManager.h"
#include "EHObject.h"
#include "EHBullet.h"
#include "EHPlayer.h"

namespace EH
{
	BigGrayIceSkel::BigGrayIceSkel()
		:
		  mAttack(nullptr)
		, mIsRight(true)
		, mIsSkill(false)
		, mCheck1(0)
	{
		SetHP(40.f);
		
		// Dect
		mDect = object::Instantiate<Detection>(enums::eLayerType::Detect);
		Collider* dectcol = mDect->AddComponent<Collider>();
		dectcol->SetScale(Math::Vector2<float>(500.f, 100.f));

		// Delay
		SetDelayTime(3.5f);
		SetSubDelayTime(4.f);

		// Weapon Col
		mBullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
		Collider* bulletcol = mBullet->AddComponent<Collider>();
		bulletcol->SetScale(Math::Vector2<float>(100.f, 100.f));
		bulletcol->SetType(Collider::eColliderType::Circle);
		mBullet->SetDelete(false);
		bulletcol->enabled(false);

		// Rigidbody
		Rigidbody* rigid = AddComponent<Rigidbody>();

		Collider* col = AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(400.f, 300.f));
	}

	BigGrayIceSkel::~BigGrayIceSkel()
	{
		Destroy(mDect);
		Destroy(mBullet);
	}

	void BigGrayIceSkel::Initialize()
	{
	}

	void BigGrayIceSkel::Update()
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
		if (mDect)
			mDect->GetComponent<Transform>()->SetPos(tr->Getpos());
	}

	void BigGrayIceSkel::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BigGrayIceSkel::OnCollisionEnter(Collider* other)
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

	void BigGrayIceSkel::OnCollisionStay(Collider* other)
	{
	}

	void BigGrayIceSkel::OnCollisionExit(Collider* other)
	{
	}

	void BigGrayIceSkel::Idle()
	{
		if (GetHP() <= 0)
		{
			SetState(eState::Dead);
		}

		mBullet->GetComponent<Collider>()->enabled(false);

		Transform* bullettr = mBullet->GetComponent<Transform>();
		Transform* tr = GetComponent<Transform>();

		float thinktime = GetCheckTime();
		SetCheckTime(thinktime += Time::GetDeltaTime());
		mIsSkill = false;


		if (mIsRight)
		{
			bullettr->SetPos(Math::Vector2<float>(tr->Getpos().x + 50.f, tr->Getpos().y + 30.f));
		}
		else
		{
			bullettr->SetPos(Math::Vector2<float>(tr->Getpos().x - 50.f, tr->Getpos().y + 30.f));
		}

		if (GetTarget() != nullptr)
		{
			if (mDect->GetComponent<Collider>()->GetEnabled())
			{
				mDect->GetComponent<Collider>()->enabled(false);
			}

			if (GetDelayTime() < thinktime)
			{
				// playanimation
				

				mIsSkill = true;
				SetCheckTime(0.f);
				SetState(eState::Attack);
			}
			else
			{
				Transform* playertr = GetTarget()->GetComponent<Transform>();

				Math::Vector2<float> playerpos = playertr->Getpos();
				Math::Vector2<float> pos = tr->Getpos();

				if (fabs(playerpos.x-pos.x) <= 50.f)
				{
					SetCheckTime(0.f);
					SetState(eState::Attack);
					// 공격 애니메이션
				}
				else
				{
					Rigidbody* rigid = GetComponent<Rigidbody>();
					if (playerpos.x < pos.x)
					{
						// Left run
						rigid->AddForce(Math::Vector2<float>(-200.f, 0.f));
						//ani->PlayAnimation(L"GreySkelLeftWalk", true);

						tr->SetPos(pos);
						mIsRight = false;
					}
					else
					{
						// Right run
						//ani->PlayAnimation(L"GreySkelRightWalk", true);
						rigid->AddForce(Math::Vector2<float>(200.f, 0.f));
						tr->SetPos(pos);
						mIsRight = true;
					}
				}
			}
		}
		else
		{
			SetTarget(mDect->passthetarget());
		}

		
	}

	void BigGrayIceSkel::Attack()
	{
		Rigidbody* rigid = GetComponent<Rigidbody>();
		rigid->SetVeclocity(Math::Vector2<float>(0.f, 0.f));
		Transform* tr = GetComponent<Transform>();
		Transform* playertr = GetTarget()->GetComponent<Transform>();
		if (GetHP() <= 0)
		{
			SetState(eState::Dead);
		}

		float chargetime = GetSubCheckTime();
		SetSubCheckTime(chargetime += Time::GetDeltaTime());

		if (mIsSkill)
		{
			if (mCheck1 == 6)
			{
				mCheck1 = 0;
				SetState(eState::Idle);
				SetSubCheckTime(0.f);
			}
			else
			{
				if (0.3f < chargetime)
				{
					Bullet* bullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
					Transform* bullettr2 = bullet->GetComponent<Transform>();
					Collider* bulletcol2 = bullet->AddComponent<Collider>();
					bullettr2->SetPos(tr->Getpos());
					//bullettr2->SetScale(Math::Vector2<float>(0.f, 0.f));
					bulletcol2->SetScale(Math::Vector2<float>(40.f, 40.f));
					bullet->SetStop(false);
					bullet->SetRadian(Math::Radian(playertr->Getpos(),tr->Getpos()));
					bullet->SetDeleteTime(10.f);
					bullet->SetPass(false);
					SetSubCheckTime(0.f);
					mCheck1++;
				}
			}
		}
		else
		{
			Collider* bulletcol = mBullet->GetComponent<Collider>();
			bulletcol->enabled(true);

			if (GetSubDelayTime() < chargetime)
			{
				SetState(eState::Idle);
				SetSubCheckTime(0.f);
			}
		}
	}

	void BigGrayIceSkel::Dead()
	{
		CollisionManager::ForceExit(GetComponent<Collider>(), mAttack->GetComponent<Collider>());
		Destroy(this);
	}
}