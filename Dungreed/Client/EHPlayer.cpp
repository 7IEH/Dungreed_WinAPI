#include "EHPlayer.h"
#include "EHInput.h"
#include "EHTime.h"

namespace EH
{
	Player::Player()
	{
		AddComponent<SpriteRenderer>();
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
	}

	void Player::Update()
	{
		GameObject::Update();
		Transform* tr = GetComponent<Transform>();
		Math::Vector2<float> pos = tr->Getpos();

		if (Input::Getkey(eKeyCode::A).state == eKeyState::PRESSED)
		{
			pos.x -= 300.f * Time::GetDeltaTime();
		}
		if (Input::Getkey(eKeyCode::W).state == eKeyState::PRESSED)
		{
			pos.y -= 300.f * Time::GetDeltaTime();
		}
		if (Input::Getkey(eKeyCode::S).state == eKeyState::PRESSED)
		{
			pos.y += 300.f * Time::GetDeltaTime();
		}
		if (Input::Getkey(eKeyCode::D).state == eKeyState::PRESSED)
		{
			pos.x += 300.f * Time::GetDeltaTime();
		}

		tr->SetPos(pos);
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}