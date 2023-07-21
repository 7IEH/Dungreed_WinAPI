#pragma once
#include "EHComponent.h"

namespace EH
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		virtual ~Rigidbody();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		float mfMass;
		Math::Vector2<float> mVelocity;
		Math::Vector2<float> mAccelation;

	};
}

