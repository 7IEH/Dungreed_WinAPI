#include "EHBigGrayIceSkel.h"
#include "EHDetection.h"
#include "EHWeapon.h"
#include "EHSound.h"
#include "EHCollisionManager.h"
#include "EHObject.h"
#include "EHBullet.h"
#include "EHPlayer.h"
#include "EHResources.h"

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
		SetSubDelayTime(2.f);

		// Weapon Col
		mBullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
		Collider* bulletcol = mBullet->AddComponent<Collider>();
		bulletcol->SetScale(Math::Vector2<float>(100.f, 100.f));
		bulletcol->SetType(Collider::eColliderType::Circle);
		mBullet->SetDelete(false);
		bulletcol->enabled(false);

		//Animator
		Animator* ani = AddComponent<Animator>();
		Texture* texture = Resources::Load<Texture>(L"BigGreyIceSkelRightIdle", L"..\\Resources\\Enemy\\IceField\\BigGrayIceSkel\\Idle\\Right\\BigGreyIceSkelIdle.bmp");
		ani->CreateAnimation(L"BigGreyIceSkelRightIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(33.f, 30.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

		texture = Resources::Load<Texture>(L"BigGreyIceSkelLeftIdle", L"..\\Resources\\Enemy\\IceField\\BigGrayIceSkel\\Idle\\Left\\BigGreyIceSkelIdle.bmp");
		ani->CreateAnimation(L"BigGreyIceSkelLeftIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(33.f, 30.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

		texture = Resources::Load<Texture>(L"BigGreyIceSkelRightAttack", L"..\\Resources\\Enemy\\IceField\\BigGrayIceSkel\\Attack\\Normal\\Right\\BigGrayIceSkelAttack.bmp");
		ani->CreateAnimation(L"BigGreyIceSkelRightAttack", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(70.f, 48.f), Math::Vector2<float>(0.f, -36.f), 13, 0.1f);

		texture = Resources::Load<Texture>(L"BigGreyIceSkelLeftAttack", L"..\\Resources\\Enemy\\IceField\\BigGrayIceSkel\\Attack\\Normal\\Left\\BigGreyIceSkelAttack.bmp");
		ani->CreateAnimation(L"BigGreyIceSkelLeftAttack", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(70.f, 48.f), Math::Vector2<float>(0.f, -36.f), 13, 0.1f);

		texture = Resources::Load<Texture>(L"BigGreyIceSkelRightMove", L"..\\Resources\\Enemy\\IceField\\BigGrayIceSkel\\Move\\Right\\BigGrayIceSkelMove.bmp");
		ani->CreateAnimation(L"BigGreyIceSkelRightMove", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(33.f, 30.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);

		texture = Resources::Load<Texture>(L"BigGreyIceSkelLeftMove", L"..\\Resources\\Enemy\\IceField\\BigGrayIceSkel\\Move\\Left\\BigGrayIceSkelMove.bmp");
		ani->CreateAnimation(L"BigGreyIceSkelLeftMove", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(33.f, 30.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);

		texture = Resources::Load<Texture>(L"BigGreyIceSkelRightSkill", L"..\\Resources\\Enemy\\IceField\\BigGrayIceSkel\\Attack\\Skill\\Right\\BigGrayIceSkelSkill.bmp");
		ani->CreateAnimation(L"BigGreyIceSkelRightSkill", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(40.f, 40.f), Math::Vector2<float>(0.f, -20.f), 13, 0.1f);

		texture = Resources::Load<Texture>(L"BigGreyIceSkelLeftSkill", L"..\\Resources\\Enemy\\IceField\\BigGrayIceSkel\\Attack\\Skill\\Left\\BigGrayIceSkelSkill.bmp");
		ani->CreateAnimation(L"BigGreyIceSkelLeftSkill", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(40.f, 40.f), Math::Vector2<float>(0.f, -20.f), 13, 0.1f);


		ani->PlayAnimation(L"BigGreyIceSkelRightIdle", true);
		// Rigidbody
		Rigidbody* rigid = AddComponent<Rigidbody>();

		Collider* col = AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(132.f, 120.f));
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

		Animator* ani = GetComponent<Animator>();

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
				if (mIsRight)
				{
					tr->SetScale(Math::Vector2<float>(160.f, 160.f));
					ani->PlayAnimation(L"BigGreyIceSkelRightSkill", false);
				}
				else
				{
					tr->SetScale(Math::Vector2<float>(160.f, 160.f));
					ani->PlayAnimation(L"BigGreyIceSkelLeftSkill", false);
				}
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
					// playanimation
					if (mIsRight)
					{
						tr->SetScale(Math::Vector2<float>(280.f, 192.f));
						ani->PlayAnimation(L"BigGreyIceSkelRightAttack", false);
					}
					else
					{
						tr->SetScale(Math::Vector2<float>(280.f, 192.f));
						ani->PlayAnimation(L"BigGreyIceSkelLeftAttack", false);
					}
				}
				else
				{
					Rigidbody* rigid = GetComponent<Rigidbody>();
					if (playerpos.x < pos.x)
					{
						// Left run
						rigid->AddForce(Math::Vector2<float>(-200.f, 0.f));
						ani->PlayAnimation(L"BigGreyIceSkelLeftMove", true);

						tr->SetPos(pos);
						mIsRight = false;
					}
					else
					{
						// Right run
						ani->PlayAnimation(L"BigGreyIceSkelRightMove", true);
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
				tr->SetScale(Math::Vector2<float>(132.f, 120.f));
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
					bullettr2->SetScale(Math::Vector2<float>(36.f, 72.f));
					SpriteRenderer* sr = bullet->AddComponent<SpriteRenderer>();
					Texture* texture = Resources::Load<Texture>(L"IceBullet" + std::to_wstring(mCheck1), L"..\\Resources\\Enemy\\IceField\\SkelIceMagician\\Attack\\IceBullet.png");
					sr->SetImg(texture);
					bulletcol2->SetScale(Math::Vector2<float>(36.f, 36.f));
					float radian = Math::Radian(playertr->Getpos(), tr->Getpos());
					texture->SetDegree(radian * (180.f / 3.14f) - 90.f);
					bullet->SetStop(false);
					bullet->SetRadian(radian);
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
				tr->SetScale(Math::Vector2<float>(132.f, 120.f));
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