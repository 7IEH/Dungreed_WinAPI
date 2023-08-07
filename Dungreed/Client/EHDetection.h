#pragma once
#include "EHGameObject.h"

namespace EH
{
	class Detection : public GameObject
	{
	public:
		Detection();
		virtual ~Detection();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		class Player* passthetarget() { return mTarget; }

	private:
		class Player* mTarget;
	};
}

