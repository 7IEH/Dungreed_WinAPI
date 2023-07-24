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
		, mbGround(false)
	{
		mGravity = Math::Vector2<float>(0.f, 800.f);
		mMaxGravity = Math::Vector2<float>(200.f, 1000.f);
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

		mVelocity += Math::Vector2(mAccelation.x * Time::GetDeltaTime(),mAccelation.y*Time::GetDeltaTime());

		if (mbGround)
		{
			Math::Vector2<float> gravity = mGravity;
			gravity.normalized<float>();
			float dot = Math::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			mVelocity += Math::Vector2<float>(mGravity.x * Time::GetDeltaTime(), mGravity.y * Time::GetDeltaTime());
		}

		Math::Vector2<float> gravity = mGravity;
		gravity.normalized<float>();
		float dot = Math::Dot(mVelocity, gravity);
		gravity = gravity * dot;
		
		Math::Vector2<float> SideGravity = mVelocity - gravity;
		if (mMaxGravity.y < gravity.lengh())
		{
			gravity.normalized<float>();
			gravity.y *= mMaxGravity.y;
		}

		if(mMaxGravity.x < SideGravity.lengh())
		{
			SideGravity.normalized<float>();
			SideGravity.x *= mMaxGravity.x;
		}
		mVelocity = gravity + SideGravity;


		if (!(mVelocity == Math::Vector2<float>(0.f, 0.f)))
		{
			Math::Vector2<float> friction = -mVelocity;
			friction = friction.normalized<float>() * mfFriction * mfMass * Time::GetDeltaTime();

			if (mVelocity.lengh() < friction.lengh())
			{
				mVelocity = Math::Vector2<float>(0.f, 0.f);
			}
			else
			{
				mVelocity += friction;
			}
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->SetPos(tr->Getpos() + Math::Vector2<float>(mVelocity.x*Time::GetDeltaTime(),mVelocity.y*Time::GetDeltaTime()));
		Clear();
	}

	void Rigidbody::Render(HDC hdc)
	{
	}
}