#include "EHWall.h"
#include "EHPlayer.h"

namespace EH
{
	Wall::Wall()
		:
		 mIsRight(true)
	{
	}

	Wall::~Wall()
	{
	}

	void Wall::Initialize()
	{
	}

	void Wall::Update()
	{
		GameObject::Update();
	}

	void Wall::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Wall::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Transform* playertr = player->GetComponent<Transform>();
			Transform* tr = GetComponent<Transform>();

			Collider* playercol = player->GetComponent<Collider>();
			Collider* col = GetComponent<Collider>();

			if (playertr->Getpos().y + playercol->GetScale().y / 2.f > tr->Getpos().y - col->GetScale().y / 2.f)
			{
				Math::Vector2<float> playerpos = playertr->Getpos();
				Math::Vector2<float> pos = tr->Getpos();
				float diff = (col->GetScale().x / 2.f) + (playercol->GetScale().x / 2.f);

				if (mIsRight)
				{
					pos.x -= diff + 1.f;

				}
				else
				{
					pos.x += diff + 1.f;
				}

				playertr->SetPos(Math::Vector2<float>(pos.x, playertr->Getpos().y));
			}
		}
	}

	void Wall::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Transform* playertr = player->GetComponent<Transform>();
			Transform* tr = GetComponent<Transform>();

			Collider* playercol = player->GetComponent<Collider>();
			Collider* col = GetComponent<Collider>();

			if (playertr->Getpos().y + playercol->GetScale().y / 2.f > tr->Getpos().y - col->GetScale().y / 2.f)
			{
				Math::Vector2<float> playerpos = playertr->Getpos();
				Math::Vector2<float> pos = tr->Getpos();
				float diff = (col->GetScale().x / 2.f) + (playercol->GetScale().x / 2.f);

				if (mIsRight)
				{
					pos.x -= diff + 1.f;

				}
				else
				{
					pos.x += diff + 1.f;
				}

				playertr->SetPos(Math::Vector2<float>(pos.x, playertr->Getpos().y));
			}
		}
	}

	void Wall::OnCollisionExit(Collider* other)
	{
	}
}
