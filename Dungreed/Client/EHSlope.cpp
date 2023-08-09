#include "EHSlope.h"
#include "EHPlayer.h"

namespace EH
{
	Slope::Slope()
		:
		  mYintercept(0.f)
		, mCorrection(0.f)
	    , mEnterCounter(0)
	{
	}

	Slope::~Slope()
	{
	}

	void Slope::Initialize()
	{
	}

	void Slope::Update()
	{
		GameObject::Update();
	}

	void Slope::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Slope::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Transform* tr = player->GetComponent<Transform>();
			Math::Vector2<float> pos = tr->Getpos();
			if (pos.y <= fabs(pos.x - mYintercept))
			{
				player->SetRightSlope(mIsRight);
				player->SetSlope(true);
				player->GetComponent<Rigidbody>()->SetGround(true);
			}
		}
	}

	void Slope::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Transform* tr = player->GetComponent<Transform>();
			Math::Vector2<float> pos = tr -> Getpos();

			if (mIsRight)
			{
				if (pos.y <= fabs(- pos.x + mYintercept))
				{
					if (mEnterCounter == 0)
					{
						player->GetComponent<Rigidbody>()->SetGround(true);
						pos.y = - pos.x + mYintercept - mCorrection;
						tr->SetPos(pos);
					}
					player->SetSlope(true);
					mEnterCounter++;
					player->ResetJumpStack();
				}
			}
			else
			{
				if (pos.y <= fabs(pos.x - mYintercept))
				{
					if (mEnterCounter == 0)
					{
						player->GetComponent<Rigidbody>()->SetGround(true);
						pos.y = pos.x - mYintercept - mCorrection;
						tr->SetPos(pos);
					}
					player->SetSlope(true);
					mEnterCounter++;
					player->ResetJumpStack();
				}
			}
		}
	}

	void Slope::OnCollisionExit(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			player->SetSlope(false);
			mEnterCounter = 0;
		}
	}
}