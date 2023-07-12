#include "EHCamera.h"
#include "EHApplication.h"

extern EH::Application application;


namespace EH
{
	Math::Vector2<float> Camera::mResolution = {};
	Math::Vector2<float> Camera::mLookAt = {};
	Math::Vector2<float> Camera::mDiffDistance = {};
	GameObject* Camera::mTarget = nullptr;

	void Camera::Initialize()
	{
		mResolution.x = application.GetWinSize().x;
		mResolution.y = application.GetWinSize().y;

		mLookAt.x = application.GetWinSize().x / 2.f;
		mLookAt.y = application.GetWinSize().y / 2.f;
	}

	void Camera::Update()
	{
		if (mTarget)
		{
			mLookAt = mTarget->GetComponent<Transform>()->Getpos();
		}

		Vector2<float> test = mResolution / 2.f;
		mDiffDistance = mLookAt - (mResolution / 2.f);
	}

}
