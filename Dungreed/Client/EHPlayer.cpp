#include "EHPlayer.h"
#include "EHInput.h"
#include "EHTime.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCollider.h"

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
		, mCurState(eAnimationState::Idle)
	{
		AddComponent<SpriteRenderer>();
		Collider* collider = AddComponent<Collider>();
		collider->SetScale(Math::Vector2<float>(128.f, 128.f));
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
		GetComponent<Animator>()->SetAffectedCamera(false);

		switch (mCurState)
		{
		case EH::eAnimationState::Idle:
			Idle();
			break;
		case EH::eAnimationState::Move:
			Move();
			break;
		case EH::eAnimationState::Jump:
			Jump();
			break;
		case eAnimationState::Attack:
			Attack();
			break;
		case EH::eAnimationState::Die:
			Die();
			break;
		default:
			break;
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

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		wchar_t hp[50] = {};
		swprintf_s(hp, 50, L"%d/%d", mCurHp, mMaxHP);
		int strlen = wcsnlen_s(hp, 50);
		SetBkColor(hdc, RGB(93, 92, 110));
		TextOut(hdc, 200, 30, hp, strlen);
	}

	void Player::Idle()
	{
		if(mIsRight)
			GetComponent<Animator>()->PlayAnimation(L"PlayerRightIdle",true);
		else
			GetComponent<Animator>()->PlayAnimation(L"PlayerLeftIdle",true);

		if (Input::Getkey(eKeyCode::A).state == eKeyState::PRESSED)
		{
			mCurState = eAnimationState::Move;
			GetComponent<Animator>()->PlayAnimation(L"PlayerLeftRun", true);
			mIsRight = false;
		}
		if (Input::Getkey(eKeyCode::S).state == eKeyState::PRESSED)
		{
			//mCurState = eAnimationState::Move;
		}
		if (Input::Getkey(eKeyCode::D).state == eKeyState::PRESSED)
		{
			mCurState = eAnimationState::Move;
			GetComponent<Animator>()->PlayAnimation(L"PlayerRightRun", true);
			mIsRight = true;
		}
		if (Input::Getkey(eKeyCode::Space).state == eKeyState::DOWN)
		{
			mCurState = eAnimationState::Jump;
			if (mIsRight)
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightJump", false);
			else
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftJump",false);
		}
		if(Input::Getkey(eKeyCode::MouseLeftClick).state==eKeyState::DOWN)
		{
			//mCurState = eAnimationState::Attack;
		}
		if (Input::Getkey(eKeyCode::MouseLeftClick).state == eKeyState::DOWN)
		{
			//mCurState = eAnimationState::Attack;
		}
		if (mCurHp <= 0.f)
		{
			if (mIsRight)
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightDie", false);
			else
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftDie", false);
		}
	}

	void Player::Move()
	{
		Transform* tr = GetComponent<Transform>();
		Math::Vector2<float> pos = tr->Getpos();
		if (Input::Getkey(eKeyCode::A).state == eKeyState::UP
			|| Input::Getkey(eKeyCode::D).state == eKeyState::UP)
		{
			mCurState = eAnimationState::Idle;
		}
		if (Input::Getkey(eKeyCode::A).state == eKeyState::PRESSED)
		{
			pos -= 300.f * Time::GetDeltaTime();
		}
		if (Input::Getkey(eKeyCode::S).state == eKeyState::PRESSED)
		{
			//
		}
		if (Input::Getkey(eKeyCode::D).state == eKeyState::PRESSED)
		{
			pos += 300.f * Time::GetDeltaTime();
		}
		tr->SetPos(pos);
	}

	void Player::Jump()
	{
		if (Input::Getkey(eKeyCode::Space).state == eKeyState::UP)
		{
			mCurState = eAnimationState::Idle;
		}
	}

	void Player::Die()
	{
		if (mCurHp > 0.f)
		{
			mCurState = eAnimationState::Idle;
		}
	}

	void Player::Attack()
	{

	}
}