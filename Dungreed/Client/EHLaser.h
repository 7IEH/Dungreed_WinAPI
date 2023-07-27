#pragma once
#include "EHGameObject.h"

namespace EH
{
	class Laser : public GameObject
	{
	public:
		Laser();
		virtual ~Laser();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
	};
}

