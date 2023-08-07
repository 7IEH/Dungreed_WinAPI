#include "EHDetection.h"
#include "EHPlayer.h"

namespace EH
{
	Detection::Detection()
		:
		 mTarget(nullptr)
	{
	}

	Detection::~Detection()
	{
	}

	void Detection::Initialize()
	{
	}

	void Detection::Update()
	{
		GameObject::Update();
	}

	void Detection::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Detection::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			mTarget = player;
			Collider* col = GetComponent<Collider>();
			col->enabled(false);
		}
	}

	void Detection::OnCollisionStay(Collider* other)
	{
	}

	void Detection::OnCollisionExit(Collider* other)
	{
	}
}