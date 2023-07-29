#include "EHBullet.h"
#include "EHPlayer.h"
#include "EHCamera.h"

namespace EH
{
	Bullet::Bullet()
		:
		  mRadian(0.f)
		, mDamage(0)
		, mDeleteTime(0.f)
		, mCheckTime(0.f)
		, mIsStop(true)
	{
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
			if (mDeleteTime < mCheckTime)
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
			Destroy(this);
		}
	}

	void Bullet::OnCollisionStay(Collider* other)
	{
	}

	void Bullet::OnCollisionExit(Collider* other)
	{
	}
}
