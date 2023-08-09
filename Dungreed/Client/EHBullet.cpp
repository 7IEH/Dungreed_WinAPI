#include "EHBullet.h"
#include "EHPlayer.h"
#include "EHCamera.h"
#include "EHObjdata.h"
#include "EHCeil.h"
#include "EHFloor.h"
#include "EHWall.h"
#include "EHResources.h"
#include "EHSound.h"

namespace EH
{
	Bullet::Bullet()
		:
		mRadian(0.f)
		, mDamage(0)
		, mDeleteTime(0.f)
		, mCheckTime(0.f)
		, mIsStop(true)
		, mIsPass(true)
		, mIsDelete(true)
	{
		mHitSound = Resources::Load<Sound>(L"playerhitsound", L"..\\Resources\\Sound\\Enemy\\public\\Hit_Player.wav");
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::Initialize()
	{
	}

	void Bullet::Update()
	{
		GameObject::Update();
		if (!mIsStop)
		{
			Transform* tr = GetComponent<Transform>();
			mCheckTime += Time::GetDeltaTime();
			Math::Vector2<float> pos = tr->Getpos();
			pos.y += sinf(mRadian) * 300.f * Time::GetDeltaTime();
			pos.x += cosf(mRadian) * 300.f * Time::GetDeltaTime();
			tr->SetPos(pos);
			if (mDeleteTime < mCheckTime && mIsDelete)
			{
				Destroy(this);
			}
		}
	}

	void Bullet::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Bullet::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player != nullptr)
		{
			Objdata::SetHP(Objdata::GetHP() - mDamage);
			mHitSound->Play(false);
			if(mIsDelete)
				Destroy(this);
		}

		if (!mIsPass)
		{
			Ceil* ceil = dynamic_cast<Ceil*>(other->GetOwner());
			Floor* floor = dynamic_cast<Floor*>(other->GetOwner());
			Wall* wall = dynamic_cast<Wall*>(other->GetOwner());
			if (ceil != nullptr)
			{
				Destroy(this);
			}
			else if (floor != nullptr)
			{
				Destroy(this);
			}
			else if (wall != nullptr)
			{
				Destroy(this);
			}
		}
	}

	void Bullet::OnCollisionStay(Collider* other)
	{
	}

	void Bullet::OnCollisionExit(Collider* other)
	{
	}
}
