#include "EHFloor.h"
#include "EHPlayer.h"

namespace EH
{
	Floor::Floor()
	{
	}
	Floor::~Floor()
	{
	}
	void Floor::Initialize()
	{
	}

	void Floor::Update()
	{
		GameObject::Update();
	}

	void Floor::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Floor::OnCollisionEnter(Collider* other)
	{
		other->GetOwner()->GetComponent<Rigidbody>()->SetGround(true);
		Transform* playertr = other->GetOwner()->GetComponent<Transform>();
		Transform* floortr = GetComponent<Transform>();

		Collider* playercol = other->GetOwner()->GetComponent<Collider>();
		Collider* floorcol = GetComponent<Collider>();

		float scale = fabs(playercol->GetScale().y / 2.f + floorcol->GetScale().y / 2.f);
		float len = fabs(playertr->Getpos().y - floortr->Getpos().y);

		if (len < scale)
		{
			Math::Vector2 playerPos = playertr->Getpos();
			playerPos.y -= (scale - len) - 1.0f;
			playertr->SetPos(playerPos);
		}
	}

	void Floor::OnCollisionStay(Collider* other)
	{

	}

	void Floor::OnCollisionExit(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		player->GetComponent<Rigidbody>()->SetGround(false);
	}
}