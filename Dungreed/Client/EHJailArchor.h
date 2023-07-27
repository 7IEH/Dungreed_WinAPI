#pragma once
#include "EHEnemy.h"

namespace EH
{
	class JailArchor : public Enemy
	{
	public:
		JailArchor();
		virtual ~JailArchor();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
	};
}
