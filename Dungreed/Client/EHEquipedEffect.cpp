#include "EHEquipedEffect.h"
#include "EHTime.h"

namespace EH
{
	void EquipedEffect::Initialize()
	{
	}

	void EquipedEffect::Update()
	{
		GameObject::Update();

		mCheckTime += Time::GetDeltaTime();
		if (mDeletetime < mCheckTime)
		{
			Destroy(this);
		}
	}

	void EquipedEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}