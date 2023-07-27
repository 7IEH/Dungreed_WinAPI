#include "EHBanshee.h"

namespace EH
{
	Banshee::Banshee()
	{
	}

	Banshee::~Banshee()
	{
	}

	void Banshee::Initialize()
	{
	}

	void Banshee::Update()
	{
		GameObject::Update();
	}

	void Banshee::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Banshee::OnCollisionEnter(Collider* other)
	{
	}

	void Banshee::OnCollisionStay(Collider* other)
	{
	}

	void Banshee::OnCollisionExit(Collider* other)
	{
	}
}