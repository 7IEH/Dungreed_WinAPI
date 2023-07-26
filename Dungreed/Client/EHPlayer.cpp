#include "EHPlayer.h"
#include "EHInput.h"
#include "EHTime.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHApplication.h"
#include "EHCamera.h"

extern EH::Application application;

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
		, mActiveWeapon(eWeapon::None)
		, mIsSwing(true)
	{
		AddComponent<Rigidbody>();
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

		Playerlogic();

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

	// 나중에 정리
	void Player::Playerlogic()
	{
		Transform* tr = GetComponent<Transform>();
		if (mIsSwing)
		{
			if (mIsRight)
			{
				if (mActiveWeapon != eWeapon::None)
					mWeapon->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x + 30.f, tr->Getpos().y));
			}
			else
			{
				if (mActiveWeapon != eWeapon::None)
					mWeapon->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x - 30.f, tr->Getpos().y));
			}
		}
		else
		{
			if (mIsRight)
			{
				if (mActiveWeapon != eWeapon::None)
					mWeapon->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x + 30.f, tr->Getpos().y + 50.f));
			}
			else
			{
				if (mActiveWeapon != eWeapon::None)
					mWeapon->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x - 30.f, tr->Getpos().y + 50.f));
			}
		}


		if (mActiveWeapon == eWeapon::Onehand)
		{
			Transform* tr = GetComponent<Transform>();
			POINT pt = {};
			GetCursorPos(&pt);
			ScreenToClient(application.GetHWND(), &pt);
			Vector2<float> cursorpos;
			cursorpos.x = pt.x;
			cursorpos.y = pt.y;
			float radian = 0.f;
			float degree = 0.f;
			//degree 구하기

			cursorpos = Camera::CaculatePos(-cursorpos);
			cursorpos = -cursorpos;

			if (mIsSwing)
			{
				if (cursorpos.x > tr->Getpos().x)
				{
					radian = atan2(tr->Getpos().y - cursorpos.y, cursorpos.x - tr->Getpos().x);
					degree = radian * (180.f / 3.14f);
					mWeapon->GetComponent<SpriteRenderer>()->GetImg()->SetDegree(-(97 + degree));
					mIsRight = true;
				}
				else
				{
					radian = atan2(tr->Getpos().y - cursorpos.y, tr->Getpos().x - cursorpos.x);
					degree = radian * (180.f / 3.14f);
					mWeapon->GetComponent<SpriteRenderer>()->GetImg()->SetDegree(277 + degree);
					mIsRight = false;
				}
			}
			else
			{
				if (cursorpos.x > tr->Getpos().x)
				{
					radian = atan2(tr->Getpos().y - cursorpos.y, cursorpos.x - tr->Getpos().x);
					degree = radian * (180.f / 3.14f);
					mWeapon->GetComponent<SpriteRenderer>()->GetImg()->SetDegree(-97 - degree - 180);
					mIsRight = true;
				}
				else
				{
					radian = atan2(tr->Getpos().y - cursorpos.y, tr->Getpos().x - cursorpos.x);
					degree = radian * (180.f / 3.14f);
					mWeapon->GetComponent<SpriteRenderer>()->GetImg()->SetDegree(180 + 277 + degree);
					mIsRight = false;
				}
			}
		}
		else
		{
			Transform* tr = GetComponent<Transform>();
			POINT pt = {};
			GetCursorPos(&pt);
			ScreenToClient(application.GetHWND(), &pt);
			Vector2<float> cursorpos;
			cursorpos.x = pt.x;
			cursorpos.y = pt.y;

			cursorpos = Camera::CaculatePos(-cursorpos);
			cursorpos = -cursorpos;
			if (cursorpos.x > tr->Getpos().x)
			{
				mIsRight = true;
			}
			else
			{
				mIsRight = false;
			}
		}
	}

	void Player::Idle()
	{
		if (mIsRight)
			GetComponent<Animator>()->PlayAnimation(L"PlayerRightIdle", true);
		else
			GetComponent<Animator>()->PlayAnimation(L"PlayerLeftIdle", true);

		// 이것도 나중에 정리
		if (Input::Getkey(eKeyCode::K).state == eKeyState::DOWN)
		{
			Transform* tr = GetComponent<Transform>();
			POINT pt = {};
			GetCursorPos(&pt);
			ScreenToClient(application.GetHWND(), &pt);
			Vector2<float> cursorpos;
			cursorpos.x = pt.x;
			cursorpos.y = pt.y;

			Camera::CaculatePos(cursorpos);

			mActiveWeapon = eWeapon::Onehand;
			BackGround* weapon = object::Instantiate<BackGround>(enums::eLayerType::UI);
			Transform* temp = weapon->GetComponent<Transform>();
			temp->SetPos(Math::Vector2<float>(tr->Getpos().x + 30.f, tr->Getpos().y));
			temp->SetScale(Math::Vector2<float>(76.f, 28.f));

			Texture* texture = Resources::Load<Texture>(L"Onehand", L"..\\Resources\\Player\\Basic\\Attack\\ShortSword.png");
			//degree 구하기
			float radian = atan2(tr->Getpos().y - cursorpos.y, cursorpos.x - tr->Getpos().x);
			float degree = radian * (180.f / 3.14f);
			texture->SetDegree(degree + 90);
			weapon->GetComponent<SpriteRenderer>()->SetImg(texture);
			weapon->GetComponent<SpriteRenderer>()->SetAffectCamera(true);
			weapon->SetName(L"Test");
			mWeapon = weapon;
		}

		if (Input::Getkey(eKeyCode::L).state == eKeyState::DOWN)
		{
			EH::Destroy(mWeapon);
		}

 		if (Input::Getkey(eKeyCode::A).state == eKeyState::PRESSED)
		{
			mCurState = eAnimationState::Move;
			if (mIsRight)
			{
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightRun", true);
			}
			else
			{
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftRun", true);
			}
		}
		if (Input::Getkey(eKeyCode::S).state == eKeyState::PRESSED)
		{
			//mCurState = eAnimationState::Move;
		}
		if (Input::Getkey(eKeyCode::D).state == eKeyState::PRESSED)
		{
			mCurState = eAnimationState::Move;
			if (mIsRight)
			{
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightRun", true);
			}
			else
			{
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftRun", true);
			}
		}
		if (Input::Getkey(eKeyCode::Space).state == eKeyState::DOWN && JumpStack < 2)
		{
			mCurState = eAnimationState::Jump;
			JumpStack++;
			if (mIsRight)
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightJump", false);
			else
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftJump", false);
		}
		if (Input::Getkey(eKeyCode::MouseLeftClick).state == eKeyState::DOWN)
		{
			if (mActiveWeapon != eWeapon::None)
			{
				mCurState = eAnimationState::Attack;
				mIsSwing = !mIsSwing;
			}
		}
		if (mCurHp <= 0.f)
		{
			mCurState = eAnimationState::Die;
			if (mIsRight)
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightDie", false);
			else
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftDie", false);

			mIsDead = true;
		}
	}

	void Player::Move()
	{
		Transform* tr = GetComponent<Transform>();
		Math::Vector2<float> pos = tr->Getpos();

		if (Input::Getkey(eKeyCode::A).state == eKeyState::PRESSED)
		{
			pos.x -= 300.f * Time::GetDeltaTime();
			if (mIsRight)
			{
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightRun", true);
			}
			else
			{
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftRun", true);
			}
			//GetComponent<Rigidbody>()->AddForce(Math::Vector2<float>(-200.f, 0.f));
		}
		if (Input::Getkey(eKeyCode::S).state == eKeyState::PRESSED)
		{
			// 벽 아래로
		}
		if (Input::Getkey(eKeyCode::D).state == eKeyState::PRESSED)
		{
			if (mIsRight)
			{
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightRun", true);
			}
			else
			{
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftRun", true);
			}
			pos.x += 300.f * Time::GetDeltaTime();
			//GetComponent<Rigidbody>()->AddForce(Math::Vector2<float>(200.f, 0.f));
		}
		if (Input::Getkey(eKeyCode::Space).state == eKeyState::DOWN && JumpStack < 2)
		{
			mCurState = eAnimationState::Jump;
			JumpStack++;
			if (mIsRight)
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightJump", false);
			else
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftJump", false);
		}
		if (Input::Getkey(eKeyCode::MouseLeftClick).state == eKeyState::DOWN)
		{
			if (mActiveWeapon != eWeapon::None)
			{
				mCurState = eAnimationState::Attack;
				mIsSwing = !mIsSwing;
			}
		}
		if (mCurHp <= 0.f)
		{
			mCurState = eAnimationState::Die;
			if (mIsRight)
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightDie", false);
			else
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftDie", false);

			mIsDead = true;
		}
		if (Input::Getkey(eKeyCode::A).state == eKeyState::UP
			|| Input::Getkey(eKeyCode::D).state == eKeyState::UP)
		{
			mCurState = eAnimationState::Idle;
		}
		tr->SetPos(pos);
	}

	void Player::Jump()
	{
		Math::Vector2<float> velocity = GetComponent<Rigidbody>()->GetVelocity();
		GetComponent<Rigidbody>()->SetVeclocity(Math::Vector2<float>(velocity.x + 0.f, velocity.y + -500.f));
		GetComponent<Rigidbody>()->SetGround(false);
		if (Input::Getkey(eKeyCode::MouseLeftClick).state == eKeyState::DOWN)
		{
			if (mActiveWeapon != eWeapon::None)
				mCurState = eAnimationState::Attack;
		}
		if (mCurHp <= 0.f)
		{
			mCurState = eAnimationState::Die;
			if (mIsRight)
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightDie", false);
			else
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftDie", false);

			mIsDead = true;
		}
		if (Input::Getkey(eKeyCode::Space).state == eKeyState::UP || Input::Getkey(eKeyCode::Space).state == eKeyState::PRESSED)
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
		if (Input::Getkey(eKeyCode::Space).state == eKeyState::DOWN && JumpStack < 2)
		{
			mCurState = eAnimationState::Jump;
			JumpStack++;
			if (mIsRight)
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightJump", false);
			else
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftJump", false);
		}
		if (Input::Getkey(eKeyCode::MouseLeftClick).state == eKeyState::UP)
		{
			mCurState = eAnimationState::Idle;
		}
		if (mCurHp <= 0.f)
		{
			mCurState = eAnimationState::Die;
			if (mIsRight)
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightDie", false);
			else
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftDie", false);

			mIsDead = true;
		}
		if (mActiveWeapon == eWeapon::Onehand)
		{
		}
	}

	void Player::OnCollisionEnter(Collider* other)
	{
	}

	void Player::OnCollisionStay(Collider* other)
	{
	}

	void Player::OnCollisionExit(Collider* other)
	{
	}

}