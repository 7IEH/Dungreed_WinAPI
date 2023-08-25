#include "EHIcePillar.h"
#include "EHResources.h"
#include "EHNiflheim.h"
#include "EHObject.h"
#include "EHBullet.h"
#include "EHWeapon.h"

namespace EH
{
	UINT IcePillar::mNum = 0;
	UINT IcePillar::mCheck1 = 0;
	IcePillar::IcePillar()
		:
		mDegree(0.f)
		, mType(ePillarAttack::None)
		, mAttack(nullptr)
	{
		Transform* tr = GetComponent<Transform>();
		Animator* ani = AddComponent<Animator>();
		Texture* texture = Resources::Load<Texture>(L"IcePillar" + std::to_wstring(mCheck1), L"..\\Resources\\Enemy\\Boss\\Niflheim\\UI\\IcePillar.png");
		tr->SetScale(Math::Vector2<float>(248.f, 132.f));
		ani->CreateAnimation(L"IcePillar", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(62.f, 33.f), Math::Vector2<float>(0.f, 0.f), 20, 0.1f);
		texture = Resources::Load<Texture>(L"IcePillarDestroy" + std::to_wstring(mCheck1), L"..\\Resources\\Enemy\\Boss\\Niflheim\\UI\\IcePillarDestroy.png");
		ani->CreateAnimation(L"IcePillarDestroy", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(62.f, 33.f), Math::Vector2<float>(0.f, 0.f), 3, 0.3f);
		ani->PlayAnimation(L"IcePillar",false);
		Collider* col = AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(40.f, 40.f));
		mCheck1++;

		mIceBulletSound = Resources::Load<Sound>(L"IceBulletSound", L"..\\Resources\\Sound\\Enemy\\public\\Fantasy_Game_Magic_Ice_Instant_Cast_Spell_B _Niflheimfire.wav");
	}

	IcePillar::~IcePillar()
	{
	}

	void IcePillar::Initialize()
	{
	}

	void IcePillar::Update()
	{
		GameObject::Update();

		Animator* ani = GetComponent<Animator>();
		Texture* texture = ani->GetActiveAnimation()->GetTexture();
		texture->SetDegree(mDegree);

		switch (mType)
		{
		case EH::ePillarAttack::Bullet:
			BulletP();
			break;
		case EH::ePillarAttack::Barrage:
			Barrage();
			break;
		case EH::ePillarAttack::None:
			break;
		case EH::ePillarAttack::Dead:
			Dead();
			break;
		default:
			break;
		}
	}

	void IcePillar::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void IcePillar::OnCollisionEnter(Collider* other)
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

	void IcePillar::OnCollisionStay(Collider* other)
	{
	}

	void IcePillar::OnCollisionExit(Collider* other)
	{
	}

	void IcePillar::BulletP()
	{
		float checktime = GetCheckTime();
		SetCheckTime(checktime += Time::GetDeltaTime());

		float createtime = GetSubCheckTime();
		SetSubCheckTime(createtime += Time::GetDeltaTime());
		if (2.f < checktime)
		{
			mOwner->SetStop(false);
			mOwner->SetCheck(mOwner->GetCheck() + 1);
			SetCheckTime(0.f);
			mType = ePillarAttack::None;
		}
		Transform* tr = GetComponent<Transform>();
		float radian = Math::Radian(mTarget, tr->Getpos());


		if (0.1f < createtime)
		{
			mNum++;
			SetSubCheckTime(0.f);
			Bullet* bullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
			SpriteRenderer* sr = bullet->AddComponent<SpriteRenderer>();
			Texture* texture = Resources::Load<Texture>(L"Icebullet" + std::to_wstring(mNum), L"..\\Resources\\Enemy\\IceField\\SkelIceMagician\\Attack\\IceBullet.png");
			Collider* col = bullet->AddComponent<Collider>();
			sr->SetImg(texture);
			Transform* bullettr = bullet->GetComponent<Transform>();
			bullettr->SetPos(tr->Getpos());

			texture->SetDegree((radian * 180.f / 3.14f) + 90.f);

			col->SetScale(Math::Vector2<float>(40.f, 40.f));
			bullettr->SetScale(Math::Vector2<float>(36.f, 72.f));

			bullet->SetRadian(radian);
			bullet->SetStop(false);
			bullet->SetDeleteTime(10.f);
			mIceBulletSound->Play(false);
		}
	}

	void IcePillar::Barrage()
	{
		float checktime = GetCheckTime();
		SetCheckTime(checktime += Time::GetDeltaTime());

		float createtime = GetSubCheckTime();
		SetSubCheckTime(createtime += Time::GetDeltaTime());
		if (5.f < checktime)
		{
			mOwner->SetStop(false);
			mOwner->SetCheck(mOwner->GetCheck() + 1);
			SetCheckTime(0.f);
			mType = ePillarAttack::None;
		}
		Transform* tr = GetComponent<Transform>();

		if (0.05f < createtime)
		{
			mNum++;
			SetSubCheckTime(0.f);
			Bullet* bullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
			SpriteRenderer* sr = bullet->AddComponent<SpriteRenderer>();
			Texture* texture = Resources::Load<Texture>(L"Icebullet" + std::to_wstring(mNum), L"..\\Resources\\Enemy\\IceField\\SkelIceMagician\\Attack\\IceBullet.png");
			Collider* col = bullet->AddComponent<Collider>();
			sr->SetImg(texture);
			Transform* bullettr = bullet->GetComponent<Transform>();
			bullettr->SetPos(tr->Getpos());

			texture->SetDegree(mDegree + 90.f);

			col->SetScale(Math::Vector2<float>(40.f, 40.f));
			bullettr->SetScale(Math::Vector2<float>(36.f, 72.f));

			bullet->SetRadian(mDegree * (3.14f / 180.f));
			bullet->SetStop(false);
			bullet->SetDeleteTime(10.f);
			mIceBulletSound->Play(false);
		}
	}

	void IcePillar::Dead()
	{
		float checktime = GetCheckTime();
		SetCheckTime(checktime += Time::GetDeltaTime());

		if (1.f < checktime)
		{
			Destroy(this);
		}
	}
}