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
		mLookAt.y = application.GetWinSize().y / 2.f + 96.f;
	}

	void Camera::Update()
	{
		if (Input::Getkey(eKeyCode::LEFT).state == eKeyState::PRESSED)
		{
			mLookAt.x -= 300.f * Time::GetDeltaTime();
		}
		if (Input::Getkey(eKeyCode::UP).state == eKeyState::PRESSED)
		{
			mLookAt.y -= 300.f * Time::GetDeltaTime();
		}
		if (Input::Getkey(eKeyCode::DOWN).state == eKeyState::PRESSED)
		{
			mLookAt.y += 300.f * Time::GetDeltaTime();
		}
		if (Input::Getkey(eKeyCode::RIGHT).state == eKeyState::PRESSED)
		{
			mLookAt.x += 300.f * Time::GetDeltaTime();
		}

		if (mTarget)
		{
			mLookAt = mTarget->GetComponent<Transform>()->Getpos();
		}
		mDiffDistance = mLookAt - (mResolution / 2.f);
	}

}