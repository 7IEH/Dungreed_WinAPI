#include "EHBulletCreator.h"
#include "EHBullet.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHBoss.h"

namespace EH
{
	BulletCreator::BulletCreator()
		:
		  mDegree(0.f)
		, mType(AttackType::None)
	{
		mBulletSound = Resources::Load<Sound>(L"BelialSound", L"..\\Resources\\Sound\\Enemy\\JailField\\Belial\\BelialBullet.wav");
		Collider* col = AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(50.f, 50.f));
	}

	BulletCreator::~BulletCreator()
	{
	}

	void BulletCreator::Initialize()
	{
	}

	void BulletCreator::Update()
	{
		GameObject::Update();

		switch (mType)
		{
		case EH::AttackType::Barrage:
			Barrage();
			break;
		case EH::AttackType::None:
			break;
		default:
			break;
		}
	}

	void BulletCreator::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BulletCreator::Barrage()
	{
		float checktime = GetCheckTime();
		float checktime2 = GetSubCheckTime();
		SetCheckTime(checktime += Time::GetDeltaTime());
		SetSubCheckTime(checktime2 += Time::GetDeltaTime());
		if (3.f < checktime)
		{
			mType = AttackType::None;
			SetCheckTime(0.f);
			mOwner->SetCheck(mOwner->GetCheck() + 1);
		}

		if (0.1f < checktime2)
		{
			SetSubCheckTime(0.f);
			Bullet* bullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
			Transform* tr = GetComponent<Transform>();
			Transform* bullettr = bullet->GetComponent<Transform>();
			Collider* bulletcol = bullet->AddComponent<Collider>();
			Animator* bulletani = bullet->AddComponent<Animator>();
			Texture* texture = Resources::Load<Texture>(L"BelialBullet", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\Attack\\Barrage\\BossBullet.bmp");
			bullettr->SetPos(tr->Getpos());
			bullettr->SetScale(Math::Vector2<float>(52.f, 52.f));
			bulletcol->SetScale(Math::Vector2<float>(52.f, 52.f));
			bulletani->CreateAnimation(L"BelialBullet", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(13.f, 13.f), Math::Vector2<float>(0.f, 0.f), 2, 0.1f);
			bulletani->PlayAnimation(L"BelialBullet", true);
			bullet->SetDeleteTime(10.f);
			bullet->SetStop(false);
			bullet->SetRadian((mDegree) * (3.14f / 180.f));
			mBulletSound->Play(false);
		}
	}
}