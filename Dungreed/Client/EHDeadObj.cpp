#include "EHDeadObj.h"

namespace EH
{
	void DeadObj::Initialize()
	{
	}

	void DeadObj::Update()
	{
		GameObject::Update();
	}

	void DeadObj::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}