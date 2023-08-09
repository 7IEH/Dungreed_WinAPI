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

		void Clear() { mForce = Math::Vector2<float>(0.f, 0.f); }

		void SetMass(float mass) { mfMass = mass; }
		void AddForce(Math::Vector2<float> force) { mForce += force; }
		
		void SetVeclocity(Math::Vector2<float> velocity) { mVelocity = velocity; }
		Math::Vector2<float> GetVelocity() { return mVelocity; }

		void SetGround(bool ground) { mbGround = ground; }
		bool GetGround() { return mbGround; }

		void SetFriction(float friction) { mfFriction = friction; }
		float GetFriction() { return mfFriction; }

	private:
		bool mbGround;

		float mfMass;
		float mfFriction;
		float mCoefficient;

		Math::Vector2<float> mVelocity;
		Math::Vector2<float> mAccelation;
		Math::Vector2<float> mForce;
		Math::Vector2<float> mGravity;
		Math::Vector2<float> mMaxGravity;
	};
}

