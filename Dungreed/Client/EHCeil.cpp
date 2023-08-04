#include "EHCeil.h"
#include "EHPlayer.h"

namespace EH
{
	void Ceil::Initialize()
	{
	}

	void Ceil::Update()
	{
		GameObject::Update();
	}

	void Ceil::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Ceil::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Transform* playertr = player->GetComponent<Transform>();
			player->GetComponent<Rigidbody>()->SetGround(true);
			Math::Vector2<float> pos = GetComponent<Transform>()->Getpos();
			Math::Vector2<float> playersclae = player->GetComponent<Collider>()->GetScale();
			Math::Vector2<float> scale = GetComponent<Collider>()->GetScale();
			pos.y += (playersclae.y / 2.f + scale.y / 2.f) + 1.f;
			playertr->SetPos(Math::Vector2<float>(playertr->Getpos().x, pos.y));
		}
	}

	void Ceil::OnCollisionStay(Collider* other)
	{
	}

	void Ceil::OnCollisionExit(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		player->GetComponent<Rigidbody>()->SetGround(false);
	}
}