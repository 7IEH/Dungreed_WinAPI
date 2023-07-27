#include "EHProjectile.h"
#include "EHPlayer.h"

namespace EH
{
	Projectile::Projectile()
		:
		mDegree(0.f)
	{
	}

	Projectile::~Projectile()
	{
	}

	void Projectile::Initialize()
	{
	}

	void Projectile::Update()
	{
		GameObject::Update();
		Transform* tr = GetComponent<Transform>();
		Math::Vector2<float> pos = tr->Getpos();
		pos.y += sinf(mDegree) * 300.f * Time::GetDeltaTime();
		pos.x += cosf(mDegree) * 300.f * Time::GetDeltaTime();
		tr->SetPos(pos);
	}

	void Projectile::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Projectile::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Destroy(this);
		}
	}

	void Projectile::OnCollisionStay(Collider* other)
	{
	}

	void Projectile::OnCollisionExit(Collider* other)
	{
	}
}
