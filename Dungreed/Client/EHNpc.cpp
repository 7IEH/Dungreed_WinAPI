#include "EHNpc.h"
#include "EHObject.h"

namespace EH
{
	Npc::Npc()
	{
		AddComponent<SpriteRenderer>();
	}

	Npc::~Npc()
	{
	}

	void Npc::Initialize()
	{
	}

	void Npc::Update()
	{
		GameObject::Update();
	}

	void Npc::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}