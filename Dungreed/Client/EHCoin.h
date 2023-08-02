#pragma once
#include "EHGameObject.h"

namespace EH
{
	class Coin : public GameObject
	{
	public:
		Coin();
		virtual ~Coin();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
	};
}


