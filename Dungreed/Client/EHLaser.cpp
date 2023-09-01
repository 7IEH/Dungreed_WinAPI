#include "EHLaser.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHPlayer.h"
#include "EHObjdata.h"

namespace  EH
{
	Laser::Laser()
		:
		  mDeleteTime(2.f)
		, mCheckTime(0.f)
		, mIsRight(true)
	{
		Animator* ani = nullptr;
		Transform* tr = nullptr;
		Texture* texture = nullptr;

		mRightLaser[0] = object::Instantiate<GameObject>(enums::eLayerType::BackGround);
		tr = mRightLaser[0]->GetComponent<Transform>();
		tr->SetScale(Math::Vector2<float>(128.f, 220.f));
		texture = Resources::Load<Texture>(L"LaserRighthead", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\RightLaser\\SkellBossLaserHeadSheet.bmp");
		ani = mRightLaser[0]->AddComponent<Animator>();
		ani->CreateAnimation(L"LaserRighthead", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 55.f), Math::Vector2<float>(0.f, 0.f), 7, 0.2f);

		mLeftLaser[0] = object::Instantiate<GameObject>(enums::eLayerType::BackGround);
		tr = mLeftLaser[0]->GetComponent<Transform>();
		tr->SetScale(Math::Vector2<float>(128.f, 220.f));
		texture = Resources::Load<Texture>(L"LaserLefthead", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\LeftLaser\\SkellBossLaserHeadSheet.bmp");
		ani = mLeftLaser[0]->AddComponent<Animator>();
		ani->CreateAnimation(L"LaserLefthead", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 55.f), Math::Vector2<float>(0.f, 0.f), 7, 0.2f);

		for (int i = 1;i < 10;i++)
		{
			mRightLaser[i] = object::Instantiate<GameObject>(enums::eLayerType::BackGround);
			tr = mRightLaser[i]->GetComponent<Transform>();
			tr->SetScale(Math::Vector2<float>(128.f, 220.f));
			texture = Resources::Load<Texture>(L"LaserRightBody", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\RightLaser\\SkellBossLaserBodySheet.bmp");
			ani = mRightLaser[i]->AddComponent<Animator>();
			ani->CreateAnimation(L"LaserRightBody", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 55.f), Math::Vector2<float>(0.f, 0.f), 7, 0.2f);

			mLeftLaser[i] = object::Instantiate<GameObject>(enums::eLayerType::BackGround);
			tr = mLeftLaser[i]->GetComponent<Transform>();
			tr->SetScale(Math::Vector2<float>(128.f, 220.f));
			texture = Resources::Load<Texture>(L"LaserLeftBody", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\LeftLaser\\SkellBossLaserBodySheet.bmp");
			ani = mLeftLaser[i]->AddComponent<Animator>();
			ani->CreateAnimation(L"LaserLeftBody", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 55.f), Math::Vector2<float>(0.f, 0.f), 7, 0.2f);
		}

		mHitSound = Resources::Load<Sound>(L"playerhitsound", L"..\\Resources\\Sound\\Enemy\\public\\Hit_Player.wav");
	}

	Laser::~Laser()
	{
		for (GameObject* obj : mRightLaser)
		{
			Destroy(obj);
		}

		for (GameObject* obj : mLeftLaser)
		{
			Destroy(obj);
		}
	}

	void Laser::Initialize()
	{
	}

	void Laser::Update()
	{
		GameObject::Update();

		mCheckTime += Time::GetDeltaTime();
		if (mDeleteTime < mCheckTime)
		{
			Destroy(this);
		}
	}

	void Laser::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		Animator* ani = nullptr;
		if (mIsRight)
		{
			ani = mRightLaser[0]->GetComponent<Animator>();
			ani->PlayAnimation(L"LaserRighthead", false);
			for (int i = 1;i < 8;i++)
			{
				ani = mRightLaser[i]->GetComponent<Animator>();
				ani->PlayAnimation(L"LaserRightBody", false);
			}
		}
		else
		{
			ani = mLeftLaser[0]->GetComponent<Animator>();
			ani->PlayAnimation(L"LaserLefthead", false);
			for (int i = 1;i < 8;i++)
			{
				ani = mLeftLaser[i]->GetComponent<Animator>();
				ani->PlayAnimation(L"LaserLeftBody", false);
			}
		}
	}

	void Laser::SetLaserPos(Math::Vector2<float> pos)
	{
		Transform* tr = nullptr;
		if (mIsRight)
		{
			for (int i = 5;i >= 1;i--)
			{
				tr = mRightLaser[5 - i]->GetComponent<Transform>();
				tr->SetPos(Math::Vector2<float>(pos.x + 128.f * i - 64.f, pos.y));
			}

			for (int i = 1;i <= 5;i++)
			{
				tr = mRightLaser[10 - i]->GetComponent<Transform>();
				tr->SetPos(Math::Vector2<float>(pos.x - 128.f * (6 - i) + 64.f, pos.y));
			}
		}
		else
		{
			for (int i = 5;i >= 1;i--)
			{
				tr = mLeftLaser[5 - i]->GetComponent<Transform>();
				tr->SetPos(Math::Vector2<float>(pos.x - 128.f * i + 64.f, pos.y));
			}

			for (int i = 1;i <= 5;i++)
			{
				tr = mLeftLaser[10 - i]->GetComponent<Transform>();
				tr->SetPos(Math::Vector2<float>(pos.x + 128.f * (6 - i) - 64.f, pos.y));
			}
		}
	}

	void Laser::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player != nullptr)
		{
			Objdata::SetHP(Objdata::GetHP() - mDamage);
			mHitSound->Play(false);
		}
	}

	void Laser::OnCollisionStay(Collider* other)
	{
	}

	void Laser::OnCollisionExit(Collider* other)
	{
	}
}