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
#include "EHBullet.h"
#include "EHEffect.h"
#include "EHLaser.h"

extern EH::Application application;

namespace EH
{
	UINT Player::mCheck1 = 0;

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
		, mSubWeapon(enums::eWeapon::None)
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
		, mInventory{}
		, mOpeninventory(false)
		, mClicked(false)
	{
		AddComponent<Rigidbody>();

		if (mCheck1 == 0)
		{
			mCheck1++;
			mInventory[0][0] = L"Sword";
			//mInventory[0][1] = L"Wand";
			//mInventory[0][2] = L"TwoHand";
			//mInventory[0][3] = L"Gun";
			Objdata::SetInventory(mInventory);
		}

		Texture* texture = Resources::Load<Texture>(L"SwordInventorybox", L"..\\Resources\\Player\\Basic\\Attack\\ShortSword\\ShortSword.png");
		texture->Enabled(false);

		texture = Resources::Load<Texture>(L"WandInventorybox", L"..\\Resources\\Player\\Basic\\Attack\\Lalawand\\Lala'sMagicWand.png");
		texture->Enabled(false);

		texture = Resources::Load<Texture>(L"TwoHandInventorybox", L"..\\Resources\\Player\\Basic\\Attack\\TwoHand\\SkeletonKingJewelSword.png");
		texture->Enabled(false);

		texture = Resources::Load<Texture>(L"GunInventorybox", L"..\\Resources\\Player\\Basic\\Attack\\Gun\\Right\\Revolver2.png");
		texture->Enabled(false);

		// Animation setting
		texture = Resources::Load<Texture>(L"PlayerRightIdle", L"..\\Resources\\Player\\Basic\\Idle\\CharRightIdleSheet.bmp");
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

		// Inventory
		texture = Resources::Load<Texture>(L"InventoryBase", L"..\\Resources\\UI\\InventoryBase.png");
		texture->Enabled(false);
		PlayerUICanvas->AddImageObject(L"InventoryBase", texture, false, Math::Vector2<float>(1034.f, 360.f), Math::Vector2<float>(492.f, 720.f));

		PlayerUICanvas->AddImageObject(L"InventoryWeapon", nullptr, false, Math::Vector2<float>(890.f, 165.f), Math::Vector2<float>(57.f, 21.f));
		PlayerUICanvas->AddImageObject(L"InventorySubWeapon", nullptr, false, Math::Vector2<float>(1105.f, 165.f), Math::Vector2<float>(57.f, 21.f));

		texture = Resources::Load<Texture>(L"InventoryBox", L"..\\Resources\\UI\\InventoryBox.png");
		texture->Enabled(false);
		for (size_t y = 0; y < 3; y++)
		{
			for (size_t x = 0; x < 5; x++)
			{
				PlayerUICanvas->AddImageObject(L"InventoryBox" + std::to_wstring(y * 5 + x), texture, false, Math::Vector2<float>(865.f + 88.f * x, 390.f + 88.f * y), Math::Vector2<float>(76.f, 76.f));
				PlayerUICanvas->AddImageObject(L"InventoryItem" + std::to_wstring(y * 5 + x), nullptr, false, Math::Vector2<float>(865.f + 88.f * x, 390.f + 88.f * y), Math::Vector2<float>(76.f, 76.f));
			}
		}
		texture = Resources::Load<Texture>(L"InventoryBox_Selected", L"..\\Resources\\UI\\InventoryBox_Selected.png");

		// Sound setting
		Sound* sound = Resources::Load<Sound>(L"PlayerRunSound", L"..\\Resources\\Sound\\Player\\Run\\step_lth1.wav");
		sound = Resources::Load<Sound>(L"PlayerJumpSound", L"..\\Resources\\Sound\\Player\\Jump\\Jumping.wav");
		sound = Resources::Load<Sound>(L"PlayerSwingSound", L"..\\Resources\\Sound\\Player\\Attack\\swing3.wav");
		sound = Resources::Load<Sound>(L"PlayerDashSound", L"..\\Resources\\Sound\\Player\\Dash\\Dash.wav");

		mTwoHandSkillSound = Resources::Load<Sound>(L"PlayerTwoHandSkillSound", L"..\\Resources\\Sound\\Enemy\\JailField\\Belial\\iceball.wav");
		mWandSkillSound = Resources::Load<Sound>(L"PlayerWandSkillSound", L"..\\Resources\\Sound\\Player\\Attack\\Wand\\MagicWandSkill.wav");
		mGunSound = Resources::Load<Sound>(L"PlayerGunSound", L"..\\Resources\\Sound\\Player\\Attack\\Gun\\Gun.wav");
		mWandSound = Resources::Load<Sound>(L"PlayerWandSound", L"..\\Resources\\Sound\\Player\\Attack\\Wand\\MagicWandAttack.wav");
		mOpeninventorysound = Resources::Load<Sound>(L"OpenInventory", L"..\\Resources\\Sound\\Player\\Inventory\\OpenInventory.wav");
		mSwapSound= Resources::Load<Sound>(L"SwapWeapon", L"..\\Resources\\Sound\\Player\\Inventory\\etc-sound0033_swap.wav");

		mCanvas = PlayerUICanvas;
		mCanvas->AddImageObject(L"Swordslot", nullptr, false, Math::Vector2<float>(1180.f, 660.f), Math::Vector2<float>(76.f, 28.f));
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
		case eAnimationState::Skill:
			Skill();
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

		Objdata::GetInventory(mInventory);

		if (mWeapon != Objdata::GetWeapon())
		{
			SceneManager::GetCurScene()->SetLayer(enums::eLayerType::UI, Objdata::GetWeapon());
			mWeapon = Objdata::GetWeapon();
		}

		if (mIsSwing != Objdata::GetSwing())
		{
			mIsSwing = Objdata::GetSwing();
		}

		if (mActiveWeapon != Objdata::GetActiveWeapon())
		{
			mActiveWeapon = Objdata::GetActiveWeapon();
		}

		if (mSubWeapon != Objdata::GetSubWeapon())
		{
			mSubWeapon = Objdata::GetSubWeapon();
		}

		if (mWeaponCollider != Objdata::GetWeaponCollider())
		{
			if (Objdata::GetWeaponCollider() == nullptr)
			{
				mWeaponCollider = Objdata::GetWeaponCollider();
				Objdata::SetWeaponCollider(mWeaponCollider);
			}
			else
			{
				SceneManager::GetCurScene()->SetLayer(enums::eLayerType::Sword, Objdata::GetWeaponCollider());
				mWeaponCollider = Objdata::GetWeaponCollider();
				Objdata::SetWeaponCollider(mWeaponCollider);
			}
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
		Texture* texture = nullptr;

		Transform* tr = GetComponent<Transform>();

		if (mIsSwing)
		{
			if (mIsRight)
			{
				if (mActiveWeapon == enums::eWeapon::Onehand || mActiveWeapon == enums::eWeapon::Wand)
					mWeapon->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x + 30.f, tr->Getpos().y));

				if (mActiveWeapon == enums::eWeapon::Gun)
					mWeapon->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x + 30.f, tr->Getpos().y));

				if (mActiveWeapon == enums::eWeapon::Twohand)
					mWeapon->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x + 40.f, tr->Getpos().y - 30.f));
			}
			else
			{
				if (mActiveWeapon == enums::eWeapon::Onehand || mActiveWeapon == enums::eWeapon::Wand)
					mWeapon->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x - 30.f, tr->Getpos().y));

				if (mActiveWeapon == enums::eWeapon::Gun)
					mWeapon->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x - 30.f, tr->Getpos().y));

				if (mActiveWeapon == enums::eWeapon::Twohand)
					mWeapon->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x - 40.f, tr->Getpos().y - 30.f));
			}
		}
		else
		{
			if (mIsRight)
			{
				if (mActiveWeapon == enums::eWeapon::Onehand || mActiveWeapon == enums::eWeapon::Wand)
					mWeapon->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x + 30.f, tr->Getpos().y + 50.f));

				if (mActiveWeapon == enums::eWeapon::Gun)
					mWeapon->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x + 30.f, tr->Getpos().y) + 20.f);

				if (mActiveWeapon == enums::eWeapon::Twohand)
					mWeapon->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x + 40.f, tr->Getpos().y + 50.f));
			}
			else
			{
				if (mActiveWeapon == enums::eWeapon::Onehand || mActiveWeapon == enums::eWeapon::Wand)
					mWeapon->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x - 30.f, tr->Getpos().y + 50.f));

				if (mActiveWeapon == enums::eWeapon::Gun)
					mWeapon->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x - 30.f, tr->Getpos().y + 20.f));

				if (mActiveWeapon == enums::eWeapon::Twohand)
					mWeapon->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x - 40.f, tr->Getpos().y + 50.f));
			}
		}

		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(application.GetHWND(), &pt);
		Vector2<float> cursorpos;
		cursorpos.x = pt.x;
		cursorpos.y = pt.y;

		cursorpos = Camera::CaculatePos(-cursorpos);
		cursorpos = -cursorpos;

		if (mActiveWeapon == enums::eWeapon::Onehand)
		{
			Texture* texture = Resources::Load<Texture>(L"SwordWeaponbox", L"..\\Resources\\Player\\Basic\\Attack\\ShortSword\\ShortSword.png");
			ImageObject* inventoryweapon = mCanvas->Find(L"InventoryWeapon");
			inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
			texture = Resources::Load<Texture>(L"Swordslot", L"..\\Resources\\Player\\Basic\\Attack\\ShortSword\\ShortSword.png");
			mCanvas->Find(L"Swordslot")->GetComponent<SpriteRenderer>()->SetImg(texture);


			mWeapon->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
			float radian = 0.f;
			float radian2 = 0.f;
			float degree = 0.f;
			//degree 구하기

			radian2 = atan2(tr->Getpos().y - cursorpos.y, tr->Getpos().x - cursorpos.x);

			if (mWeaponCollider != nullptr)
			{
				Transform* weaponcoltr = mWeaponCollider->GetComponent<Transform>();
				weaponcoltr->SetPos(Math::Vector2<float>(tr->Getpos().x - 60.f * cosf(radian2), tr->Getpos().y - 60.f * sinf(radian2)));
			}

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
		else if (mActiveWeapon == enums::eWeapon::Wand)
		{
			Texture* texture = Resources::Load<Texture>(L"WandWeaponbox", L"..\\Resources\\Player\\Basic\\Attack\\LalaWand\\Lala'sMagicWand.png");
			ImageObject* inventoryweapon = mCanvas->Find(L"InventoryWeapon");
			inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
			texture = Resources::Load<Texture>(L"Wandslot", L"..\\Resources\\Player\\Basic\\Attack\\LalaWand\\Lala'sMagicWand.png");
			mCanvas->Find(L"Swordslot")->GetComponent<SpriteRenderer>()->SetImg(texture);

			mIsAttack = false;
			mWeapon->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
			float radian = 0.f;
			float radian2 = 0.f;
			float degree = 0.f;
			//degree 구하기

			radian2 = atan2(tr->Getpos().y - cursorpos.y, tr->Getpos().x - cursorpos.x);
			if (mIsSwing)
			{
				if (cursorpos.x > tr->Getpos().x)
				{
					radian = atan2(tr->Getpos().y - cursorpos.y, cursorpos.x - tr->Getpos().x);
					degree = radian * (180.f / 3.14f);
					mWeapon->GetComponent<SpriteRenderer>()->GetImg()->SetDegree(-(7 + degree));
					mIsRight = true;
				}
				else
				{
					radian = atan2(tr->Getpos().y - cursorpos.y, tr->Getpos().x - cursorpos.x);
					degree = radian * (180.f / 3.14f);
					mWeapon->GetComponent<SpriteRenderer>()->GetImg()->SetDegree(7 + degree);
					mIsRight = false;
				}
			}
			else
			{
				if (cursorpos.x > tr->Getpos().x)
				{
					radian = atan2(tr->Getpos().y - cursorpos.y, cursorpos.x - tr->Getpos().x);
					degree = radian * (180.f / 3.14f);
					mWeapon->GetComponent<SpriteRenderer>()->GetImg()->SetDegree(-7 - degree - 180);
					mIsRight = true;
				}
				else
				{
					radian = atan2(tr->Getpos().y - cursorpos.y, tr->Getpos().x - cursorpos.x);
					degree = radian * (180.f / 3.14f);
					mWeapon->GetComponent<SpriteRenderer>()->GetImg()->SetDegree(180 + 7 + degree);
					mIsRight = false;
				}
			}
		}
		else if (mActiveWeapon == enums::eWeapon::Gun)
		{
			Texture* texture = Resources::Load<Texture>(L"GunWeaponbox", L"..\\Resources\\Player\\Basic\\Attack\\Gun\\Right\\Revolver2.png");
			ImageObject* inventoryweapon = mCanvas->Find(L"InventoryWeapon");
			inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
			texture = Resources::Load<Texture>(L"Gunslot", L"..\\Resources\\Player\\Basic\\Attack\\Gun\\Right\\Revolver2.png");
			mCanvas->Find(L"Swordslot")->GetComponent<SpriteRenderer>()->SetImg(texture);

			mIsAttack = false;
			mWeapon->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
			float radian = 0.f;
			float radian2 = 0.f;
			float degree = 0.f;
			//degree 구하기

			if (cursorpos.x > tr->Getpos().x)
			{
				radian = atan2(tr->Getpos().y - cursorpos.y, cursorpos.x - tr->Getpos().x);
				degree = radian * (180.f / 3.14f);
				texture = Resources::Load<Texture>(L"GunRight", L"..\\Resources\\Player\\Basic\\Attack\\Gun\\Right\\Revolver2.png");
				mWeapon->GetComponent<SpriteRenderer>()->SetImg(texture);
				mWeapon->GetComponent<SpriteRenderer>()->GetImg()->SetDegree(-degree);
				mIsRight = true;
			}
			else
			{
				radian = atan2(tr->Getpos().y - cursorpos.y, tr->Getpos().x - cursorpos.x);
				degree = radian * (180.f / 3.14f);
				texture = Resources::Load<Texture>(L"GunLeft", L"..\\Resources\\Player\\Basic\\Attack\\Gun\\Left\\Revolver2.png");
				mWeapon->GetComponent<SpriteRenderer>()->SetImg(texture);
				mWeapon->GetComponent<SpriteRenderer>()->GetImg()->SetDegree(degree);
				mIsRight = false;
			}
		}
		else if (mActiveWeapon == enums::eWeapon::Twohand)
		{
			Texture* texture = Resources::Load<Texture>(L"TwoHandWeaponbox", L"..\\Resources\\Player\\Basic\\Attack\\TwoHand\\SkeletonKingJewelSword.png");
			ImageObject* inventoryweapon = mCanvas->Find(L"InventoryWeapon");
			inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
			texture = Resources::Load<Texture>(L"TwoHandslot", L"..\\Resources\\Player\\Basic\\Attack\\TwoHand\\SkeletonKingJewelSword.png");
			mCanvas->Find(L"Swordslot")->GetComponent<SpriteRenderer>()->SetImg(texture);

			mWeapon->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
			float radian = 0.f;
			float radian2 = 0.f;
			float degree = 0.f;
			//degree 구하기

			radian2 = atan2(tr->Getpos().y - cursorpos.y, tr->Getpos().x - cursorpos.x);

			if (mWeaponCollider != nullptr)
			{
				Transform* weaponcoltr = mWeaponCollider->GetComponent<Transform>();
				weaponcoltr->SetPos(Math::Vector2<float>(tr->Getpos().x - 60.f * cosf(radian2), tr->Getpos().y - 60.f * sinf(radian2)));
			}

			if (mIsSwing)
			{
				if (cursorpos.x > tr->Getpos().x)
				{
					radian = atan2(tr->Getpos().y - cursorpos.y, cursorpos.x - tr->Getpos().x);
					degree = radian * (180.f / 3.14f);
					mWeapon->GetComponent<SpriteRenderer>()->GetImg()->SetDegree(-(7 + degree));
					mIsRight = true;
				}
				else
				{
					radian = atan2(tr->Getpos().y - cursorpos.y, tr->Getpos().x - cursorpos.x);
					degree = radian * (180.f / 3.14f);
					mWeapon->GetComponent<SpriteRenderer>()->GetImg()->SetDegree(7 + degree);
					mIsRight = false;
				}
			}
			else
			{
				if (cursorpos.x > tr->Getpos().x)
				{
					radian = atan2(tr->Getpos().y - cursorpos.y, cursorpos.x - tr->Getpos().x);
					degree = radian * (180.f / 3.14f);
					mWeapon->GetComponent<SpriteRenderer>()->GetImg()->SetDegree(-7 - degree - 180);
					mIsRight = true;
				}
				else
				{
					radian = atan2(tr->Getpos().y - cursorpos.y, tr->Getpos().x - cursorpos.x);
					degree = radian * (180.f / 3.14f);
					mWeapon->GetComponent<SpriteRenderer>()->GetImg()->SetDegree(180 + 7 + degree);
					mIsRight = false;
				}
			}
		}
		else
		{
			Texture* texture = Resources::Load<Texture>(L"TransWeaponbox", L"..\\Resources\\Player\\Basic\\Trans.png");
			ImageObject* inventoryweapon = mCanvas->Find(L"InventoryWeapon");
			inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
			texture = Resources::Load<Texture>(L"TransWeapon", L"..\\Resources\\Player\\Basic\\Trans.png");
			mCanvas->Find(L"Swordslot")->GetComponent<SpriteRenderer>()->SetImg(texture);

			if (cursorpos.x > tr->Getpos().x)
			{
				mIsRight = true;
			}
			else
			{
				mIsRight = false;
			}
		}

		if (mSubWeapon == enums::eWeapon::Onehand)
		{
			Texture* texture = Resources::Load<Texture>(L"SwordWeaponbox", L"..\\Resources\\Player\\Basic\\Attack\\ShortSword\\ShortSword.png");
			ImageObject* inventoryweapon = mCanvas->Find(L"InventorySubWeapon");
			inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
		}
		else if (mSubWeapon == enums::eWeapon::Wand)
		{
			Texture* texture = Resources::Load<Texture>(L"WandWeaponbox", L"..\\Resources\\Player\\Basic\\Attack\\LalaWand\\Lala'sMagicWand.png");
			ImageObject* inventoryweapon = mCanvas->Find(L"InventorySubWeapon");
			inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
		}
		else if (mSubWeapon == enums::eWeapon::Gun)
		{
			Texture* texture = Resources::Load<Texture>(L"GunWeaponbox", L"..\\Resources\\Player\\Basic\\Attack\\Gun\\Right\\Revolver2.png");
			ImageObject* inventoryweapon = mCanvas->Find(L"InventorySubWeapon");
			inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
		}
		else if (mSubWeapon == enums::eWeapon::Twohand)
		{
			Texture* texture = Resources::Load<Texture>(L"TwoHandWeaponbox", L"..\\Resources\\Player\\Basic\\Attack\\TwoHand\\SkeletonKingJewelSword.png");
			ImageObject* inventoryweapon = mCanvas->Find(L"InventorySubWeapon");
			inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
		}
		else
		{
			Texture* texture = Resources::Load<Texture>(L"TransWeaponbox", L"..\\Resources\\Player\\Basic\\Trans.png");
			ImageObject* inventoryweapon = mCanvas->Find(L"InventorySubWeapon");
			inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
		}

		// 아이템 설정
		for (size_t y = 0; y < 3; y++)
		{
			for (size_t x = 0; x < 5; x++)
			{
				std::wstring name = mInventory[y][x];
				SpriteRenderer* inventoryitem = mCanvas->Find(L"InventoryItem" + std::to_wstring(y * 5 + x))->GetComponent<SpriteRenderer>();
				texture = Resources::Load<Texture>(name + L"Inventorybox", L"");
				inventoryitem->SetImg(texture);
			}
		}

		// Inventory
		if (mOpeninventory)
		{
			POINT pt = {};
			GetCursorPos(&pt);
			ScreenToClient(application.GetHWND(), &pt);
			Vector2<float> cursorpos;
			cursorpos.x = pt.x;
			cursorpos.y = pt.y;
			UINT inventory = -1;
			UINT dy = -1;
			UINT dx = -1;
			// 인벤토리 박스 초기화
			for (size_t y = 0; y < 3; y++)
			{
				for (size_t x = 0; x < 5; x++)
				{
					SpriteRenderer* inventorybox = mCanvas->Find(L"InventoryBox" + std::to_wstring(y * 5 + x))->GetComponent<SpriteRenderer>();
					texture = Resources::Load<Texture>(L"InventoryBox", L"");
					inventorybox->SetImg(texture);
				}
			}

			// 박스 위 아이템 표시
			for (size_t y = 0; y < 3; y++)
			{
				for (size_t x = 0; x < 5; x++)
				{
					if (mInventory[y][x] != L"")
					{
						Texture* texture = mCanvas->Find(L"InventoryItem" + std::to_wstring(y * 5 + x))->GetComponent<SpriteRenderer>()->GetImg();
						texture->Enabled(true);
					}
					else
					{
						Texture* texture = mCanvas->Find(L"InventoryItem" + std::to_wstring(y * 5 + x))->GetComponent<SpriteRenderer>()->GetImg();
						texture->Enabled(false);
					}
				}
			}

			// 아이템 선택 확인
			for (size_t y = 0; y < 3; y++)
			{
				for (size_t x = 0; x < 5; x++)
				{
					if ((cursorpos.x < 865.f + 88.f * x + 38.f && cursorpos.x > 865.f + 88.f * x - 38.f) &&
						(cursorpos.y < 390.f + 88.f * y + 38.f && cursorpos.y > 390.f + 88.f * y - 38.f))
					{
						inventory = y * 5 + x;
						dy = y;
						dx = x;
					}
				}
			}
			if (inventory != -1)
			{
				SpriteRenderer* inventorybox = mCanvas->Find(L"InventoryBox" + std::to_wstring(inventory))->GetComponent<SpriteRenderer>();
				texture = Resources::Load<Texture>(L"InventoryBox_Selected", L"..\\Resources\\UI\\InventoryBox_Selected.png");
				inventorybox->SetImg(texture);

				if (Input::Getkey(eKeyCode::MouseRightClick).state == eKeyState::DOWN)
				{
					std::wstring item = mInventory[dy][dx];
					if (item == L"Sword")
					{
						mInventory[dy][dx] = L"";
						if (mActiveWeapon == enums::eWeapon::Wand)
						{
							UINT mCheck1 = 0;
							for (int y = 0;y < 3;y++)
							{
								for (int x = 0;x < 5;x++)
								{
									if (mInventory[y][x] == L"")
									{
										mInventory[y][x] = L"Wand";
										Objdata::GetMagicWand()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
										mCheck1 = 1;
										break;
									}
								}
								if (mCheck1 == 1)
									break;
							}
						}
						else if (mActiveWeapon == enums::eWeapon::Twohand)
						{
							UINT mCheck1 = 0;
							for (int y = 0;y < 3;y++)
							{
								for (int x = 0;x < 5;x++)
								{
									if (mInventory[y][x] == L"")
									{
										mInventory[y][x] = L"TwoHand";
										Objdata::GetBelialSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
										mCheck1 = 1;
										break;
									}
								}
								if (mCheck1 == 1)
									break;
							}
						}
						else if (mActiveWeapon == enums::eWeapon::Gun)
						{
							UINT mCheck1 = 0;
							for (int y = 0;y < 3;y++)
							{
								for (int x = 0;x < 5;x++)
								{
									if (mInventory[y][x] == L"")
									{
										mInventory[y][x] = L"Gun";
										Objdata::GetGun()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
										mCheck1 = 1;
										break;
									}
								}
								if (mCheck1 == 1)
									break;
							}
						}
						mActiveWeapon = enums::eWeapon::Onehand;
						texture = Resources::Load<Texture>(item + L"Inventorybox", L"");
						ImageObject* inventoryweapon = mCanvas->Find(L"InventoryWeapon");
						Transform* inventorytr = inventoryweapon->GetComponent<Transform>();
						inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
						inventorytr->SetScale(Math::Vector2<float>(57.f, 21.f));
						mWeapon = Objdata::GetSword();
						mWeaponCollider = Objdata::GetSwordCollider();
						Objdata::SetActiveWeapon(mActiveWeapon);
						Objdata::SetWeapon(mWeapon);
						Objdata::SetWeaponCollider(mWeaponCollider);
						SceneManager::GetCurScene()->SetLayer(enums::eLayerType::UI, mWeapon);
						SceneManager::GetCurScene()->SetLayer(enums::eLayerType::Sword, mWeaponCollider);
					}
					else if (item == L"Wand")
					{
						mInventory[dy][dx] = L"";
						if (mActiveWeapon == enums::eWeapon::Onehand)
						{
							UINT mCheck1 = 0;
							for (int y = 0;y < 3;y++)
							{
								for (int x = 0;x < 5;x++)
								{
									if (mInventory[y][x] == L"")
									{
										mInventory[y][x] = L"Sword";
										Objdata::GetSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
										mCheck1 = 1;
										break;
									}
								}
								if (mCheck1 == 1)
									break;
							}
						}
						else if (mActiveWeapon == enums::eWeapon::Twohand)
						{
							UINT mCheck1 = 0;
							for (int y = 0;y < 3;y++)
							{
								for (int x = 0;x < 5;x++)
								{
									if (mInventory[y][x] == L"")
									{
										mInventory[y][x] = L"TwoHand";
										Objdata::GetBelialSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
										mCheck1 = 1;
										break;
									}
								}
								if (mCheck1 == 1)
									break;
							}
						}
						else if (mActiveWeapon == enums::eWeapon::Gun)
						{
							UINT mCheck1 = 0;
							for (int y = 0;y < 3;y++)
							{
								for (int x = 0;x < 5;x++)
								{
									if (mInventory[y][x] == L"")
									{
										mInventory[y][x] = L"Gun";
										Objdata::GetGun()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
										mCheck1 = 1;
										break;
									}
								}
								if (mCheck1 == 1)
									break;
							}
						}

						mActiveWeapon = enums::eWeapon::Wand;
						texture = Resources::Load<Texture>(item + L"Inventorybox", L"");
						ImageObject* inventoryweapon = mCanvas->Find(L"InventoryWeapon");
						Transform* inventorytr = inventoryweapon->GetComponent<Transform>();
						inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
						inventorytr->SetScale(Math::Vector2<float>(57.f, 21.f));
						mWeapon = Objdata::GetMagicWand();
						mWeaponCollider = nullptr;
						Objdata::SetActiveWeapon(mActiveWeapon);
						Objdata::SetWeapon(mWeapon);
						Objdata::SetWeaponCollider(nullptr);
						SceneManager::GetCurScene()->SetLayer(enums::eLayerType::UI, mWeapon);
					}
					else if (item == L"TwoHand")
					{
						mInventory[dy][dx] = L"";
						if (mActiveWeapon == enums::eWeapon::Wand)
						{
							UINT mCheck1 = 0;
							for (int y = 0;y < 3;y++)
							{
								for (int x = 0;x < 5;x++)
								{
									if (mInventory[y][x] == L"")
									{
										mInventory[y][x] = L"Wand";
										Objdata::GetMagicWand()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
										mCheck1 = 1;
										break;
									}
								}
								if (mCheck1 == 1)
									break;
							}
						}
						else if (mActiveWeapon == enums::eWeapon::Onehand)
						{
							UINT mCheck1 = 0;
							for (int y = 0;y < 3;y++)
							{
								for (int x = 0;x < 5;x++)
								{
									if (mInventory[y][x] == L"")
									{
										mInventory[y][x] = L"Sword";
										Objdata::GetSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
										mCheck1 = 1;
										break;
									}
								}
								if (mCheck1 == 1)
									break;
							}
						}
						else if (mActiveWeapon == enums::eWeapon::Gun)
						{
							UINT mCheck1 = 0;
							for (int y = 0;y < 3;y++)
							{
								for (int x = 0;x < 5;x++)
								{
									if (mInventory[y][x] == L"")
									{
										mInventory[y][x] = L"Gun";
										Objdata::GetGun()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
										mCheck1 = 1;
										break;
									}
								}
								if (mCheck1 == 1)
									break;
							}
						}
						mActiveWeapon = enums::eWeapon::Twohand;
						texture = Resources::Load<Texture>(item + L"Inventorybox", L"");
						ImageObject* inventoryweapon = mCanvas->Find(L"InventoryWeapon");
						Transform* inventorytr = inventoryweapon->GetComponent<Transform>();
						inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
						inventorytr->SetScale(Math::Vector2<float>(57.f, 21.f));
						mWeapon = Objdata::GetBelialSword();
						mWeaponCollider = Objdata::GetBelialSwordCollider();
						Objdata::SetActiveWeapon(mActiveWeapon);
						Objdata::SetWeapon(mWeapon);
						Objdata::SetWeaponCollider(mWeaponCollider);
						SceneManager::GetCurScene()->SetLayer(enums::eLayerType::UI, mWeapon);
						SceneManager::GetCurScene()->SetLayer(enums::eLayerType::Sword, mWeaponCollider);
					}
					else if (item == L"Gun")
					{
						mInventory[dy][dx] = L"";
						if (mActiveWeapon == enums::eWeapon::Wand)
						{
							UINT mCheck1 = 0;
							for (int y = 0;y < 3;y++)
							{
								for (int x = 0;x < 5;x++)
								{
									if (mInventory[y][x] == L"")
									{
										mInventory[y][x] = L"Wand";
										Objdata::GetMagicWand()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
										mCheck1 = 1;
										break;
									}
								}
								if (mCheck1 == 1)
									break;
							}
						}
						else if (mActiveWeapon == enums::eWeapon::Twohand)
						{
							UINT mCheck1 = 0;
							for (int y = 0;y < 3;y++)
							{
								for (int x = 0;x < 5;x++)
								{
									if (mInventory[y][x] == L"")
									{
										mInventory[y][x] = L"TwoHand";
										Objdata::GetBelialSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
										mCheck1 = 1;
										break;
									}
								}
								if (mCheck1 == 1)
									break;
							}
						}
						else if (mActiveWeapon == enums::eWeapon::Onehand)
						{
							UINT mCheck1 = 0;
							for (int y = 0;y < 3;y++)
							{
								for (int x = 0;x < 5;x++)
								{
									if (mInventory[y][x] == L"")
									{
										mInventory[y][x] = L"Sword";
										Objdata::GetSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
										mCheck1 = 1;
										break;
									}
								}
								if (mCheck1 == 1)
									break;
							}
						}
						mActiveWeapon = enums::eWeapon::Gun;
						texture = Resources::Load<Texture>(item + L"Inventorybox", L"");
						ImageObject* inventoryweapon = mCanvas->Find(L"InventoryWeapon");
						Transform* inventorytr = inventoryweapon->GetComponent<Transform>();
						inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
						inventorytr->SetScale(Math::Vector2<float>(57.f, 21.f));
						mWeapon = Objdata::GetGun();
						mWeaponCollider = nullptr;
						Objdata::SetActiveWeapon(mActiveWeapon);
						Objdata::SetWeapon(mWeapon);
						Objdata::SetWeaponCollider(mWeaponCollider);
						SceneManager::GetCurScene()->SetLayer(enums::eLayerType::UI, mWeapon);
					}
					Objdata::SetInventory(mInventory);
				}
			}

			// 왼쪽 선택 확인
			if (Input::Getkey(eKeyCode::MouseLeftClick).state == eKeyState::DOWN)
			{
				for (int y = 0;y < 3;y++)
				{
					for (int x = 0;x < 5;x++)
					{
						if ((cursorpos.x < 865.f + 88.f * x + 38.f && cursorpos.x > 865.f + 88.f * x - 38.f) &&
							(cursorpos.y < 390.f + 88.f * y + 38.f && cursorpos.y > 390.f + 88.f * y - 38.f))
						{
							mClickedName = mInventory[y][x];
							mClicked = true;
						}
					}
				}
			}

			if (mClicked)
			{
				if (Input::Getkey(eKeyCode::MouseLeftClick).state == eKeyState::UP)
				{
					UINT lx = -1;
					UINT ly = -1;

					for (int y = 0;y < 3;y++)
					{
						for (int x = 0;x < 5;x++)
						{
							if (mInventory[y][x] == mClickedName)
							{
								lx = x;
								ly = y;
							}
						}
					}

					if ((cursorpos.x < 890.f + 38.f && cursorpos.x > 890.f - 38.f) &&
						(cursorpos.y < 165.f + 38.f && cursorpos.y > 165.f - 38.f))
					{
						if (mClickedName == L"Sword")
						{
							mInventory[ly][lx] = L"";
							if (mActiveWeapon == enums::eWeapon::Wand)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"Wand";
											mCheck1 = 1;
											Objdata::GetMagicWand()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							else if (mActiveWeapon == enums::eWeapon::Twohand)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"TwoHand";
											mCheck1 = 1;
											Objdata::GetBelialSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							else if (mActiveWeapon == enums::eWeapon::Gun)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"Gun";
											mCheck1 = 1;
											Objdata::GetGun()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							mActiveWeapon = enums::eWeapon::Onehand;
							texture = Resources::Load<Texture>(mClickedName + L"Inventorybox", L"");
							ImageObject* inventoryweapon = mCanvas->Find(L"InventoryWeapon");
							Transform* inventorytr = inventoryweapon->GetComponent<Transform>();
							inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
							inventorytr->SetScale(Math::Vector2<float>(57.f, 21.f));
							mWeapon = Objdata::GetSword();
							Objdata::GetSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
							mWeaponCollider = Objdata::GetSwordCollider();
							Objdata::SetActiveWeapon(mActiveWeapon);
							Objdata::SetWeapon(mWeapon);
							Objdata::SetWeaponCollider(mWeaponCollider);
							SceneManager::GetCurScene()->SetLayer(enums::eLayerType::UI, mWeapon);
							SceneManager::GetCurScene()->SetLayer(enums::eLayerType::Sword, mWeaponCollider);
						}
						else if (mClickedName == L"Wand")
						{
							mInventory[ly][lx] = L"";
							if (mActiveWeapon == enums::eWeapon::Onehand)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"Sword";
											mCheck1 = 1;
											Objdata::GetSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							else if (mActiveWeapon == enums::eWeapon::Twohand)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"TwoHand";
											mCheck1 = 1;
											Objdata::GetBelialSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							else if (mActiveWeapon == enums::eWeapon::Gun)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"Gun";
											mCheck1 = 1;
											Objdata::GetGun()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							mActiveWeapon = enums::eWeapon::Wand;
							texture = Resources::Load<Texture>(mClickedName + L"Inventorybox", L"");
							ImageObject* inventoryweapon = mCanvas->Find(L"InventoryWeapon");
							Transform* inventorytr = inventoryweapon->GetComponent<Transform>();
							inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
							inventorytr->SetScale(Math::Vector2<float>(57.f, 21.f));
							mWeapon = Objdata::GetMagicWand();
							Objdata::GetMagicWand()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
							mWeaponCollider = nullptr;
							Objdata::SetActiveWeapon(mActiveWeapon);
							Objdata::SetWeapon(mWeapon);
							Objdata::SetWeaponCollider(nullptr);
							SceneManager::GetCurScene()->SetLayer(enums::eLayerType::UI, mWeapon);
						}
						else if (mClickedName == L"TwoHand")
						{
							mInventory[ly][lx] = L"";
							if (mActiveWeapon == enums::eWeapon::Wand)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"Wand";
											Objdata::GetMagicWand()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											mCheck1 = 1;
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							else if (mActiveWeapon == enums::eWeapon::Onehand)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"Sword";
											Objdata::GetSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											mCheck1 = 1;
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							else if (mActiveWeapon == enums::eWeapon::Gun)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"Gun";
											Objdata::GetGun()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											mCheck1 = 1;
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							mActiveWeapon = enums::eWeapon::Twohand;
							texture = Resources::Load<Texture>(mClickedName + L"Inventorybox", L"");
							ImageObject* inventoryweapon = mCanvas->Find(L"InventoryWeapon");
							inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
							Transform* inventorytr = inventoryweapon->GetComponent<Transform>();
							inventorytr->SetScale(Math::Vector2<float>(57.f, 21.f));
							mWeapon = Objdata::GetBelialSword();
							mWeaponCollider = Objdata::GetBelialSwordCollider();
							Objdata::SetActiveWeapon(mActiveWeapon);
							Objdata::SetWeapon(mWeapon);
							Objdata::SetWeaponCollider(mWeaponCollider);
							SceneManager::GetCurScene()->SetLayer(enums::eLayerType::UI, mWeapon);
							SceneManager::GetCurScene()->SetLayer(enums::eLayerType::Sword, mWeaponCollider);
						}
						else if (mClickedName == L"Gun")
						{
							mInventory[ly][lx] = L"";
							if (mActiveWeapon == enums::eWeapon::Wand)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"Wand";
											Objdata::GetMagicWand()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											mCheck1 = 1;
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							else if (mActiveWeapon == enums::eWeapon::Twohand)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"TwoHand";
											Objdata::GetBelialSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											mCheck1 = 1;
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							else if (mActiveWeapon == enums::eWeapon::Onehand)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"Sword";
											Objdata::GetSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											mCheck1 = 1;
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							mActiveWeapon = enums::eWeapon::Gun;
							texture = Resources::Load<Texture>(mClickedName + L"Inventorybox", L"");
							ImageObject* inventoryweapon = mCanvas->Find(L"InventoryWeapon");
							Transform* inventorytr = inventoryweapon->GetComponent<Transform>();
							inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
							inventorytr->SetScale(Math::Vector2<float>(57.f, 21.f));
							mWeapon = Objdata::GetGun();
							mWeaponCollider = nullptr;
							Objdata::SetActiveWeapon(mActiveWeapon);
							Objdata::SetWeapon(mWeapon);
							Objdata::SetWeaponCollider(mWeaponCollider);
							SceneManager::GetCurScene()->SetLayer(enums::eLayerType::UI, mWeapon);
						}
						Objdata::SetInventory(mInventory);
					}

					if ((cursorpos.x < 1105.f + 38.f && cursorpos.x > 1105.f - 38.f) &&
						(cursorpos.y < 165.f + 38.f && cursorpos.y > 165.f - 38.f))
					{
						if (mClickedName == L"Sword")
						{
							mInventory[ly][lx] = L"";
							if (mSubWeapon == enums::eWeapon::Wand)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"Wand";
											mCheck1 = 1;
											Objdata::GetMagicWand()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							else if (mSubWeapon == enums::eWeapon::Twohand)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"TwoHand";
											mCheck1 = 1;
											Objdata::GetBelialSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							else if (mSubWeapon == enums::eWeapon::Gun)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"Gun";
											mCheck1 = 1;
											Objdata::GetGun()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							mSubWeapon = enums::eWeapon::Onehand;
							texture = Resources::Load<Texture>(mClickedName + L"Inventorybox", L"");
							ImageObject* inventoryweapon = mCanvas->Find(L"InventorySubWeapon");
							Transform* inventorytr = inventoryweapon->GetComponent<Transform>();
							inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
							inventorytr->SetScale(Math::Vector2<float>(57.f, 21.f));
							Objdata::SetSubWeapon(mSubWeapon);
						}
						else if (mClickedName == L"Wand")
						{
							mInventory[ly][lx] = L"";
							if (mSubWeapon == enums::eWeapon::Onehand)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"Sword";
											mCheck1 = 1;
											Objdata::GetSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							else if (mSubWeapon == enums::eWeapon::Twohand)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"TwoHand";
											mCheck1 = 1;
											Objdata::GetBelialSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							else if (mSubWeapon == enums::eWeapon::Gun)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"Gun";
											mCheck1 = 1;
											Objdata::GetGun()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							mSubWeapon = enums::eWeapon::Wand;
							texture = Resources::Load<Texture>(mClickedName + L"Inventorybox", L"");
							ImageObject* inventoryweapon = mCanvas->Find(L"InventorySubWeapon");
							Transform* inventorytr = inventoryweapon->GetComponent<Transform>();
							inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
							inventorytr->SetScale(Math::Vector2<float>(57.f, 21.f));
							Objdata::SetSubWeapon(mSubWeapon);
						}
						else if (mClickedName == L"TwoHand")
						{
							mInventory[ly][lx] = L"";
							if (mSubWeapon == enums::eWeapon::Wand)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"Wand";
											Objdata::GetMagicWand()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											mCheck1 = 1;
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							else if (mSubWeapon == enums::eWeapon::Onehand)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"Sword";
											Objdata::GetSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											mCheck1 = 1;
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							else if (mSubWeapon == enums::eWeapon::Gun)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"Gun";
											Objdata::GetGun()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											mCheck1 = 1;
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							mSubWeapon = enums::eWeapon::Twohand;
							texture = Resources::Load<Texture>(mClickedName + L"Inventorybox", L"");
							ImageObject* inventoryweapon = mCanvas->Find(L"InventorySubWeapon");
							Transform* inventorytr = inventoryweapon->GetComponent<Transform>();
							inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
							inventorytr->SetScale(Math::Vector2<float>(57.f, 21.f));
							Objdata::SetSubWeapon(mSubWeapon);
						}
						else if (mClickedName == L"Gun")
						{
							mInventory[ly][lx] = L"";
							if (mSubWeapon == enums::eWeapon::Wand)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"Wand";
											Objdata::GetMagicWand()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											mCheck1 = 1;
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							else if (mSubWeapon == enums::eWeapon::Twohand)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"TwoHand";
											Objdata::GetBelialSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											mCheck1 = 1;
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							else if (mSubWeapon == enums::eWeapon::Onehand)
							{
								UINT mCheck1 = 0;
								for (int y = 0;y < 3;y++)
								{
									for (int x = 0;x < 5;x++)
									{
										if (mInventory[y][x] == L"")
										{
											mInventory[y][x] = L"Sword";
											Objdata::GetSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
											mCheck1 = 1;
											break;
										}
									}
									if (mCheck1 == 1)
										break;
								}
							}
							mSubWeapon = enums::eWeapon::Gun;
							texture = Resources::Load<Texture>(mClickedName + L"Inventorybox", L"");
							ImageObject* inventoryweapon = mCanvas->Find(L"InventorySubWeapon");
							Transform* inventorytr = inventoryweapon->GetComponent<Transform>();
							inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
							inventorytr->SetScale(Math::Vector2<float>(57.f, 21.f));
							Objdata::SetSubWeapon(mSubWeapon);
						}
						Objdata::SetInventory(mInventory);
					}

					for (int y = 0;y < 3;y++)
					{
						for (int x = 0;x < 5;x++)
						{
							if ((cursorpos.x < 865.f + 88.f * x + 38.f && cursorpos.x > 865.f + 88.f * x - 38.f) &&
								(cursorpos.y < 390.f + 88.f * y + 38.f && cursorpos.y > 390.f + 88.f * y - 38.f))
							{
								mInventory[ly][lx] = L"";
								mInventory[y][x] = mClickedName;
							}
						}
					}



					Objdata::SetInventory(mInventory);

					if (Input::Getkey(eKeyCode::MouseLeftClick).state == eKeyState::NONE)
					{
						mClickedName = L"";
						mClicked = false;
					}
				}
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
			if (mActiveWeapon == enums::eWeapon::Onehand)
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
			else if (mActiveWeapon == enums::eWeapon::Wand)
			{
				mCurState = eAnimationState::Attack;
				mIsSwing = !mIsSwing;
				Objdata::SetSwing(mIsSwing);
				if (mSound != nullptr)
				{
					mSound->Stop(true);
				}
				mWandSound->Play(false);
			}
			else if (mActiveWeapon == enums::eWeapon::Twohand)
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
			else if (mActiveWeapon == enums::eWeapon::Gun)
			{
				mCurState = eAnimationState::Attack;
				if (mSound != nullptr)
				{
					mSound->Stop(true);
				}
				mGunSound->Play(false);
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

		if (Input::Getkey(eKeyCode::V).state == eKeyState::DOWN)
		{
			Inventory();
		}

		if (Input::Getkey(eKeyCode::Tap).state == eKeyState::DOWN)
		{
			Swap();
		}

		if (Input::Getkey(eKeyCode::Q).state == eKeyState::DOWN)
		{
			mCurState = eAnimationState::Skill;
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
			if (mActiveWeapon == enums::eWeapon::Onehand)
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
			else if (mActiveWeapon == enums::eWeapon::Wand)
			{
				mCurState = eAnimationState::Attack;
				mIsSwing = !mIsSwing;
				Objdata::SetSwing(mIsSwing);
				if (mSound != nullptr)
				{
					mSound->Stop(true);
				}
				mWandSound->Play(false);
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
			if (mActiveWeapon == enums::eWeapon::Onehand)
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
			else if (mActiveWeapon == enums::eWeapon::Wand)
			{
				mCurState = eAnimationState::Attack;
				mIsSwing = !mIsSwing;
				Objdata::SetSwing(mIsSwing);
				if (mSound != nullptr)
				{
					mSound->Stop(true);
				}
				mWandSound->Play(false);
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
		if (mActiveWeapon == enums::eWeapon::Wand)
		{
			POINT pt = {};
			GetCursorPos(&pt);
			ScreenToClient(application.GetHWND(), &pt);
			Vector2<float> cursorpos;
			cursorpos.x = pt.x;
			cursorpos.y = pt.y;

			cursorpos = Camera::CaculatePos(-cursorpos);
			cursorpos = -cursorpos;
			Transform* playertr = GetComponent<Transform>();
			Bullet* bullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
			Animator* ani = bullet->AddComponent<Animator>();
			Texture* texture = Resources::Load<Texture>(L"StarBullet", L"..\\Resources\\Player\\Basic\\Attack\\LalaWand\\StarBullet\\StarBullet.bmp");
			Collider* col = bullet->AddComponent<Collider>();
			Transform* tr = bullet->GetComponent<Transform>();
			ani->CreateAnimation(L"StarBullet", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(14.f, 13.f), Math::Vector2<float>(0.f, 0.f), 4, 0.1f);
			ani->PlayAnimation(L"StarBullet", true);
			col->SetScale(Math::Vector2<float>(56.f, 52.f));
			tr->SetScale(Math::Vector2<float>(56.f, 52.f));
			tr->SetPos(playertr->Getpos());
			bullet->SetDeleteTime(10.f);
			bullet->SetDamage(10.f);
			bullet->SetSpeed(2.f);
			bullet->SetPlayer(true);
			bullet->SetStop(false);
			bullet->SetStar(true);
			float radian = Math::Radian(cursorpos, tr->Getpos());
			bullet->SetRadian(radian);
			bullet->setHoming(true);
			mCurState = eAnimationState::Idle;

			Effect* bulletFX = object::Instantiate<Effect>(enums::eLayerType::UI);
			texture = Resources::Load<Texture>(L"StarBulletFX", L"..\\Resources\\Player\\Basic\\Attack\\LalaWand\\StarBulletFX\\StarBulletFX.bmp");
			tr = bulletFX->GetComponent<Transform>();
			ani = bulletFX->AddComponent<Animator>();

			tr->SetPos(playertr->Getpos());
			tr->SetScale(Math::Vector2<float>(144.f, 140.f));

			ani->CreateAnimation(L"StarBulletFX", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(36.f, 35.f), Math::Vector2<float>(0.f, 0.f), 7, 0.1f);
			ani->PlayAnimation(L"StarBulletFX", false);
			mIsAttack = false;
		}
		if (mActiveWeapon == enums::eWeapon::Twohand)
		{
			mWeaponCollider->GetComponent<Collider>()->enabled(true);
			mIsAttack = true;
			mCheckTime = 0.f;
		}
		if (mActiveWeapon == enums::eWeapon::Gun)
		{
			POINT pt = {};
			GetCursorPos(&pt);
			ScreenToClient(application.GetHWND(), &pt);
			Vector2<float> cursorpos;
			cursorpos.x = pt.x;
			cursorpos.y = pt.y;

			cursorpos = Camera::CaculatePos(-cursorpos);
			cursorpos = -cursorpos;
			Transform* playertr = GetComponent<Transform>();
			Bullet* bullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
			SpriteRenderer* sr = bullet->AddComponent<SpriteRenderer>();
			Texture* texture = Resources::Load<Texture>(L"RevolverBullet", L"..\\Resources\\Player\\Basic\\Attack\\Gun\\Bullet02.png");
			Collider* col = bullet->AddComponent<Collider>();
			Transform* tr = bullet->GetComponent<Transform>();
			sr->SetImg(texture);
			col->SetScale(Math::Vector2<float>(20.f, 36.f));
			tr->SetScale(Math::Vector2<float>(20.f, 36.f));
			tr->SetPos(playertr->Getpos());
			bullet->SetDeleteTime(10.f);
			bullet->SetDamage(10.f);
			bullet->SetSpeed(3.f);
			bullet->SetPlayer(true);
			bullet->SetStop(false);
			bullet->SetPass(false);
			float radian = Math::Radian(cursorpos, tr->Getpos());
			bullet->SetRadian(radian);
			texture->SetDegree(90 + radian * 180.f / 3.14f);
			mCurState = eAnimationState::Idle;
			mIsAttack = false;
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

	void Player::Inventory()
	{
		ImageObject* imageobjectBase = mCanvas->Find(L"InventoryBase");
		SpriteRenderer* Basesr = imageobjectBase->GetComponent<SpriteRenderer>();

		ImageObject* imageobjectBox = mCanvas->Find(L"InventoryBox0");
		SpriteRenderer* Boxsr = imageobjectBox->GetComponent<SpriteRenderer>();

		ImageObject* imageobjectweapon = mCanvas->Find(L"InventoryWeapon");
		SpriteRenderer* weaponsr = imageobjectweapon->GetComponent<SpriteRenderer>();

		ImageObject* imageobjectSubweapon = mCanvas->Find(L"InventorySubWeapon");
		SpriteRenderer* weaponsubsr = imageobjectSubweapon->GetComponent<SpriteRenderer>();
		if (mOpeninventory)
		{
			mOpeninventorysound->Play(false);
			Basesr->GetImg()->Enabled(false);
			Boxsr->GetImg()->Enabled(false);
			if (weaponsr->GetImg() != nullptr)
			{
				weaponsr->GetImg()->Enabled(false);
			}
			if (weaponsubsr->GetImg() != nullptr)
			{
				weaponsubsr->GetImg()->Enabled(false);
			}
			mOpeninventory = false;

			for (size_t y = 0; y < 3; y++)
			{
				for (size_t x = 0; x < 5; x++)
				{
					if (mInventory[y][x] != L"")
					{
						Texture* texture = mCanvas->Find(L"InventoryItem" + std::to_wstring(y * 5 + x))->GetComponent<SpriteRenderer>()->GetImg();
						texture->Enabled(false);
					}
				}
			}
		}
		else
		{
			mOpeninventorysound->Play(false);
			Basesr->GetImg()->Enabled(true);
			Boxsr->GetImg()->Enabled(true);
			if (weaponsr->GetImg() != nullptr)
			{
				weaponsr->GetImg()->Enabled(true);
			}
			if (weaponsubsr->GetImg() != nullptr)
			{
				weaponsubsr->GetImg()->Enabled(true);
			}
			mOpeninventory = true;

			for (size_t y = 0; y < 3; y++)
			{
				for (size_t x = 0; x < 5; x++)
				{
					if (mInventory[y][x] != L"")
					{
						Texture* texture = mCanvas->Find(L"InventoryItem" + std::to_wstring(y * 5 + x))->GetComponent<SpriteRenderer>()->GetImg();
						texture->Enabled(true);
					}
				}
			}
		}
		mCurState = eAnimationState::Idle;
	}

	void Player::Swap()
	{
		mSwapSound->Play(false);
		enums::eWeapon temp = mActiveWeapon;
		mActiveWeapon = mSubWeapon;
		mSubWeapon = temp;
		Objdata::SetActiveWeapon(mActiveWeapon);
		Objdata::SetSubWeapon(mSubWeapon);

		bool IsExist = false;

		Scene* mCurScene = SceneManager::GetCurScene();

		if (mActiveWeapon == enums::eWeapon::Onehand)
		{
			Objdata::GetSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
			mWeapon = Objdata::GetSword();
			mWeaponCollider = Objdata::GetSwordCollider();

			for (GameObject* obj : mCurScene->GetLayer(enums::eLayerType::UI).GetObjects())
			{
				if (obj == Objdata::GetSword())
				{
					IsExist = true;
					break;
				}
			}

			if (!IsExist)
			{
				mCurScene->SetLayer(enums::eLayerType::UI, Objdata::GetSword());
				mCurScene->SetLayer(enums::eLayerType::Sword, Objdata::GetSwordCollider());
			}

			if (mSubWeapon == enums::eWeapon::Twohand)
			{
				Objdata::GetBelialSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
			}
			else if(mSubWeapon == enums::eWeapon::Wand)
			{
				Objdata::GetMagicWand()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
			}
			else if (mSubWeapon == enums::eWeapon::Gun)
			{
				Objdata::GetGun()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
			}
		}
		else if (mActiveWeapon == enums::eWeapon::Twohand)
		{
			Objdata::GetBelialSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
			mWeapon = Objdata::GetBelialSword();
			mWeaponCollider = Objdata::GetBelialSwordCollider();

			for (GameObject* obj : mCurScene->GetLayer(enums::eLayerType::UI).GetObjects())
			{
				if (obj == Objdata::GetBelialSword())
				{
					IsExist = true;
					break;
				}
			}

			if (!IsExist)
			{
				mCurScene->SetLayer(enums::eLayerType::UI, Objdata::GetBelialSword());
				mCurScene->SetLayer(enums::eLayerType::Sword, Objdata::GetBelialSwordCollider());
			}

			if (mSubWeapon == enums::eWeapon::Onehand)
			{
				Objdata::GetSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
			}
			else if (mSubWeapon == enums::eWeapon::Wand)
			{
				Objdata::GetMagicWand()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
			}
			else if (mSubWeapon == enums::eWeapon::Gun)
			{
				Objdata::GetGun()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
			}
		}
		else if (mActiveWeapon == enums::eWeapon::Wand)
		{
			Objdata::GetMagicWand()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
			mWeapon = Objdata::GetMagicWand();
			mWeaponCollider = nullptr;

			for (GameObject* obj : mCurScene->GetLayer(enums::eLayerType::UI).GetObjects())
			{
				if (obj == Objdata::GetMagicWand())
				{
					IsExist = true;
					break;
				}
			}

			if (!IsExist)
			{
				mCurScene->SetLayer(enums::eLayerType::UI, Objdata::GetMagicWand());
			}

			if (mSubWeapon == enums::eWeapon::Twohand)
			{
				Objdata::GetBelialSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
			}
			else if (mSubWeapon == enums::eWeapon::Onehand)
			{
				Objdata::GetSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
			}
			else if (mSubWeapon == enums::eWeapon::Gun)
			{
				Objdata::GetGun()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
			}
		}
		else if (mActiveWeapon == enums::eWeapon::Gun)
		{
			Objdata::GetGun()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
			mWeapon = Objdata::GetGun();
			mWeaponCollider = nullptr;

			for (GameObject* obj : mCurScene->GetLayer(enums::eLayerType::UI).GetObjects())
			{
				if (obj == Objdata::GetGun())
				{
					IsExist = true;
					break;
				}
			}

			if (!IsExist)
			{
				mCurScene->SetLayer(enums::eLayerType::UI, Objdata::GetGun());
			}

			if (mSubWeapon == enums::eWeapon::Twohand)
			{
				Objdata::GetBelialSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
			}
			else if (mSubWeapon == enums::eWeapon::Wand)
			{
				Objdata::GetMagicWand()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
			}
			else if (mSubWeapon == enums::eWeapon::Onehand)
			{
				Objdata::GetSword()->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
			}
		}
		else
		{
			mWeapon = nullptr;
			mWeaponCollider = nullptr;
		}
		Objdata::SetWeapon(mWeapon);
		Objdata::SetWeaponCollider(mWeaponCollider);
	}

	void Player::Skill()
	{
		if (mActiveWeapon == enums::eWeapon::Wand)
		{
			mWandSkillSound->Play(false);
			POINT pt = {};
			GetCursorPos(&pt);
			ScreenToClient(application.GetHWND(), &pt);
			Vector2<float> cursorpos;
			cursorpos.x = pt.x;
			cursorpos.y = pt.y;

			cursorpos = Camera::CaculatePos(-cursorpos);
			cursorpos = -cursorpos;
			Transform* playertr = GetComponent<Transform>();
			Animator* ani = nullptr;
			Transform* tr = nullptr;
			Collider* col = nullptr;
			Texture* texture = nullptr;
			for (int i = -4;i < 4;i++)
			{
				Bullet* bullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
				ani = bullet->AddComponent<Animator>();
				texture = Resources::Load<Texture>(L"StarBullet", L"..\\Resources\\Player\\Basic\\Attack\\LalaWand\\StarBullet\\StarBullet.bmp");
				col = bullet->AddComponent<Collider>();
				tr = bullet->GetComponent<Transform>();
				ani->CreateAnimation(L"StarBullet", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(14.f, 13.f), Math::Vector2<float>(0.f, 0.f), 4, 0.1f);
				ani->PlayAnimation(L"StarBullet", true);
				col->SetScale(Math::Vector2<float>(56.f, 52.f));
				tr->SetScale(Math::Vector2<float>(56.f, 52.f));
				tr->SetPos(playertr->Getpos());
				bullet->SetDeleteTime(10.f);
				bullet->SetDamage(10.f);
				bullet->SetSpeed(2.f);
				bullet->SetPlayer(true);
				bullet->SetStop(false);
				float radian = Math::Radian(cursorpos, tr->Getpos());
				bullet->SetRadian(radian + 0.261 * i);
				bullet->setHoming(true);
				bullet->SetStar(true);
			}

			// Effect
			Effect* bulletFX = object::Instantiate<Effect>(enums::eLayerType::UI);
			texture = Resources::Load<Texture>(L"StarBulletFX", L"..\\Resources\\Player\\Basic\\Attack\\LalaWand\\StarBulletFX\\StarBulletFX.bmp");
			tr = bulletFX->GetComponent<Transform>();
			ani = bulletFX->AddComponent<Animator>();

			tr->SetPos(playertr->Getpos());
			tr->SetScale(Math::Vector2<float>(144.f, 140.f));

			ani->CreateAnimation(L"StarBulletFX", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(36.f, 35.f), Math::Vector2<float>(0.f, 0.f), 7, 0.1f);
			ani->PlayAnimation(L"StarBulletFX", false);
		}
		else if (mActiveWeapon == enums::eWeapon::Twohand)
		{
			mTwoHandSkillSound->Play(false);

			POINT pt = {};
			GetCursorPos(&pt);
			ScreenToClient(application.GetHWND(), &pt);
			Vector2<float> cursorpos;
			cursorpos.x = pt.x;
			cursorpos.y = pt.y;

			cursorpos = Camera::CaculatePos(-cursorpos);
			cursorpos = -cursorpos;

			Transform* tr = GetComponent<Transform>();
			Math::Vector2<float> pos = tr->Getpos();
			float radian = Math::Radian(pos, cursorpos);

			Math::Vector2<float> startpos = pos;
			startpos.x += 200.f * cosf(radian);
			startpos.y += 200.f * sinf(radian);

			Effect* handeffect = object::Instantiate<Effect>(enums::eLayerType::UI);
			tr = handeffect->GetComponent<Transform>();
			tr->SetPos(startpos);
			tr->SetScale(Math::Vector2<float>(156.f, 160.f));
			Texture* texture = Resources::Load<Texture>(L"TwoHandSkillHand", L"..\\Resources\\Player\\Basic\\Attack\\TwoHand\\Skill\\Hand\\SkeletonKingSwordHand.png");
			texture->SetDegree(radian * 180.f / 3.14f + 270.f);
			Animator* ani = handeffect->AddComponent<Animator>();
			ani->CreateAnimation(L"TwoHandSkillHand", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(39.f, 40.f), Math::Vector2<float>(0.f, 0.f), 13, 0.1f);
			ani->PlayAnimation(L"TwoHandSkillHand", false);

			Bullet* bullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
			ani = bullet->AddComponent<Animator>();
			texture = Resources::Load<Texture>(L"SkellBossWeaponHead", L"..\\Resources\\Player\\Basic\\Attack\\TwoHand\\Skill\\Laser\\SkellBossWeaponHead.png");
			texture->SetDegree(radian * 180.f / 3.14f + 270.f);
			Collider* col = bullet->AddComponent<Collider>();
			tr = bullet->GetComponent<Transform>();
			ani->CreateAnimation(L"SkellBossWeaponHead", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(55.f, 32.f), Math::Vector2<float>(0.f, 0.f), 7, 0.1f);
			ani->PlayAnimation(L"SkellBossWeaponHead", false);
			col->SetScale(Math::Vector2<float>(220.f, 128.f));
			tr->SetScale(Math::Vector2<float>(220.f, 128.f));
			tr->SetPos(startpos);
			bullet->SetDeleteTime(0.7f);
			bullet->SetDamage(10.f);
			bullet->SetStop(true);
			bullet->SetPlayer(true);
			bullet->SetLaser(true);

			for (int i = 0;i < 8;i++)
			{
				Bullet* bullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
				ani = bullet->AddComponent<Animator>();
				texture = Resources::Load<Texture>(L"SkellBossWeaponBody" + std::to_wstring(i), L"..\\Resources\\Player\\Basic\\Attack\\TwoHand\\Skill\\Laser\\SkellBossWeaponLaserBody.png");
				texture->SetDegree(radian * 180.f / 3.14f + 270.f);
				Collider* col = bullet->AddComponent<Collider>();
				tr = bullet->GetComponent<Transform>();
				ani->CreateAnimation(L"SkellBossWeaponBody", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(55.f, 32.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
				ani->PlayAnimation(L"SkellBossWeaponBody", false);
				col->SetScale(Math::Vector2<float>(120.f, 120.f));
				tr->SetScale(Math::Vector2<float>(220.f, 128.f));
				startpos.x -= 120.f * cosf(radian);
				startpos.y -= 120.f * sinf(radian);
				tr->SetPos(startpos);
				bullet->SetPlayer(true);
				bullet->SetDeleteTime(0.7f);
				bullet->SetDamage(10.f);
				bullet->SetStop(true);
				bullet->SetLaser(true);
			}
		}
		mCurState = eAnimationState::Idle;
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