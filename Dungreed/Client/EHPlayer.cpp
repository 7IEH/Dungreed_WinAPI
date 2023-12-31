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
#include "EHCollisionManager.h"

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
		, mCurDash(0)
		, mMaxDash(3)
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

		CollisionManager::CollisionLayerCheck(enums::eLayerType::Sword, enums::eLayerType::Bullet,true);

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
		GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 75.f));
		GetComponent<Collider>()->SetOffset(Math::Vector2<float>(0.f, 28.5f));
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

		texture = Resources::Load<Texture>(L"DashBack", L"..\\Resources\\UI\\DashCountBack.bmp");
		PlayerUICanvas->AddImageObject(L"DashBack", texture, false, Math::Vector2<float>(75.f, 97.f), Math::Vector2<float>(116.f, 16.f));

		texture = Resources::Load<Texture>(L"Dash", L"..\\Resources\\UI\\Dash.bmp");
		PlayerUICanvas->AddImageObject(L"Dash", texture, false, Math::Vector2<float>(75.f, 97.f), Math::Vector2<float>(116.f, 16.f));

		texture = Resources::Load<Texture>(L"DashBase", L"..\\Resources\\UI\\DashCountBase.bmp");
		PlayerUICanvas->AddImageObject(L"DashBase", texture, false, Math::Vector2<float>(75.f, 97.f), Math::Vector2<float>(132.f, 32.f));

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

		// Dust
		GameObject* effect = object::Instantiate<GameObject>(enums::eLayerType::UI);
		Transform* effecttr = effect->GetComponent<Transform>();
		Animator* effectani = effect->AddComponent<Animator>();
		effecttr->SetScale(Math::Vector2<float>(64.f, 64.f));
		texture = Resources::Load<Texture>(L"workrightdust", L"..\\Resources\\Player\\Basic\\Rightdust\\Dust.bmp");
		effectani->CreateAnimation(L"rightdust", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(16.f, 16.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		texture = Resources::Load<Texture>(L"workleftdust", L"..\\Resources\\Player\\Basic\\Leftdust\\Dust.bmp");
		effectani->CreateAnimation(L"leftdust", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(16.f, 16.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		texture = Resources::Load<Texture>(L"worktrans", L"..\\Resources\\Player\\Basic\\Trans.png");
		effectani->CreateAnimation(L"worktrans", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(16.f, 16.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		//effectani->PlayAnimation(L"worktrans", false);
		mDust = effect;

		// Inventory
		texture = Resources::Load<Texture>(L"InventoryBase", L"..\\Resources\\UI\\InventoryBase.png");
		texture->Enabled(false);
		PlayerUICanvas->AddImageObject(L"InventoryBase", texture, false, Math::Vector2<float>(1034.f, 360.f), Math::Vector2<float>(492.f, 720.f),Math::Vector2<float>(0.f,0.f),1.0f,true);

		PlayerUICanvas->AddImageObject(L"InventoryWeapon", nullptr, false, Math::Vector2<float>(890.f, 165.f), Math::Vector2<float>(57.f, 21.f), Math::Vector2<float>(0.f, 0.f), 1.0f, true);
		PlayerUICanvas->AddImageObject(L"InventorySubWeapon", nullptr, false, Math::Vector2<float>(1105.f, 165.f), Math::Vector2<float>(57.f, 21.f), Math::Vector2<float>(0.f, 0.f), 1.0f, true);

		texture = Resources::Load<Texture>(L"InventoryBox", L"..\\Resources\\UI\\InventoryBox.png");
		texture->Enabled(false);
		for (size_t y = 0; y < 3; y++)
		{
			for (size_t x = 0; x < 5; x++)
			{
				PlayerUICanvas->AddImageObject(L"InventoryBox" + std::to_wstring(y * 5 + x), texture, false, Math::Vector2<float>(865.f + 88.f * x, 390.f + 88.f * y), Math::Vector2<float>(76.f, 76.f), Math::Vector2<float>(0.f, 0.f), 1.0f, true);
				PlayerUICanvas->AddImageObject(L"InventoryItem" + std::to_wstring(y * 5 + x), nullptr, false, Math::Vector2<float>(865.f + 88.f * x, 390.f + 88.f * y), Math::Vector2<float>(76.f, 76.f), Math::Vector2<float>(0.f, 0.f), 1.0f, true);
			}
		}
		texture = Resources::Load<Texture>(L"InventoryBox_Selected", L"..\\Resources\\UI\\InventoryBox_Selected.png");
		
		texture = Resources::Load<Texture>(L"iteminfo1", L"..\\Resources\\UI\\ItemFont\\ItemEquip.bmp");
		texture->Enabled(false);
		PlayerUICanvas->AddImageObject(L"iteminfo1", texture, false, Math::Vector2<float>(0.f,0.f), Math::Vector2<float>(330.f, 110.f), Math::Vector2<float>(0.f, 0.f), 0.5f, true);
		PlayerUICanvas->AddImageObject(L"iteminfo2", nullptr, false, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(0.f, 0.f), 1.0f, true);
		PlayerUICanvas->AddImageObject(L"iteminfo3", nullptr, false, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(0.f, 0.f), 1.0f, true);
		PlayerUICanvas->AddImageObject(L"iteminfo4", nullptr, false, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(0.f, 0.f), 1.0f, true);


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

		UINT curten = mCurHp / 10;
		UINT curone = mCurHp % 10;

		UINT maxten = mMaxHP / 10;
		UINT maxone = mMaxHP % 10;

		Objdata::SetGold(1000);

		GameObject* ten1 = object::Instantiate<GameObject>(enums::eLayerType::UI);
		Transform* tr = ten1->GetComponent<Transform>();
		Animator* ani = ten1->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"numberfont", L"..\\Resources\\UI\\NumberFont.bmp");
		tr->SetPos(Math::Vector2<float>(150.f, 40.f));
		tr->SetScale(Math::Vector2<float>(21.f, 33.f));
		for (int i = 0;i < 9;i++)
		{
			ani->CreateAnimation(L"NUM" + std::to_wstring(i), texture, Math::Vector2<float>(i * 7.f, 0.f), Math::Vector2<float>(7.f, 11.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		}
		ani->PlayAnimation(L"NUM"+std::to_wstring(curten), false);
		ani->SetAffectedCamera(false);
		mCurhpImage1 = ten1;

		GameObject* one1 = object::Instantiate<GameObject>(enums::eLayerType::UI);
		tr = one1->GetComponent<Transform>();
		ani = one1->AddComponent<Animator>();
		tr->SetPos(Math::Vector2<float>(171.f, 40.f));
		tr->SetScale(Math::Vector2<float>(21.f, 33.f));
		for (int i = 0;i < 9;i++)
		{
			ani->CreateAnimation(L"NUM" + std::to_wstring(i), texture, Math::Vector2<float>(i * 7.f, 0.f), Math::Vector2<float>(7.f, 11.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		}
		ani->PlayAnimation(L"NUM" + std::to_wstring(curten), false);
		ani->SetAffectedCamera(false);
		mCurhpImage2 = one1;

		GameObject* slash = object::Instantiate<GameObject>(enums::eLayerType::UI);
		tr = slash->GetComponent<Transform>();
		ani = slash->AddComponent<Animator>();
		tr->SetPos(Math::Vector2<float>(190.5f, 40.f));
		tr->SetScale(Math::Vector2<float>(18.f, 30.f));
		Texture* texture2 = Resources::Load<Texture>(L"slash", L"..\\Resources\\UI\\slash.bmp");
		ani->CreateAnimation(L"slash", texture2, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(6.f, 10.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		ani->PlayAnimation(L"slash", false);
		ani->SetAffectedCamera(false);


		GameObject* ten2 = object::Instantiate<GameObject>(enums::eLayerType::UI);
		tr = ten2->GetComponent<Transform>();
		ani = ten2->AddComponent<Animator>();
		tr->SetPos(Math::Vector2<float>(210.f, 40.f));
		tr->SetScale(Math::Vector2<float>(21.f, 33.f));
		for (int i = 0;i < 9;i++)
		{
			ani->CreateAnimation(L"NUM" + std::to_wstring(i), texture, Math::Vector2<float>(i * 7.f, 0.f), Math::Vector2<float>(7.f, 11.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		}
		ani->PlayAnimation(L"NUM" + std::to_wstring(curten), false);
		ani->SetAffectedCamera(false);
		mMaxhpImage1 = ten2;

		GameObject* one2 = object::Instantiate<GameObject>(enums::eLayerType::UI);
		tr = one2->GetComponent<Transform>();
		ani = one2->AddComponent<Animator>();
		tr->SetPos(Math::Vector2<float>(231.f, 40.f));
		tr->SetScale(Math::Vector2<float>(21.f, 33.f));
		for (int i = 0;i < 9;i++)
		{
			ani->CreateAnimation(L"NUM" + std::to_wstring(i), texture, Math::Vector2<float>(i * 7.f, 0.f), Math::Vector2<float>(7.f, 11.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		}
		ani->PlayAnimation(L"NUM" + std::to_wstring(curten), false);
		ani->SetAffectedCamera(false);
		mMaxhpImage2 = one2;

		UINT thousand = mGold / 1000;
		UINT hundred = (mGold- thousand *1000) / 100;
		UINT ten = (mGold - thousand * 1000 + hundred*100) / 10;
		UINT one4 = mGold % 10;

		GameObject* goldt = object::Instantiate<GameObject>(enums::eLayerType::UI);
		tr = goldt->GetComponent<Transform>();
		ani = goldt->AddComponent<Animator>();
		tr->SetPos(Math::Vector2<float>(75.f, 655.f));
		tr->SetScale(Math::Vector2<float>(14.f, 22.f));
		for (int i = 0;i < 9;i++)
		{
			ani->CreateAnimation(L"NUM" + std::to_wstring(i), texture, Math::Vector2<float>(i * 7.f, 0.f), Math::Vector2<float>(7.f, 11.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		}
		ani->PlayAnimation(L"NUM" + std::to_wstring(thousand), false);
		ani->SetAffectedCamera(false);
		mGoldt = goldt;

		GameObject* goldh = object::Instantiate<GameObject>(enums::eLayerType::UI);
		tr = goldh->GetComponent<Transform>();
		ani = goldh->AddComponent<Animator>();
		tr->SetPos(Math::Vector2<float>(89.f, 655.f));
		tr->SetScale(Math::Vector2<float>(14.f, 22.f));
		for (int i = 0;i < 9;i++)
		{
			ani->CreateAnimation(L"NUM" + std::to_wstring(i), texture, Math::Vector2<float>(i * 7.f, 0.f), Math::Vector2<float>(7.f, 11.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		}
		ani->PlayAnimation(L"NUM" + std::to_wstring(hundred), false);
		ani->SetAffectedCamera(false);
		mGoldh = goldh;

		GameObject* goldten = object::Instantiate<GameObject>(enums::eLayerType::UI);
		tr = goldten->GetComponent<Transform>();
		ani = goldten->AddComponent<Animator>();
		tr->SetPos(Math::Vector2<float>(103.f, 655.f));
		tr->SetScale(Math::Vector2<float>(14.f, 22.f));
		for (int i = 0;i < 9;i++)
		{
			ani->CreateAnimation(L"NUM" + std::to_wstring(i), texture, Math::Vector2<float>(i * 7.f, 0.f), Math::Vector2<float>(7.f, 11.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		}
		ani->PlayAnimation(L"NUM" + std::to_wstring(ten), false);
		ani->SetAffectedCamera(false);
		mGoldten = goldten;

		GameObject* goldone = object::Instantiate<GameObject>(enums::eLayerType::UI);
		tr = goldone->GetComponent<Transform>();
		ani = goldone->AddComponent<Animator>();
		tr->SetPos(Math::Vector2<float>(117.f, 655.f));
		tr->SetScale(Math::Vector2<float>(14.f, 22.f));
		for (int i = 0;i < 9;i++)
		{
			ani->CreateAnimation(L"NUM" + std::to_wstring(i), texture, Math::Vector2<float>(i * 7.f, 0.f), Math::Vector2<float>(7.f, 11.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		}
		ani->PlayAnimation(L"NUM" + std::to_wstring(one4), false);
		ani->SetAffectedCamera(false);
		mGoldone = goldone;
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
		mCurDash = Objdata::GetDash();

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

		mDashTime += Time::GetDeltaTime();
		if (1.f < mDashTime)
		{
			if (mCurDash <= mMaxDash && mCurDash > 0)
			{
				Objdata::SetDash(Objdata::GetDash() - 1);
			}
			mDashTime = 0.f;
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

		ImageObject* dash = mCanvas->Find(L"Dash");
		tr = dash->GetComponent<Transform>();
		tr->SetPos(Math::Vector2<float>(75.f - ((116.f - 116.f * ((float)(mMaxDash - mCurDash) / mMaxDash)) / 2.f), tr->Getpos().y));
		tr->SetScale(Math::Vector2<float>(116.f * ((float)(mMaxDash - mCurDash) / mMaxDash), tr->GetScale().y));


		UINT curten = mCurHp / 10;
		UINT curone = mCurHp % 10;

		UINT maxten = mMaxHP / 10;
		UINT maxone = mMaxHP % 10;

		mCurhpImage1->GetComponent<Animator>()->PlayAnimation(L"NUM" + std::to_wstring(curten), false);
		mCurhpImage2->GetComponent<Animator>()->PlayAnimation(L"NUM" + std::to_wstring(curone), false);
		mMaxhpImage1->GetComponent<Animator>()->PlayAnimation(L"NUM" + std::to_wstring(maxten), false);
		mMaxhpImage2->GetComponent<Animator>()->PlayAnimation(L"NUM" + std::to_wstring(maxone), false);

		UINT thousand = mGold / 1000;
		UINT hundred = (mGold - thousand * 1000) / 100;
		UINT ten = (mGold - thousand * 1000 + hundred * 100) / 10;
		UINT one4 = mGold % 10;

		mGoldt->GetComponent<Animator>()->PlayAnimation(L"NUM" + std::to_wstring(thousand), false);
		mGoldh->GetComponent<Animator>()->PlayAnimation(L"NUM" + std::to_wstring(hundred), false);
		mGoldten->GetComponent<Animator>()->PlayAnimation(L"NUM" + std::to_wstring(ten), false);
		mGoldone->GetComponent<Animator>()->PlayAnimation(L"NUM" + std::to_wstring(one4), false);

		Playerlogic();
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
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
			inventoryweapon->GetComponent<Transform>()->SetScale(Math::Vector2<float>(76.f, 28.f));

			texture = Resources::Load<Texture>(L"Swordslot", L"..\\Resources\\Player\\Basic\\Attack\\ShortSword\\ShortSword.png");
			mCanvas->Find(L"Swordslot")->GetComponent<SpriteRenderer>()->SetImg(texture);
			mCanvas->Find(L"Swordslot")->GetComponent<Transform>()->SetScale(Math::Vector2<float>(76.f, 28.f));

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
			inventoryweapon->GetComponent<Transform>()->SetScale(Math::Vector2<float>(52.f, 52.f));

			texture = Resources::Load<Texture>(L"Wandslot", L"..\\Resources\\Player\\Basic\\Attack\\LalaWand\\Lala'sMagicWand.png");
			mCanvas->Find(L"Swordslot")->GetComponent<SpriteRenderer>()->SetImg(texture);
			mCanvas->Find(L"Swordslot")->GetComponent<Transform>()->SetScale(Math::Vector2<float>(52.f, 52.f));

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
			inventoryweapon->GetComponent<Transform>()->SetScale(Math::Vector2<float>(64.f, 36.f));

			texture = Resources::Load<Texture>(L"Gunslot", L"..\\Resources\\Player\\Basic\\Attack\\Gun\\Right\\Revolver2.png");
			mCanvas->Find(L"Swordslot")->GetComponent<SpriteRenderer>()->SetImg(texture);
			mCanvas->Find(L"Swordslot")->GetComponent<Transform>()->SetScale(Math::Vector2<float>(64.f, 36.f));

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
			inventoryweapon->GetComponent<Transform>()->SetScale(Math::Vector2<float>(68.f, 144.f));

			texture = Resources::Load<Texture>(L"TwoHandslot", L"..\\Resources\\Player\\Basic\\Attack\\TwoHand\\SkeletonKingJewelSword.png");
			mCanvas->Find(L"Swordslot")->GetComponent<SpriteRenderer>()->SetImg(texture);
			mCanvas->Find(L"Swordslot")->GetComponent<Transform>()->SetScale(Math::Vector2<float>(68.f, 144.f));

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
			inventoryweapon->GetComponent<Transform>()->SetScale(Math::Vector2<float>(76.f, 28.f));
		}
		else if (mSubWeapon == enums::eWeapon::Wand)
		{
			Texture* texture = Resources::Load<Texture>(L"WandWeaponbox", L"..\\Resources\\Player\\Basic\\Attack\\LalaWand\\Lala'sMagicWand.png");
			ImageObject* inventoryweapon = mCanvas->Find(L"InventorySubWeapon");
			inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
			inventoryweapon->GetComponent<Transform>()->SetScale(Math::Vector2<float>(52.f, 52.f));
		}
		else if (mSubWeapon == enums::eWeapon::Gun)
		{
			Texture* texture = Resources::Load<Texture>(L"GunWeaponbox", L"..\\Resources\\Player\\Basic\\Attack\\Gun\\Right\\Revolver2.png");
			ImageObject* inventoryweapon = mCanvas->Find(L"InventorySubWeapon");
			inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
			inventoryweapon->GetComponent<Transform>()->SetScale(Math::Vector2<float>(64.f, 36.f));
		}
		else if (mSubWeapon == enums::eWeapon::Twohand)
		{
			Texture* texture = Resources::Load<Texture>(L"TwoHandWeaponbox", L"..\\Resources\\Player\\Basic\\Attack\\TwoHand\\SkeletonKingJewelSword.png");
			ImageObject* inventoryweapon = mCanvas->Find(L"InventorySubWeapon");
			inventoryweapon->GetComponent<SpriteRenderer>()->SetImg(texture);
			inventoryweapon->GetComponent<Transform>()->SetScale(Math::Vector2<float>(68.f, 144.f));
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
				if (mInventory[dy][dx] == L"Sword")
				{
					ImageObject* info1 = mCanvas->Find(L"iteminfo1");
					if (info1->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
					{
						if (mInventory1 == 0)
							info1->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
						else
							info1->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
					}
					ImageObject* info2 = mCanvas->Find(L"iteminfo2");
					if (info2->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
					{
						if (mInventory1 == 0)
							info2->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
						else
							info2->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
					}
					ImageObject* info3 = mCanvas->Find(L"iteminfo3");
					if (info3->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
					{
						if (mInventory1 == 0)
							info3->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
						else
							info3->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
					}
					ImageObject* info4 = mCanvas->Find(L"iteminfo4");
					if (info4->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
					{
						if (mInventory1 == 0)
							info4->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
						else
							info4->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
					}

					info1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(cursorpos.x - 165.f, cursorpos.y - 55.f));
					Texture* temp4 = Resources::Load<Texture>(L"infosword", L"..\\Resources\\UI\\ItemFont\\shortswordalphabet.bmp");
					info2->GetComponent<SpriteRenderer>()->SetImg(temp4);
					info2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(cursorpos.x - 165.f, cursorpos.y - 80.f));
					info2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(56.f, 26.f));

					temp4 = Resources::Load<Texture>(L"infosworddamage", L"..\\Resources\\UI\\ItemFont\\Attack20.bmp");
					info3->GetComponent<SpriteRenderer>()->SetImg(temp4);
					info3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(cursorpos.x - 165.f, cursorpos.y - 55.f));
					info3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(46.f, 11.f));

					temp4 = Resources::Load<Texture>(L"infoswordimage", L"..\\Resources\\Player\\Basic\\Attack\\ShortSword\\ShortSword.png");
					info4->GetComponent<SpriteRenderer>()->SetImg(temp4);
					info4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(cursorpos.x - 250.f, cursorpos.y - 55.f));
					info4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(76.f, 28.f));
					mInventory1 = 0;
				}
				else if (mInventory[dy][dx] == L"Wand")
				{
					ImageObject* info1 = mCanvas->Find(L"iteminfo1");
					if (info1->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
					{
						if (mInventory1 == 1)
							info1->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
						else
							info1->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
					}
					ImageObject* info2 = mCanvas->Find(L"iteminfo2");
					if (info2->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
					{
						if (mInventory1 == 1)
							info2->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
						else
							info2->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
					}
					ImageObject* info3 = mCanvas->Find(L"iteminfo3");
					if (info3->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
					{
						if (mInventory1 == 1)
							info3->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
						else
							info3->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
					}
					ImageObject* info4 = mCanvas->Find(L"iteminfo4");
					if (info4->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
					{
						if (mInventory1 == 1)
							info4->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
						else
							info4->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
					}

					info1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(cursorpos.x - 165.f, cursorpos.y - 55.f));
					Texture* temp4 = Resources::Load<Texture>(L"infoWand", L"..\\Resources\\UI\\ItemFont\\Wandalphabet.bmp");
					info2->GetComponent<SpriteRenderer>()->SetImg(temp4);
					info2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(cursorpos.x - 165.f, cursorpos.y - 80.f));
					info2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(136.f, 22.f));

					temp4 = Resources::Load<Texture>(L"infoWanddamage", L"..\\Resources\\UI\\ItemFont\\Attack20.bmp");
					info3->GetComponent<SpriteRenderer>()->SetImg(temp4);
					info3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(cursorpos.x - 165.f, cursorpos.y - 55.f));
					info3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(46.f, 11.f));

					temp4 = Resources::Load<Texture>(L"infoWandimage", L"..\\Resources\\Player\\Basic\\Attack\\LalaWand\\Lala'sMagicWand.png");
					info4->GetComponent<SpriteRenderer>()->SetImg(temp4);
					info4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(cursorpos.x - 270.f, cursorpos.y - 55.f));
					info4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(52.f, 52.f));
					mInventory1 = 1;
				}
				else if (mInventory[dy][dx]==L"Gun")
				{
					ImageObject* info1 = mCanvas->Find(L"iteminfo1");
					if (info1->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
					{
						if (mInventory1 == 2)
							info1->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
						else
							info1->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
					}
					ImageObject* info2 = mCanvas->Find(L"iteminfo2");
					if (info2->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
					{
						if (mInventory1 == 2)
							info2->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
						else
							info2->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
					}
					ImageObject* info3 = mCanvas->Find(L"iteminfo3");
					if (info3->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
					{
						if (mInventory1 == 2)
							info3->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
						else
							info3->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
					}
					ImageObject* info4 = mCanvas->Find(L"iteminfo4");
					if (info4->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
					{
						if (mInventory1 == 2)
							info4->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
						else
							info4->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
					}

					info1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(cursorpos.x - 165.f, cursorpos.y - 55.f));
					Texture* temp4 = Resources::Load<Texture>(L"infogun", L"..\\Resources\\UI\\ItemFont\\Gunalphabet.bmp");
					info2->GetComponent<SpriteRenderer>()->SetImg(temp4);
					info2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(cursorpos.x - 165.f, cursorpos.y - 80.f));
					info2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(138.f, 24.f));

					temp4 = Resources::Load<Texture>(L"infogundamage", L"..\\Resources\\UI\\ItemFont\\Attack10.bmp");
					info3->GetComponent<SpriteRenderer>()->SetImg(temp4);
					info3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(cursorpos.x - 165.f, cursorpos.y - 55.f));
					info3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(46.f, 11.f));

					temp4 = Resources::Load<Texture>(L"infogunimage", L"..\\Resources\\Player\\Basic\\Attack\\Gun\\Right\\Revolver2.png");
					info4->GetComponent<SpriteRenderer>()->SetImg(temp4);
					info4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(cursorpos.x - 270.f, cursorpos.y - 55.f));
					info4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(64.f, 36.f));
					mInventory1 = 2;
				}
				else if (mInventory[dy][dx] == L"TwoHand")
				{
					ImageObject* info1 = mCanvas->Find(L"iteminfo1");
					if (info1->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
					{
						if (mInventory1 == 3)
							info1->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
						else
							info1->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
					}	
					ImageObject* info2 = mCanvas->Find(L"iteminfo2");
					if (info2->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
					{
						if (mInventory1 == 3)
							info2->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
						else
							info2->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
					}
					ImageObject* info3 = mCanvas->Find(L"iteminfo3");
					if (info3->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
					{
						if (mInventory1 == 3)
							info3->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
						else
							info3->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
					}
					ImageObject* info4 = mCanvas->Find(L"iteminfo4");
					if (info4->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
					{
						if (mInventory1 == 3)
							info4->GetComponent<SpriteRenderer>()->GetImg()->Enabled(true);
						else
							info4->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
					}


					info1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(cursorpos.x - 165.f, cursorpos.y - 55.f));
					Texture* temp4 = Resources::Load<Texture>(L"infotwohand", L"..\\Resources\\UI\\ItemFont\\twohandalphabet.bmp");
					info2->GetComponent<SpriteRenderer>()->SetImg(temp4);
					info2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(cursorpos.x - 165.f, cursorpos.y - 80.f));
					info2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(134.f, 24.f));

					temp4 = Resources::Load<Texture>(L"infotwohanddamage", L"..\\Resources\\UI\\ItemFont\\Attack20.bmp");
					info3->GetComponent<SpriteRenderer>()->SetImg(temp4);
					info3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(cursorpos.x - 165.f, cursorpos.y - 55.f));
					info3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(46.f, 11.f));

					temp4 = Resources::Load<Texture>(L"infotwohandimage", L"..\\Resources\\Player\\Basic\\Attack\\TwoHand\\SkeletonKingJewelSword.png");
					info4->GetComponent<SpriteRenderer>()->SetImg(temp4);
					info4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(cursorpos.x - 270.f, cursorpos.y - 55.f));
					info4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(68.f, 144.f));
					mInventory1 = 3;
				}
				else
				{
					ImageObject* info1 = mCanvas->Find(L"iteminfo1");
					if(info1->GetComponent<SpriteRenderer>()->GetImg()!=nullptr)
						info1->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
					ImageObject* info2 = mCanvas->Find(L"iteminfo2");
					if (info2->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
						info2->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
					ImageObject* info3 = mCanvas->Find(L"iteminfo3");
					if (info3->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
						info3->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
					ImageObject* info4 = mCanvas->Find(L"iteminfo4");
					if (info4->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
						info4->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
				}

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
			else
			{
				ImageObject* info1 = mCanvas->Find(L"iteminfo1");
				if (info1->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
					info1->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
				ImageObject* info2 = mCanvas->Find(L"iteminfo2");
				if (info2->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
					info2->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
				ImageObject* info3 = mCanvas->Find(L"iteminfo3");
				if (info3->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
					info3->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
				ImageObject* info4 = mCanvas->Find(L"iteminfo4");
				if (info4->GetComponent<SpriteRenderer>()->GetImg() != nullptr)
					info4->GetComponent<SpriteRenderer>()->GetImg()->Enabled(false);
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
		// Cursor
		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(application.GetHWND(), &pt);
		Vector2<float> cursorpos;
		cursorpos.x = pt.x;
		cursorpos.y = pt.y;

		cursorpos = Camera::CaculatePos(-cursorpos);
		cursorpos = -cursorpos;

		Transform* tr = GetComponent<Transform>();

		if (mIsRight && mIsJump)
			GetComponent<Animator>()->PlayAnimation(L"PlayerRightIdle", true);
		else if (!mIsRight && mIsJump)
			GetComponent<Animator>()->PlayAnimation(L"PlayerLeftIdle", true);
		else if (mIsRight && !mIsJump)
			GetComponent<Animator>()->PlayAnimation(L"PlayerRightJump", false);
		else if (!mIsRight && !mIsJump)
			GetComponent<Animator>()->PlayAnimation(L"PlayerLeftJump", false);

		mDust->GetComponent<Animator>()->PlayAnimation(L"worktrans", false);

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

				float radian2 = Math::Radian(tr->Getpos(), cursorpos);

				Effect* effect = object::Instantiate<Effect>(enums::eLayerType::UI);
				Transform* effecttr = effect->GetComponent<Transform>();
				Animator* effectani = effect->AddComponent<Animator>();
				effecttr->SetPos(Math::Vector2<float>(tr->Getpos().x - 60.f * cosf(radian2), tr->Getpos().y - 60.f * sinf(radian2)));
				effecttr->SetScale(Math::Vector2<float>(160.f,112.f));
				Texture* texture2 = Resources::Load<Texture>(L"swingfx", L"..\\Resources\\Player\\Basic\\Attack\\SwingFX.png");
				texture2->SetDegree(radian2 * (180.f / 3.14f) - 90.f);
				effectani->CreateAnimation(L"swingfx",texture2,Math::Vector2<float>(0.f,0.f), Math::Vector2<float>(40.f, 28.f), Math::Vector2<float>(0.f, 0.f),3,0.1f);
				effectani->PlayAnimation(L"swingfx",false);
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

				float radian2 = Math::Radian(tr->Getpos(), cursorpos);

				Effect* effect = object::Instantiate<Effect>(enums::eLayerType::UI);
				Transform* effecttr = effect->GetComponent<Transform>();
				Animator* effectani = effect->AddComponent<Animator>();
				effecttr->SetPos(Math::Vector2<float>(tr->Getpos().x - 60.f * cosf(radian2), tr->Getpos().y - 60.f * sinf(radian2)));
				effecttr->SetScale(Math::Vector2<float>(160.f, 112.f));
				Texture* texture2 = Resources::Load<Texture>(L"swingfx", L"..\\Resources\\Player\\Basic\\Attack\\SwingFX.png");
				texture2->SetDegree(radian2 * (180.f / 3.14f) - 90.f);
				effectani->CreateAnimation(L"swingfx", texture2, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(40.f, 28.f), Math::Vector2<float>(0.f, 0.f), 3, 0.1f);
				effectani->PlayAnimation(L"swingfx", false);
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
		if (Input::Getkey(eKeyCode::MouseRightClick).state == eKeyState::DOWN && mCurDash<mMaxDash)
		{
			Objdata::SetDash(mCurDash + 1);
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

		if (Input::Getkey(eKeyCode::O).state == eKeyState::DOWN)
		{
			Collider::SetRender(!Collider::GetRender());
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

		Transform* dusteffecttr = mDust->GetComponent<Transform>();
		Animator* dusteffectani = mDust->GetComponent<Animator>();

		if (mIsRight && !mIsJump)
			GetComponent<Animator>()->PlayAnimation(L"PlayerRightJump", false);
		else if (!mIsRight && !mIsJump)
			GetComponent<Animator>()->PlayAnimation(L"PlayerLeftJump", false);

		if (Input::Getkey(eKeyCode::A).state == eKeyState::PRESSED)
		{
			dusteffecttr->SetPos(Math::Vector2<float>(pos.x + 40.f, pos.y + 40.f));
			dusteffectani->PlayAnimation(L"leftdust", true);
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
			dusteffecttr->SetPos(Math::Vector2<float>(pos.x - 40.f, pos.y + 40.f));
			dusteffectani->PlayAnimation(L"rightdust", true);
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

				float radian2 = Math::Radian(tr->Getpos(), cursorpos);

				Effect* effect = object::Instantiate<Effect>(enums::eLayerType::UI);
				Transform* effecttr = effect->GetComponent<Transform>();
				Animator* effectani = effect->AddComponent<Animator>();
				effecttr->SetPos(Math::Vector2<float>(tr->Getpos().x - 60.f * cosf(radian2), tr->Getpos().y - 60.f * sinf(radian2)));
				effecttr->SetScale(Math::Vector2<float>(160.f, 112.f));
				Texture* texture2 = Resources::Load<Texture>(L"swingfx", L"..\\Resources\\Player\\Basic\\Attack\\SwingFX.png");
				texture2->SetDegree(radian2* (180.f / 3.14f) - 90.f);
				effectani->CreateAnimation(L"swingfx", texture2, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(40.f, 28.f), Math::Vector2<float>(0.f, 0.f), 3, 0.1f);
				effectani->PlayAnimation(L"swingfx", false);
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

				float radian2 = Math::Radian(tr->Getpos(), cursorpos);

				Effect* effect = object::Instantiate<Effect>(enums::eLayerType::UI);
				Transform* effecttr = effect->GetComponent<Transform>();
				Animator* effectani = effect->AddComponent<Animator>();
				effecttr->SetPos(Math::Vector2<float>(tr->Getpos().x - 60.f * cosf(radian2), tr->Getpos().y - 60.f * sinf(radian2)));
				effecttr->SetScale(Math::Vector2<float>(160.f, 112.f));
				Texture* texture2 = Resources::Load<Texture>(L"swingfx", L"..\\Resources\\Player\\Basic\\Attack\\SwingFX.png");
				texture2->SetDegree(radian2* (180.f / 3.14f) - 90.f);
				effectani->CreateAnimation(L"swingfx", texture2, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(40.f, 28.f), Math::Vector2<float>(0.f, 0.f), 3, 0.1f);
				effectani->PlayAnimation(L"swingfx", false);
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
		if (Input::Getkey(eKeyCode::MouseRightClick).state == eKeyState::DOWN && mCurDash<mMaxDash)
		{
			Objdata::SetDash(mCurDash + 1);
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
		Transform* tr = GetComponent<Transform>();
		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(application.GetHWND(), &pt);
		Vector2<float> cursorpos;
		cursorpos.x = pt.x;
		cursorpos.y = pt.y;

		cursorpos = Camera::CaculatePos(-cursorpos);
		cursorpos = -cursorpos;

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

				float radian2 = Math::Radian(tr->Getpos(), cursorpos);

				Effect* effect = object::Instantiate<Effect>(enums::eLayerType::UI);
				Transform* effecttr = effect->GetComponent<Transform>();
				Animator* effectani = effect->AddComponent<Animator>();
				effecttr->SetPos(Math::Vector2<float>(tr->Getpos().x - 60.f * cosf(radian2), tr->Getpos().y - 60.f * sinf(radian2)));
				effecttr->SetScale(Math::Vector2<float>(160.f, 112.f));
				Texture* texture2 = Resources::Load<Texture>(L"swingfx", L"..\\Resources\\Player\\Basic\\Attack\\SwingFX.png");
				texture2->SetDegree(radian2 * (180.f / 3.14f) - 90.f);
				effectani->CreateAnimation(L"swingfx", texture2, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(40.f, 28.f), Math::Vector2<float>(0.f, 0.f), 3, 0.1f);
				effectani->PlayAnimation(L"swingfx", false);
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

				float radian2 = Math::Radian(tr->Getpos(), cursorpos);

				Effect* effect = object::Instantiate<Effect>(enums::eLayerType::UI);
				Transform* effecttr = effect->GetComponent<Transform>();
				Animator* effectani = effect->AddComponent<Animator>();
				effecttr->SetPos(Math::Vector2<float>(tr->Getpos().x - 60.f * cosf(radian2), tr->Getpos().y - 60.f * sinf(radian2)));
				effecttr->SetScale(Math::Vector2<float>(160.f, 112.f));
				Texture* texture2 = Resources::Load<Texture>(L"swingfx", L"..\\Resources\\Player\\Basic\\Attack\\SwingFX.png");
				texture2->SetDegree(radian2 * (180.f / 3.14f) - 90.f);
				effectani->CreateAnimation(L"swingfx", texture2, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(40.f, 28.f), Math::Vector2<float>(0.f, 0.f), 3, 0.1f);
				effectani->PlayAnimation(L"swingfx", false);
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
			bullet->SetDeleteTime(5.f);
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

		Effect* dasheffect = object::Instantiate<Effect>(enums::eLayerType::Effect);
		Transform* effecttr = dasheffect->GetComponent<Transform>();
		Animator* effectani = dasheffect->AddComponent<Animator>();
		effecttr->SetPos(pos);
		effecttr->SetScale(Math::Vector2<float>(128.f, 128.f));
		Texture* texture = nullptr;
		if (mIsRight)
		{
			texture = Resources::Load<Texture>(L"PlayerRightJump", L"..\\Resources\\Player\\Basic\\Jump\\CharRightJump.bmp");
		}
		else
		{
			texture = Resources::Load<Texture>(L"PlayerLeftJump", L"..\\Resources\\Player\\Basic\\Jump\\CharLeftJump.bmp");
		}

		effectani->SetAlpha(0.5f);
		effectani->CreateAnimation(L"jump", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		effectani->PlayAnimation(L"jump", false);

		Math::Vector2<float> dir = cursurpos - pos;
		dir.normalized<float>();

		pos.x += dir.x * 1500.f * Time::GetDeltaTime();
		pos.y += dir.y * 1500.f * Time::GetDeltaTime();

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