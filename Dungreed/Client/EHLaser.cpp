#include "EHLaser.h"

namespace  EH
{
	Laser::Laser()
	{
	}

	Laser::~Laser()
	{
	}

	void Laser::Initialize()
	{
	}

	void Laser::Update()
	{
		GameObject::Update();
	}

	void Laser::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Laser::OnCollisionEnter(Collider* other)
	{
	}

	void Laser::OnCollisionStay(Collider* other)
	{
	}

	void Laser::OnCollisionExit(Collider* other)
	{
	}
}