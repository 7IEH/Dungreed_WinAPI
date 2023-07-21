#include "EHRigidbody.h"
#include "EHTime.h"
#include "EHTransform.h"
#include "EHGameObject.h"

namespace EH
{
	Rigidbody::Rigidbody()
		:
		  Component(enums::eComponentType::Rigidbody)
		, mfMass(1.f)
		, mVelocity(Math::Vector2<float>(0.f,0.f))
		, mAccelation(Math::Vector2<float>(0.f,0.f))
		, mForce(Math::Vector2<float>(0.f,0.f))
		, mfFriction(10.f)
		, mCoefficient(0.2f)
	{
	}

	Rigidbody::~Rigidbody()
	{
	}

	void Rigidbody::Initialize()
	{
	}

	void Rigidbody::Update()
	{
		mAccelation = mForce / mfMass;

		mVelocity += mAccelation * Time::GetDeltaTime();

		if (!(mVelocity == Math::Vector2<float>(0.f, 0.f)))
		{
			Math::Vector2<float> friction = -mVelocity;
			Math::Vector2<float> test = friction.normalized<float>();
			friction = friction.normalized<float>() * mfFriction * mfMass * Time::GetDeltaTime();

			if (mVelocity.lengh() <= friction.lengh())
			{
				mVelocity = Math::Vector2<float>(0.f, 0.f);
			}
			else
			{
				mVelocity += friction;
			}
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetPos(tr->Getpos() += mVelocity);
		Clear();
	}

	void Rigidbody::Render(HDC hdc)
	{
	}
}