#include "EHPlayer.h"
#include "EHInput.h"
#include "EHTime.h"
#include "EHObject.h"
#include "EHResources.h"

namespace EH
{
	Player::Player()
		:
		mCurHp(80)
		, mMaxHP(80)
		, mGold(0)
		, mFood(0)
		, mLevel(1)
		, mIsRight(true)
		, mIsDead(false)
	{
		AddComponent<SpriteRenderer>();
		Texture* temp = Resources::Load<Texture>(L"HPRed", L"..\\Resources\\UI\\PlayerLife.png");
		mHp = EH::object::Instantiate<BackGround>(enums::eLayerType::UI);
		mHp->GetComponent<Transform>()->SetPos(Math::Vector2<float>(195.f, 42.f));
		mHp->GetComponent<Transform>()->SetScale(Math::Vector2<float>(192.f, 36.f));
		temp->SetWidth(48);
		temp->SetHeight(9);
		mHp->GetComponent<SpriteRenderer>()->SetImg(temp);
		mHp->GetComponent<SpriteRenderer>()->SetAffectCamera(false);
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
		Math::Vector2<float> initPos = pos;
		GetComponent<Animator>()->SetAffectedCamera(false);
		
		if (mCurHp <= 0)
		{
			mIsDead = true;
		}
		else
		{
			mIsDead = false;
		}

		if (!mIsDead)
		{
			if (Input::Getkey(eKeyCode::A).state == eKeyState::PRESSED)
			{
				mIsRight = false;
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftRun", true);
				pos.x -= 300.f * Time::GetDeltaTime();
			}
			if (Input::Getkey(eKeyCode::W).state == eKeyState::PRESSED)
			{
				if(mIsRight)
					GetComponent<Animator>()->PlayAnimation(L"PlayerRightJump", true);
				else
					GetComponent<Animator>()->PlayAnimation(L"PlayerLeftJump", true);
				pos.y -= 300.f * Time::GetDeltaTime();
			}
			if (Input::Getkey(eKeyCode::S).state == eKeyState::PRESSED)
			{
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightRun", true);
				pos.y += 300.f * Time::GetDeltaTime();
			}
			if (Input::Getkey(eKeyCode::D).state == eKeyState::PRESSED)
			{
				mIsRight = true;
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightRun", true);
				pos.x += 300.f * Time::GetDeltaTime();
			}

			if (mIsRight && pos-initPos == Math::Vector2<float>(0.f,0.f))
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightIdle", true);
			else if (!mIsRight && pos - initPos == Math::Vector2<float>(0.f, 0.f))
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftIdle", true);

			if (Input::Getkey(eKeyCode::P).state == eKeyState::DOWN)
			{
				mCurHp -= 5;
				mHp->GetComponent<Transform>()->SetScale(Math::Vector2<float>(192.f * ((float)mCurHp / (float)mMaxHP), 36.f));
			}

			if (Input::Getkey(eKeyCode::O).state == eKeyState::DOWN)
			{
				mCurHp += 5;
				mHp->GetComponent<Transform>()->SetScale(Math::Vector2<float>(192.f * ((float)mCurHp / (float)mMaxHP), 36.f));
			}
		}
		else
		{
			if (mIsRight)
			{
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightDie", true);
			}
			else
			{
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftDie", true);
			}

			if (Input::Getkey(eKeyCode::P).state == eKeyState::DOWN)
			{
				mCurHp -= 5;
				mHp->GetComponent<Transform>()->SetScale(Math::Vector2<float>(192.f * ((float)mCurHp / (float)mMaxHP), 36.f));
			}

			if (Input::Getkey(eKeyCode::O).state == eKeyState::DOWN)
			{
				mCurHp += 5;
				mHp->GetComponent<Transform>()->SetScale(Math::Vector2<float>(192.f * ((float)mCurHp / (float)mMaxHP), 36.f));
			}
		}
		tr->SetPos(pos);
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		wchar_t hp[50] = {};
		swprintf_s(hp, 50, L"%d/%d", mCurHp, mMaxHP);
		int strlen = wcsnlen_s(hp, 50);
		SetBkColor(hdc, RGB(93, 92, 110));
		TextOut(hdc, 200, 30, hp, strlen);
	}

}