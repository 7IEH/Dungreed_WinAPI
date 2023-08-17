#include "EHEffect.h"

namespace EH
{
	void Effect::Initialize()
	{
	}

	void Effect::Update()
	{
		GameObject::Update();

		Animator* ani = GetComponent<Animator>();
		if (ani->GetActiveAnimation()->IsComplete())
		{
			Destroy(this);
		}
	}

	void Effect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}