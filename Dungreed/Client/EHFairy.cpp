#include "EHFairy.h"
#include "EHPlayer.h"
#include "EHObjdata.h"
#include "EHResources.h"
#include "EHSound.h"

namespace EH
{
	Fairy::Fairy()
		:
		mHeal(0)
	{
		Collider* col = AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(40.f, 40.f));

		mEquipSound = Resources::Load<Sound>(L"FairyEqup", L"..\\Resources\\Sound\\Item\\EC Collect.wav");
	}

	Fairy::~Fairy()
	{
	}

	void Fairy::Initialize()
	{
	}

	void Fairy::Update()
	{
		GameObject::Update();
	}

	void Fairy::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Fairy::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			if (Objdata::GetMaxHP() < Objdata::GetHP() + mHeal)
			{
				Objdata::SetHP(Objdata::GetMaxHP());
			}
			else
			{
				Objdata::SetHP(Objdata::GetHP() + mHeal);
			}
			mEquipSound->Play(false);
			Destroy(this);
		}
	}

	void Fairy::OnCollisionStay(Collider* other)
	{
	}

	void Fairy::OnCollisionExit(Collider* other)
	{
	}
}