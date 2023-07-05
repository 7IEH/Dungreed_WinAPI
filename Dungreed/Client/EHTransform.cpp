#include "EHTransform.h"

namespace EH
{
	Transform::Transform()
		:
		Component(enums::eComponentType::Transform)
		,mPos(0.f,0.f)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
		if (Input::Getkey(eKeyCode::A).state == eKeyState::PRESSED)
		{
			mPos.x -= 300.f * Time::GetDeltaTime();
		}
		if (Input::Getkey(eKeyCode::W).state == eKeyState::PRESSED)
		{
			mPos.y -= 300.f * Time::GetDeltaTime();
		}
		if (Input::Getkey(eKeyCode::S).state == eKeyState::PRESSED)
		{
			mPos.y += 300.f * Time::GetDeltaTime();
		}
		if (Input::Getkey(eKeyCode::D).state == eKeyState::PRESSED)
		{
			mPos.x += 300.f * Time::GetDeltaTime();
		}
	}

	void Transform::Render(HDC hdc)
	{
	}
}