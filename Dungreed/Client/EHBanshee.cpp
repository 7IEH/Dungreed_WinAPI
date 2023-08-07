#include "EHBanshee.h"
#include "EHBullet.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHWeapon.h"
#include "EHCollisionManager.h"
#include "EHCoin.h"
#include "EHFairy.h"

namespace EH
{
	Banshee::Banshee()
		:
		 mAttack(nullptr)
	{
		Collider* col = AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(80.f, 80.f));
		SetHP(40.f);
	}

	Banshee::~Banshee()
	{
	}

	void Banshee::Initialize()
	{
	}

	void Banshee::Update()
	{
		GameObject::Update();

		switch (GetState())
		{
		case eState::Idle:
			Idle();
			break;
		case eState::Attack:
			Attack();
			break;
		case eState::Dead:
			Dead();
			break;
		default:
			break;
		}
	}

	void Banshee::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Banshee::OnCollisionEnter(Collider* other)
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

	void Banshee::OnCollisionStay(Collider* other)
	{
	}

	void Banshee::OnCollisionExit(Collider* other)
	{
	}

	void Banshee::Idle()
	{
		float checktime = GetCheckTime();
		SetCheckTime(checktime += Time::GetDeltaTime());
		if (GetHP() <= 0)
		{
			SetState(eState::Dead);
		}
		else
		{
			if (GetComponent<Animator>()->GetActiveAnimation()->IsComplete() == true)
				GetComponent<Animator>()->PlayAnimation(L"BansheeIdle", true);
			if (GetDelayTime() < checktime)
			{
				GetComponent<Animator>()->PlayAnimation(L"BansheeAttack", false);
				SetState(eState::Attack);
				SetCheckTime(0.f);
			}
		}
	}

	void Banshee::Attack()
	{
		if (GetHP() <= 0)
		{
			SetState(eState::Dead);
		}

		for (size_t i = 0; i < 12; i++)
		{
			Bullet* bullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
			Transform* bullettr = bullet->GetComponent<Transform>();
			Transform* bansheetr = GetComponent<Transform>();
			Math::Vector2<float> bansheepos = bansheetr->Getpos();
			bullettr->SetPos(Math::Vector2<float>(bansheepos.x, bansheepos.y));
			bullettr->SetScale(Math::Vector2<float>(52.f, 64.f));
			Texture* texture = Resources::Load<Texture>(L"BansheeBullet", L"..\\Resources\\Enemy\\JailField\\Banshee\\Attack\\BansheeBulletSheet.bmp");
			bullet->AddComponent<Animator>();
			bullet->AddComponent<Collider>();
			bullet->GetComponent<Collider>()->SetScale(Math::Vector2(52.f, 64.f));
			bullet->GetComponent<Animator>()->CreateAnimation(L"BansheeBullet", texture,
				Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(13.f, 16.f),
				Math::Vector2<float>(0.f, 0.f), 4, 0.1f);
			bullet->GetComponent<Animator>()->PlayAnimation(L"BansheeBullet", true);
			bullet->SetDamage(5.f);
			// 30degree
			bullet->SetDeleteTime(2.f);
			bullet->SetRadian(0.52 * i);
			bullet->SetStop(false);
		}
		SetState(eState::Idle);
	}

	void Banshee::Dead()
	{
		CollisionManager::ForceExit(this->GetComponent<Collider>(), mAttack->GetComponent<Collider>());

		Transform* enemytr = GetComponent<Transform>();
		Coin* coin = object::Instantiate<Coin>(enums::eLayerType::Item);
		Math::Vector2<float> pos = enemytr->Getpos();
		Transform* tr = coin->GetComponent<Transform>();
		tr->SetPos(Math::Vector2<float>(pos.x-30.f, pos.y));
		tr->SetScale(Math::Vector2<float>(28.f, 28.f));

	    Fairy* fairy = object::Instantiate<Fairy>(enums::eLayerType::Item);
		fairy->SetHeal(10.f);
		pos = enemytr->Getpos();
		tr = fairy->GetComponent<Transform>();
		tr->SetPos(Math::Vector2<float>(pos.x, pos.y));
		tr->SetScale(Math::Vector2<float>(80.f, 80.f));
		Texture* texture = Resources::Load<Texture>(L"FairyM", L"..\\Resources\\Item\\Fairy\\FairyMSheet.bmp");
		Animator* animator = fairy ->AddComponent<Animator>();
		animator->CreateAnimation(L"FairyM", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 20.f), Math::Vector2<float>(0.f, 0.f), 16, 0.1f);
		animator->PlayAnimation(L"FairyM", true);

		Destroy(this);
	}
}