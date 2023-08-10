#include "EHFloor.h"
#include "EHPlayer.h"
#include "EHCamera.h"
#include "EHSceneManager.h"
#include "EHCoin.h"
#include "EHJailDog.h"
#include "EHJailWarrior.h"

namespace EH
{
	Floor::Floor()
		:
		  mIsDownFloor(true)
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
		// 현재 충돌체가 player인지 확인
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Coin* coin = dynamic_cast<Coin*>(other->GetOwner());
		JailDog* dog = dynamic_cast<JailDog*>(other->GetOwner());
		JailWarrior* warrior = dynamic_cast<JailWarrior*>(other->GetOwner());

		if (player != nullptr)
		{
			// 점프 스택 초기화
			player->ResetJumpStack();

			// 
			Transform* playertr = other->GetOwner()->GetComponent<Transform>();
			Transform* floortr = GetComponent<Transform>();

			Collider* playercol = other->GetOwner()->GetComponent<Collider>();
			Collider* floorcol = GetComponent<Collider>();

			if (player->GetComponent<Rigidbody>()->GetVelocity().y > 0)
			{
				other->GetOwner()->GetComponent<Rigidbody>()->SetGround(true);

				float scale = fabs(playercol->GetScale().y / 2.f + floorcol->GetScale().y / 2.f);
				float len = fabs(playertr->Getpos().y - floortr->Getpos().y);

				if (len < scale)
				{
					Math::Vector2 playerPos = playertr->Getpos();
					playerPos.y -= (scale - len) - 1.0f;
					playertr->SetPos(playerPos);
				}
			}
		}
	
		if(coin != nullptr)
		{
			Transform* cointr = coin->GetComponent<Transform>();
			Transform* floortr = GetComponent<Transform>();

			Collider* coincol = coin->GetComponent<Collider>();
			Collider* floorcol = GetComponent<Collider>();

			if (coin->GetComponent<Rigidbody>()->GetVelocity().y > 0)
			{
				coin->GetComponent<Rigidbody>()->SetGround(true);

				float scale = fabs(coincol->GetScale().y / 2.f + floorcol->GetScale().y / 2.f);
				float len = fabs(cointr->Getpos().y - floortr->Getpos().y);

				if (len < scale)
				{
					Math::Vector2 coinPos = cointr->Getpos();
					coinPos.y -= (scale - len) - 1.0f;
					cointr->SetPos(coinPos);
				}
			}
		}

		if (dog != nullptr)
		{
			Transform* dogtr = dog->GetComponent<Transform>();
			Transform* floortr = GetComponent<Transform>();

			Collider* dogcol = dog->GetComponent<Collider>();
			Collider* floorcol = GetComponent<Collider>();

			if (dog->GetComponent<Rigidbody>()->GetVelocity().y > 0)
			{
				dog->GetComponent<Rigidbody>()->SetGround(true);

				float scale = fabs(dogcol->GetScale().y / 2.f + floorcol->GetScale().y / 2.f);
				float len = fabs(dogtr->Getpos().y - floortr->Getpos().y);

				if (len < scale)
				{
					Math::Vector2 dogPos = dogtr->Getpos();
					dogPos.y -= (scale - len) - 1.0f;
					dogtr->SetPos(dogPos);
				}
			}
		}

		if (warrior != nullptr)
		{
			Transform* warriortr = warrior->GetComponent<Transform>();
			Transform* floortr = GetComponent<Transform>();

			Collider* warriorcol = warrior->GetComponent<Collider>();
			Collider* floorcol = GetComponent<Collider>();

			if (warrior->GetComponent<Rigidbody>()->GetVelocity().y > 0)
			{
				warrior->GetComponent<Rigidbody>()->SetGround(true);

				float scale = fabs(warriorcol->GetScale().y / 2.f + floorcol->GetScale().y / 2.f);
				float len = fabs(warriortr->Getpos().y - floortr->Getpos().y);

				if (len < scale)
				{
					Math::Vector2 warriorPos = warriortr->Getpos();
					warriorPos.y -= (scale - len) - 1.0f;
					warriortr->SetPos(warriorPos);
				}
			}
		}
	}

	void Floor::OnCollisionStay(Collider* other)
	{
	}

	void Floor::OnCollisionExit(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Transform* playertr = other->GetOwner()->GetComponent<Transform>();
		Transform* floortr = GetComponent<Transform>();

		Collider* playercol = other->GetOwner()->GetComponent<Collider>();
		Collider* floorcol = GetComponent<Collider>();

		JailDog* dog = dynamic_cast<JailDog*>(other->GetOwner());
		
		if (player != nullptr)
		{
			if ((playertr->Getpos().y + playertr->GetScale().y / 2.f) - 1.f <= (floortr->Getpos().y - floorcol->GetScale().y / 2.f))
			{
				if (player->GetDir())
				{
					player->GetComponent<Animator>()->PlayAnimation(L"PlayerRightJump", false);
				}
				else
				{
					player->GetComponent<Animator>()->PlayAnimation(L"PlayerLeftJump", false);
				}
				player->GetComponent<Rigidbody>()->SetGround(false);
			}
		}

		if (dog != nullptr)
		{
			dog->GetComponent<Rigidbody>()->SetGround(false);
		}
	}
}