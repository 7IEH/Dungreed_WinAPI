#include "EHPlayer.h"
#include "EHInput.h"
#include "EHTime.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHApplication.h"
#include "EHCamera.h"
#include "EHFloor.h"
#include "EHBackGround.h"
#include "EHWeapon.h"
#include "EHCanvas.h"
#include "EHObjdata.h"
#include "EHImageObject.h"
#include "EHSound.h"

extern EH::Application application;

namespace EH
{
	Player::Player()
		:
		mCurHp(Objdata::GetHP())
		, mMaxHP(Objdata::GetMaxHP())
		, mGold(Objdata::GetGold())
		, mFood(Objdata::GetFood())
		, mLevel(Objdata::GetLevel())
		, mIsRight(true)
		, mIsDead(false)
		, mCurState(eAnimationState::Idle)
		, mActiveWeapon(enums::eWeapon::None)
		, mJumpStack(0)
		, mWeapon(nullptr)
		, mIsJump(false)
		, mOnBlock(false)
		, mIsSwing(true)
		, mIsSlope(false)
		, mIsRightSlope(false)
		, mCheckTime(0.f)
		, mWeaponCollider(nullptr)
		, mSound(nullptr)
		, Trans(false)
	{
		AddComponent<Rigidbody>();

		// Animation setting
		Texture* texture = Resources::Load<Texture>(L"PlayerRightIdle", L"..\\Resources\\Player\\Basic\\Idle\\CharRightIdleSheet.bmp");
		Animator* animator = AddComponent<Animator>();
		animator->CreateAnimation(L"PlayerRightIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 5, 0.1f);
		animator->PlayAnimation(L"PlayerRightIdle", true);

		texture = Resources::Load<Texture>(L"PlayerRightRun", L"..\\Resources\\Player\\Basic\\Run\\CharRightRunSheet.bmp");
		animator->CreateAnimation(L"PlayerRightRun", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

		texture = Resources::Load<Texture>(L"PlayerRightDie", L"..\\Resources\\Player\\Basic\\Die\\CharRightDie.bmp");
		animator->CreateAnimation(L"PlayerRightDie", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);

		texture = Resources::Load<Texture>(L"PlayerRightJump", L"..\\Resources\\Player\\Basic\\Jump\\CharRightJump.bmp");
		animator->CreateAnimation(L"PlayerRightJump", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);

		// Left
		texture = Resources::Load<Texture>(L"PlayerLeftIdle", L"..\\Resources\\Player\\Basic\\Idle\\CharLeftIdleSheet.bmp");
		animator->CreateAnimation(L"PlayerLeftIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 5, 0.1f);

		texture = Resources::Load<Texture>(L"PlayerLeftRun", L"..\\Resources\\Player\\Basic\\Run\\CharLeftRunSheet.bmp");
		animator->CreateAnimation(L"PlayerLeftRun", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

		texture = Resources::Load<Texture>(L"PlayerLeftDie", L"..\\Resources\\Player\\Basic\\Die\\CharLeftDie.bmp");
		animator->CreateAnimation(L"PlayerLeftDie", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);

		texture = Resources::Load<Texture>(L"PlayerLeftJump", L"..\\Resources\\Player\\Basic\\Jump\\CharLeftJump.bmp");
		animator->CreateAnimation(L"PlayerLeftJump", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);

		texture = Resources::Load<Texture>(L"Trans", L"..\\Resources\\Player\\Basic\\Trans.png");
		animator->CreateAnimation(L"Trans", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);

		AddComponent<Collider>();
		GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 128.f));
		GetComponent<Collider>()->SetOffset(Math::Vector2<float>(0.f, 0.f));
		animator->SetAffectedCamera(true);
		GetComponent<Collider>()->SetAffectedCamera(true);

		// UI setting
		Canvas* PlayerUICanvas = object::Instantiate<Canvas>(enums::eLayerType::UI);
		texture = Resources::Load<Texture>(L"HPBack", L"..\\Resources\\UI\\PlayerLifeBack.png");
		PlayerUICanvas->AddImageObject(L"HPBack", texture, false, Math::Vector2<float>(157.f, 42.f), Math::Vector2<float>(296.f, 64.f));

		texture = Resources::Load<Texture>(L"HP", L"..\\Resources\\UI\\PlayerLife.png");
		PlayerUICanvas->AddImageObject(L"HP", texture, false, Math::Vector2<float>(194.f, 42.f), Math::Vector2<float>(198.f, 56.f));

		texture = Resources::Load<Texture>(L"HPBase", L"..\\Resources\\UI\\PlayerLifeBase 1.png");
		PlayerUICanvas->AddImageObject(L"HPBase", texture, false, Math::Vector2<float>(157.f, 42.f), Math::Vector2<float>(296.f, 64.f));

		texture = Resources::Load<Texture>(L"DashBase", L"..\\Resources\\UI\\DashCountBase.png");
		PlayerUICanvas->AddImageObject(L"DashBase", texture, false, Math::Vector2<float>(135.f, 97.f), Math::Vector2<float>(252.f, 34.f));

		texture = Resources::Load<Texture>(L"CoinUI", L"..\\Resources\\UI\\Coin.png");
		PlayerUICanvas->AddImageObject(L"CoinUI", texture, false, Math::Vector2<float>(29.f, 657.f), Math::Vector2<float>(34.f, 28.f));

		texture = Resources::Load<Texture>(L"FoodGage", L"..\\Resources\\UI\\FoodGage.png");
		PlayerUICanvas->AddImageObject(L"FoodGage", texture, false, Math::Vector2<float>(110.f, 710.f), Math::Vector2<float>(82.f, 12.f));

		texture = Resources::Load<Texture>(L"FoodBase", L"..\\Resources\\UI\\FoodBase.bmp");
		PlayerUICanvas->AddImageObject(L"FoodBase", texture, false, Math::Vector2<float>(110.f, 710.f), Math::Vector2<float>(82.f, 12.f));

		texture = Resources::Load<Texture>(L"FoodUI", L"..\\Resources\\UI\\Food.png");
		PlayerUICanvas->AddImageObject(L"FoodUI", texture, false, Math::Vector2<float>(29.f, 690.f), Math::Vector2<float>(34.f, 28.f));

		texture = Resources::Load<Texture>(L"WeaponSlot", L"..\\Resources\\UI\\EquippedWeaponBase.png");
		PlayerUICanvas->AddImageObject(L"WeaponSlot", texture, false, Math::Vector2<float>(1210.f, 641.f), Math::Vector2<float>(140.f, 102.f));
		PlayerUICanvas->AddImageObject(L"WeaponSlot2", texture, false, Math::Vector2<float>(1190.f, 657.f), Math::Vector2<float>(140.f, 102.f));

		// Sound setting
		Sound* sound = Resources::Load<Sound>(L"PlayerRunSound", L"..\\Resources\\Sound\\Player\\Run\\step_lth1.wav");
		sound = Resources::Load<Sound>(L"PlayerJumpSound", L"..\\Resources\\Sound\\Player\\Jump\\Jumping.wav");
		sound = Resources::Load<Sound>(L"PlayerSwingSound", L"..\\Resources\\Sound\\Player\\Attack\\swing3.wav");
		sound = Resources::Load<Sound>(L"PlayerDashSound", L"..\\Resources\\Sound\\Player\\Dash\\Dash.wav");

		mCanvas = PlayerUICanvas;
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
	}

	void Player::Update()
	{
		if (Trans)
			return;

		GameObject::Update();
		mIsJump = GetComponent<Rigidbody>()->GetGround();

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
		case eAnimationState::DownJump:
			DownJump();
			break;
		case eAnimationState::Dash:
			Dash();
			break;
		case EH::eAnimationState::Die:
			Die();
			break;
		default:
			break;
		}

		if (mWeaponCollider != nullptr)
		{
			if (mIsAttack)
			{
				mCheckTime += Time::GetDeltaTime();
			}
			if (mWeaponCollider->GetDelayTime() < mCheckTime)
			{
				// 끄고 exit해주고
				mWeaponCollider->GetComponent<Collider>()->enabled(false);
				mCheckTime = 0.f;
				mIsAttack = false;
			}
		}

		// objdata update
		mCurHp = Objdata::GetHP();
		mLevel = Objdata::GetLevel();
		mGold = Objdata::GetGold();
		mFood = Objdata::GetFood();
		mCurDash = Objdata::GetDash();
		mMaxHP = Objdata::GetMaxHP();

		if (mWeapon != Objdata::GetWeapon())
		{
			//BackGround* weapon = object::Instantiate<BackGround>(enums::eLayerType::UI);
			//Transform* temp = weapon->GetComponent<Transform>();
			//temp->SetPos(Math::Vector2<float>(tr->Getpos().x + 30.f, tr->Getpos().y));
			//temp->SetScale(Math::Vector2<float>(76.f, 28.f));

			//Texture* texture = Resources::Load<Texture>(L"Onehand", L"..\\Resources\\Player\\Basic\\Attack\\ShortSword.png");
			////degree 구하기
			//float radian = atan2(tr->Getpos().y - cursorpos.y, cursorpos.x - tr->Getpos().x);
			//float degree = radian * (180.f / 3.14f);
			//texture->SetDegree(degree + 90);
			//weapon->GetComponent<SpriteRenderer>()->SetImg(texture);
			//weapon->GetComponent<SpriteRenderer>()->SetAffectCamera(true);
			//weapon->SetName(L"Test");
			SceneManager::GetCurScene()->SetLayer(enums::eLayerType::UI, Objdata::GetWeapon());
			mWeapon = Objdata::GetWeapon();
			Texture* texture = Resources::Load<Texture>(L"Sword1", L"..\\Resources\\Player\\Basic\\Attack\\ShortSword.png");
			mCanvas->AddImageObject(L"Sword1", texture, false, Math::Vector2<float>(1180.f, 660.f), Math::Vector2<float>(76.f, 28.f));
			Objdata::SetWeapon(mWeapon);
		}

		if (mIsSwing != Objdata::GetSwing())
		{
			mIsSwing = Objdata::GetSwing();
		}

		if (mActiveWeapon != Objdata::GetActiveWeapon())
		{
			mActiveWeapon = Objdata::GetActiveWeapon();
		}

		if (mWeaponCollider != Objdata::GetWeaponCollider())
		{
			SceneManager::GetCurScene()->SetLayer(enums::eLayerType::Sword, Objdata::GetWeaponCollider());
			mWeaponCollider = Objdata::GetWeaponCollider();
			Objdata::SetWeaponCollider(mWeaponCollider);
		}

		// UI Update
		ImageObject* hp = mCanvas->Find(L"HP");
		Transform* tr = hp->GetComponent<Transform>();
		tr->SetPos(Math::Vector2<float>(194.f - ((198.f - 198.f * ((float)mCurHp / (float)mMaxHP)) / 2.f), tr->Getpos().y));
		tr->SetScale(Math::Vector2<float>(198.f * ((float)mCurHp / (float)mMaxHP), tr->GetScale().y));

		ImageObject* foodgage = mCanvas->Find(L"FoodGage");
		tr = foodgage->GetComponent<Transform>();
		tr->SetPos(Math::Vector2<float>(110.f - ((82.f - 82.f * ((float)mFood / 100.f)) / 2.f), tr->Getpos().y));
		tr->SetScale(Math::Vector2<float>(82.f * ((float)mFood / 100.f), tr->GetScale().y));

		Playerlogic();
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		// UI text
		// SetTextColor(hdc, RGB(255, 255, 255));
		////SetBkMode(hdc, TRANSPARENT);
		wchar_t szFloat[50] = {};
		//HFONT hNewFont;
		//HFONT hOldFont;
		//hNewFont = CreateFont(42, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Neo둥근모"));
		//hOldFont = (HFONT)SelectObject(hdc, hNewFont);

		swprintf_s(szFloat, 50, L"%d / %d", mCurHp, mMaxHP);
		int strLen = wcsnlen_s(szFloat, 50);
		TextOutW(hdc, 125, 20, szFloat, strLen);

		//swprintf_s(szFloat, 50, L"%d", mLevel);
		//strLen = wcsnlen_s(szFloat, 50);
		//TextOutW(hdc, 43, 20, szFloat, strLen);

		//hNewFont = CreateFont(27, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Neo둥근모"));
		//SelectObject(hdc, hNewFont);

		swprintf_s(szFloat, 50, L"%d", mGold);
		strLen = wcsnlen_s(szFloat, 50);
		TextOutW(hdc, 65, 649, szFloat, strLen);

		//swprintf_s(szFloat, 50, L"%d / 100", mFood);
		//strLen = wcsnlen_s(szFloat, 50);
		//TextOutW(hdc, 65, 675, szFloat, strLen);

		//SelectObject(hdc, hOldFont);
		//DeleteObject(hNewFont);
	}

	// 나중에 정리
	void Player::Playerlogic()
	{
		Transform* tr = GetComponent<Transform>();
		if (mIsSwing)
		{
			if (mIsRight)
			{
				if (mActiveWeapon != enums::eWeapon::None)
					mWeapon->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x + 30.f, tr->Getpos().y));
			}
			else
			{
				if (mActiveWeapon != enums::eWeapon::None)
					mWeapon->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x - 30.f, tr->Getpos().y));
			}
		}
		else
		{
			if (mIsRight)
			{
				if (mActiveWeapon != enums::eWeapon::None)
					mWeapon->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x + 30.f, tr->Getpos().y + 50.f));
			}
			else
			{
				if (mActiveWeapon != enums::eWeapon::None)
					mWeapon->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x - 30.f, tr->Getpos().y + 50.f));
			}
		}


		if (mActiveWeapon == enums::eWeapon::Onehand)
		{
			Transform* tr = GetComponent<Transform>();
			Transform* weaponcoltr = mWeaponCollider->GetComponent<Transform>();
			POINT pt = {};
			GetCursorPos(&pt);
			ScreenToClient(application.GetHWND(), &pt);
			Vector2<float> cursorpos;
			cursorpos.x = pt.x;
			cursorpos.y = pt.y;
			float radian = 0.f;
			float radian2 = 0.f;
			float degree = 0.f;
			//degree 구하기

			cursorpos = Camera::CaculatePos(-cursorpos);
			cursorpos = -cursorpos;

			radian2 = atan2(tr->Getpos().y - cursorpos.y, tr->Getpos().x - cursorpos.x);
			weaponcoltr->SetPos(Math::Vector2<float>(tr->Getpos().x - 60.f * cosf(radian2), tr->Getpos().y - 60.f * sinf(radian2)));

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
		if (mIsRight && mIsJump)
			GetComponent<Animator>()->PlayAnimation(L"PlayerRightIdle", true);
		else if (!mIsRight && mIsJump)
			GetComponent<Animator>()->PlayAnimation(L"PlayerLeftIdle", true);
		else if (mIsRight && !mIsJump)
			GetComponent<Animator>()->PlayAnimation(L"PlayerRightJump", false);
		else if (!mIsRight && !mIsJump)
			GetComponent<Animator>()->PlayAnimation(L"PlayerLeftJump", false);

		if (mSound != nullptr)
		{
			mSound->Stop(true);
		}

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

			mActiveWeapon = enums::eWeapon::Onehand;
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
			Objdata::SetActiveWeapon(mActiveWeapon);
			Objdata::SetWeapon(weapon);

			Weapon* weaponcollider = object::Instantiate<Weapon>(enums::eLayerType::Sword);
			Transform* weapontr = weaponcollider->GetComponent<Transform>();
			Collider* weaponcol = weaponcollider->AddComponent<Collider>();
			weapontr->SetPos(Math::Vector2<float>(tr->Getpos().x + 60.f * cosf(radian), tr->Getpos().y + 60.f * sinf(radian)));
			weaponcol->SetScale(Math::Vector2<float>(120.f, 120.f));
			weaponcol->SetType(Collider::eColliderType::Circle);
			mWeaponCollider = weaponcollider;
			weaponcol->enabled(false);
			weaponcollider->SetDelayTime(0.1f);
			Objdata::SetWeaponCollider(weaponcollider);

			texture = Resources::Load<Texture>(L"Sword1", L"..\\Resources\\Player\\Basic\\Attack\\ShortSword.png");
			mCanvas->AddImageObject(L"Sword1", texture, false, Math::Vector2<float>(1180.f, 660.f), Math::Vector2<float>(76.f, 28.f));
		}

		if (Input::Getkey(eKeyCode::L).state == eKeyState::DOWN)
		{
			EH::Destroy(mWeapon);
		}

		if (Input::Getkey(eKeyCode::A).state == eKeyState::PRESSED)
		{
			mCurState = eAnimationState::Move;
			if (mIsRight && mIsJump)
			{
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightRun", true);
				if (mSound != nullptr)
				{
					mSound->Stop(true);
				}
				mSound = Resources::Find<Sound>(L"PlayerRunSound");
				mSound->Play(true);
			}
			else if (!mIsRight && mIsJump)
			{
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftRun", true);
				if (mSound != nullptr)
				{
					mSound->Stop(true);
				}
				mSound = Resources::Find<Sound>(L"PlayerRunSound");
				mSound->Play(true);
			}
		}

		if (Input::Getkey(eKeyCode::S).state == eKeyState::DOWN)
		{
			mCurState = eAnimationState::DownJump;
		}

		if (Input::Getkey(eKeyCode::D).state == eKeyState::PRESSED)
		{
			mCurState = eAnimationState::Move;
			if (mIsRight && mIsJump)
			{
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightRun", true);
				if (mSound != nullptr)
				{
					mSound->Stop(true);
				}
				mSound = Resources::Find<Sound>(L"PlayerRunSound");
				mSound->Play(true);
			}
			else if (!mIsRight && mIsJump)
			{
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftRun", true);
				if (mSound != nullptr)
				{
					mSound->Stop(true);
				}
				mSound = Resources::Find<Sound>(L"PlayerRunSound");
				mSound->Play(true);
			}
		}

		if (Input::Getkey(eKeyCode::Space).state == eKeyState::DOWN && mJumpStack < 2)
		{
			mCurState = eAnimationState::Jump;
			mJumpStack++;

			Math::Vector2<float> velocity = GetComponent<Rigidbody>()->GetVelocity();
			GetComponent<Rigidbody>()->SetVeclocity(Math::Vector2<float>(velocity.x + 0.f, velocity.y + -500.f));
			GetComponent<Rigidbody>()->SetGround(false);

			if (mIsRight)
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightJump", false);
			else
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftJump", false);

			if (mSound != nullptr)
			{
				mSound->Stop(true);
			}
			mSound = Resources::Find<Sound>(L"PlayerJumpSound");
			mSound->Play(true);
		}

		if (Input::Getkey(eKeyCode::MouseLeftClick).state == eKeyState::DOWN && !mIsAttack)
		{
			if (mActiveWeapon != enums::eWeapon::None)
			{
				mCurState = eAnimationState::Attack;
				mIsSwing = !mIsSwing;
				Objdata::SetSwing(mIsSwing);
				if (mSound != nullptr)
				{
					mSound->Stop(true);
				}
				mSound = Resources::Find<Sound>(L"PlayerSwingSound");
				mSound->Play(false);
			}
		}
		if (Input::Getkey(eKeyCode::MouseRightClick).state == eKeyState::DOWN)
		{
			mCurState = eAnimationState::Dash;
			if (mSound != nullptr)
			{
				mSound->Stop(true);
			}
			mSound = Resources::Find<Sound>(L"PlayerDashSound");
			mSound->Play(false);
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

		if (mIsRight && !mIsJump)
			GetComponent<Animator>()->PlayAnimation(L"PlayerRightJump", false);
		else if (!mIsRight && !mIsJump)
			GetComponent<Animator>()->PlayAnimation(L"PlayerLeftJump", false);

		if (Input::Getkey(eKeyCode::A).state == eKeyState::PRESSED)
		{
			if (mIsRight && mIsJump)
			{
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightRun", true);
			}
			else if (!mIsRight && mIsJump)
			{
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftRun", true);
			}
			if (mIsSlope)
			{
				if (mIsRightSlope)
				{
					pos.x -= 200.f * Time::GetDeltaTime();
					pos.y += 200.f * Time::GetDeltaTime();
				}
				else
				{
					pos.x -= 200.f * Time::GetDeltaTime();
					pos.y -= 200.f * Time::GetDeltaTime();
				}
			}
			else
			{
				pos.x -= 300.f * Time::GetDeltaTime();
			}
			//GetComponent<Rigidbody>()->AddForce(Math::Vector2<float>(-200.f, 0.f));
		}
		if (Input::Getkey(eKeyCode::S).state == eKeyState::PRESSED)
		{
			mCurState = eAnimationState::DownJump;
		}
		if (Input::Getkey(eKeyCode::D).state == eKeyState::PRESSED)
		{
			if (mIsRight && mIsJump)
			{
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightRun", true);
			}
			else if (!mIsRight && mIsJump)
			{
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftRun", true);
			}

			if (mIsSlope)
			{
				if (mIsRightSlope)
				{
					pos.x += 200.f * Time::GetDeltaTime();
					pos.y -= 200.f * Time::GetDeltaTime();
				}
				else
				{
					pos.x += 200.f * Time::GetDeltaTime();
					pos.y += 200.f * Time::GetDeltaTime();
				}
			}
			else
			{
				pos.x += 300.f * Time::GetDeltaTime();
			}
			//GetComponent<Rigidbody>()->AddForce(Math::Vector2<float>(200.f, 0.f));
		}
		if (Input::Getkey(eKeyCode::Space).state == eKeyState::DOWN && mJumpStack < 2)
		{
			mCurState = eAnimationState::Jump;
			mJumpStack++;

			Math::Vector2<float> velocity = GetComponent<Rigidbody>()->GetVelocity();
			GetComponent<Rigidbody>()->SetVeclocity(Math::Vector2<float>(velocity.x + 0.f, velocity.y + -500.f));
			GetComponent<Rigidbody>()->SetGround(false);

			if (mIsRight)
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightJump", false);
			else
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftJump", false);

			if (mSound != nullptr)
			{
				mSound->Stop(true);
			}
			mSound = Resources::Find<Sound>(L"PlayerJumpSound");
			mSound->Play(false);
		}
		if (Input::Getkey(eKeyCode::MouseLeftClick).state == eKeyState::DOWN && !mIsAttack)
		{
			if (mActiveWeapon != enums::eWeapon::None)
			{
				mCurState = eAnimationState::Attack;
				mIsSwing = !mIsSwing;
				Objdata::SetSwing(mIsSwing);
				if (mSound != nullptr)
				{
					mSound->Stop(true);
				}
				mSound = Resources::Find<Sound>(L"PlayerSwingSound");
				mSound->Play(false);
			}
		}
		if (Input::Getkey(eKeyCode::MouseRightClick).state == eKeyState::DOWN)
		{
			mCurState = eAnimationState::Dash;

			if (mSound != nullptr)
			{
				mSound->Stop(true);
			}
			mSound = Resources::Find<Sound>(L"PlayerDashSound");
			mSound->Play(false);
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
		if (Input::Getkey(eKeyCode::MouseLeftClick).state == eKeyState::DOWN && !mIsAttack)
		{
			if (mActiveWeapon != enums::eWeapon::None)
			{
				mCurState = eAnimationState::Attack;
				mIsSwing = !mIsSwing;
				Objdata::SetSwing(mIsSwing);
				if (mSound != nullptr)
				{
					mSound->Stop(true);
				}
				mSound = Resources::Find<Sound>(L"PlayerSwingSound");
				mSound->Play(false);
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
		if (mCurHp <= 0.f)
		{
			mCurState = eAnimationState::Die;
			if (mIsRight)
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightDie", false);
			else
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftDie", false);

			mIsDead = true;
			return;
		}
		if (Input::Getkey(eKeyCode::Space).state == eKeyState::DOWN && mJumpStack < 2)
		{
			mCurState = eAnimationState::Jump;
			mJumpStack++;
			if (mIsRight)
				GetComponent<Animator>()->PlayAnimation(L"PlayerRightJump", false);
			else
				GetComponent<Animator>()->PlayAnimation(L"PlayerLeftJump", false);
		}
		if (mActiveWeapon == enums::eWeapon::Onehand)
		{
			// 일단 시간 재고
			mWeaponCollider->GetComponent<Collider>()->enabled(true);
			mIsAttack = true;
			mCheckTime = 0.f;
		}
		if (Input::Getkey(eKeyCode::MouseLeftClick).state == eKeyState::UP)
		{
			mCurState = eAnimationState::Idle;
		}
	}

	void Player::Dash()
	{
		Math::Vector2<float> pos = GetComponent<Transform>()->Getpos();
		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(application.GetHWND(), &pt);
		Math::Vector2<float> cursurpos(pt.x, pt.y);
		cursurpos = Camera::CaculatePos(-cursurpos);
		cursurpos = -cursurpos;
		float radian = Math::Radian(cursurpos, pos);

		pos.x += cosf(radian) * 20.f;
		pos.y += sinf(radian) * 20.f;

		GetComponent<Transform>()->SetPos(pos);

		if (Input::Getkey(eKeyCode::MouseRightClick).state == eKeyState::UP)
		{
			mCurState = eAnimationState::Idle;
		}
	}

	void Player::DownJump()
	{
		if (Input::Getkey(eKeyCode::Space).state == eKeyState::DOWN && !mOnBlock)
		{
			Math::Vector2<float> velocity = GetComponent<Rigidbody>()->GetVelocity();
			GetComponent<Rigidbody>()->SetVeclocity(Math::Vector2<float>(velocity.x + 0.f, velocity.y + 50.f));
			GetComponent<Rigidbody>()->SetGround(false);
		}
		if (Input::Getkey(eKeyCode::S).state == eKeyState::UP)
		{
			mCurState = eAnimationState::Idle;
		}
	}

	void Player::OnCollisionEnter(Collider* other)
	{
	}

	void Player::OnCollisionStay(Collider* other)
	{
		// DownJump
		Floor* check = dynamic_cast<Floor*>(other->GetOwner());
		if (check != nullptr)
		{
			if (!(check->GetDownFloor()))
			{
				mOnBlock = true;
			}
		}
	}

	void Player::OnCollisionExit(Collider* other)
	{
		// DownJump
		Floor* check = dynamic_cast<Floor*>(other->GetOwner());
		if (check != nullptr)
		{
			if (!(check->GetDownFloor()))
			{
				mOnBlock = false;
			}
		}
	}
}