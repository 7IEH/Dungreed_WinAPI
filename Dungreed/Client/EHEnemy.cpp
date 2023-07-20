#include "EHEnemy.h"

namespace EH
{
	Enemy::Enemy()
	{
	}

	Enemy::~Enemy()
	{
	}

	void Enemy::Initialize()
	{
	}

	void Enemy::Update()
	{
		GameObject::Update();
	}

	void Enemy::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Enemy::OnCollisionEnter(Collider* other)
	{
	}

	void Enemy::OnCollisionStay(Collider* other)
	{
	}

	void Enemy::OnCollisionExit(Collider* other)
	{
	}
}
