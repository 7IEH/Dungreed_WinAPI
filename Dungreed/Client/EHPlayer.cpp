#include "EHPlayer.h"
#include "EHInput.h"
#include "EHTime.h"
#include "EHObject.h"
#include "EHResources.h"

namespace EH
{
	Player::Player()
		:
		CurHp(80),
		MaxHP(80),
		Gold(0),
		Food(0),
		Level(1)
	{
		AddComponent<SpriteRenderer>();
		Texture* temp = Resources::Load<Texture>(L"HPRed", L"..\\Resources\\UI\\PlayerLife.png");
		mHp = EH::object::Instantiate<BackGround>(enums::eLayerType::UI);
		mHp->GetComponent<Transform>()->SetPos(Math::Vector2<float>(99.f, 24.f));
		mHp->GetComponent<Transform>()->SetScale(Math::Vector2<float>(192.f, 36.f));
		temp->SetWidth(48);
		temp->SetHeight(9);
		mHp->GetComponent<SpriteRenderer>()->SetImg(temp);
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

		if (Input::Getkey(eKeyCode::P).state == eKeyState::DOWN)
		{
			CurHp -= 5;
			mHp->GetComponent<Transform>()->SetScale(Math::Vector2<float>(192.f * ((float)CurHp / (float)MaxHP), 36.f));
		}

		tr->SetPos(pos);
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		wchar_t hp[50] = {};
		swprintf_s(hp, 50, L"%d/%d", CurHp, MaxHP);
		int strlen = wcsnlen_s(hp, 50);
		SetBkColor(hdc, RGB(93, 92,110));
		TextOut(hdc, 200, 30, hp, strlen);
	}

}