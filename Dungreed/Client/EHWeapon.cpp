#include "EHWeapon.h"
#include "EHTime.h"
#include "EHEnemy.h"

namespace EH
{
	void Weapon::Initialize()
	{
	}

	void Weapon::Update()
	{
		GameObject::Update();
	}

	void Weapon::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Weapon::OnCollisionEnter(Collider* other)
	{
	}

	void Weapon::OnCollisionStay(Collider* other)
	{
	}

	void Weapon::OnCollisionExit(Collider* other)
	{
	}
}