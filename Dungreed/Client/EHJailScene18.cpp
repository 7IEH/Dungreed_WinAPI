#include "EHJailScene18.h"
#include "EHSceneManager.h"
#include "EHBackGround.h"
#include "EHResources.h"
#include "EHObject.h"
#include "EHPlayer.h"
#include "EHCamera.h"

namespace EH
{
	JailScene18::JailScene18()
	{
	}

	JailScene18::~JailScene18()
	{
	}

	void JailScene18::Initialize()
	{
		// HP
		BackGround* HPBack = object::Instantiate<BackGround>(enums::eLayerType::UI);
		HPBack->GetComponent<Transform>()->SetPos(Math::Vector2<float>(157.f, 42.f));
		HPBack->GetComponent<Transform>()->SetScale(Math::Vector2<float>(296.f, 64.f));
		Texture* temp = Resources::Load<Texture>(L"HPBack", L"..\\Resources\\UI\\PlayerLifeBack.png");
		HPBack->GetComponent<SpriteRenderer>()->SetImg(temp);
		HPBack->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* HPBase = object::Instantiate<BackGround>(enums::eLayerType::UI);
		HPBase->GetComponent<Transform>()->SetPos(Math::Vector2<float>(157.f, 42.f));
		HPBase->GetComponent<Transform>()->SetScale(Math::Vector2<float>(296.f, 64.f));
		temp = Resources::Load<Texture>(L"HPBase", L"..\\Resources\\UI\\PlayerLifeBase 1.png");
		HPBase->GetComponent<SpriteRenderer>()->SetImg(temp);
		HPBase->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// DASH
		BackGround* DashBase = object::Instantiate<BackGround>(enums::eLayerType::UI);
		DashBase->GetComponent<Transform>()->SetPos(Math::Vector2<float>(135.f, 97.f));
		DashBase->GetComponent<Transform>()->SetScale(Math::Vector2<float>(252.f, 34.f));
		temp = Resources::Load<Texture>(L"DashBase", L"..\\Resources\\UI\\DashCountBase.png");
		DashBase->GetComponent<SpriteRenderer>()->SetImg(temp);
		DashBase->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// COIN
		BackGround* Coin = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Coin->GetComponent<Transform>()->SetPos(Math::Vector2<float>(29.f, 657.f));
		Coin->GetComponent<Transform>()->SetScale(Math::Vector2<float>(17.f, 14.f));
		temp = Resources::Load<Texture>(L"CoinUI", L"..\\Resources\\UI\\Coin.png");
		Coin->GetComponent<SpriteRenderer>()->SetImg(temp);
		Coin->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// FOOD
		BackGround* Food = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Food->GetComponent<Transform>()->SetPos(Math::Vector2<float>(29.f, 690.f));
		Food->GetComponent<Transform>()->SetScale(Math::Vector2<float>(34.f, 28.f));
		temp = Resources::Load<Texture>(L"FoodUI", L"..\\Resources\\UI\\Food.png");
		Food->GetComponent<SpriteRenderer>()->SetImg(temp);
		Food->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// Weapon Swap
		BackGround* WeaponSlot = object::Instantiate<BackGround>(enums::eLayerType::UI);
		WeaponSlot->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1210.f, 641.f));
		WeaponSlot->GetComponent<Transform>()->SetScale(Math::Vector2<float>(140.f, 102.f));
		temp = Resources::Load<Texture>(L"WeaponSlot", L"..\\Resources\\UI\\EquippedWeaponBase.png");
		WeaponSlot->GetComponent<SpriteRenderer>()->SetImg(temp);
		WeaponSlot->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* WeaponSlot2 = object::Instantiate<BackGround>(enums::eLayerType::UI);
		WeaponSlot2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1190.f, 657.f));
		WeaponSlot2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(140.f, 102.f));
		temp = Resources::Load<Texture>(L"WeaponSlot", L"..\\Resources\\UI\\EquippedWeaponBase.png");
		WeaponSlot2->GetComponent<SpriteRenderer>()->SetImg(temp);
		WeaponSlot2->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Minimap = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Minimap->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1105.f, 58.f));
		Minimap->GetComponent<Transform>()->SetScale(Math::Vector2<float>(350.f, 85.f));
		Minimap->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailBossPrevBackGround = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBossPrevBackGround->GetComponent<Transform>()->SetPos(Math::Vector2<float>(760.f, 416.f));
		JailBossPrevBackGround->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1520.f, 832.f));
		temp = Resources::Load<Texture>(L"Jailprevprev", L"..\\Resources\\Dungeon\\Belial\\Bossprevprev.bmp");
		JailBossPrevBackGround->GetComponent<SpriteRenderer>()->SetImg(temp);

		BackGround* Candle1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Candle1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(376.f, 670.f));
		Candle1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(48.f, 68.f));
		temp = Resources::Load<Texture>(L"Candle1", L"..\\Resources\\Dungeon\\Belial\\CandleOn20.png");
		Candle1->GetComponent<SpriteRenderer>()->SetImg(temp);

		BackGround* Door1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Door1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(810.f, 574.f));
		Door1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(228.f, 260.f));
		temp = Resources::Load<Texture>(L"Door1", L"..\\Resources\\Dungeon\\Belial\\Door0.png");
		Door1->GetComponent<SpriteRenderer>()->SetImg(temp);

		BackGround* SavePoint1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		SavePoint1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1142.f, 670.f));
		SavePoint1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(92.f, 68.f));
		temp = Resources::Load<Texture>(L"SavePoint1", L"..\\Resources\\Dungeon\\Belial\\SavePoint_Off.png");
		SavePoint1->GetComponent<SpriteRenderer>()->SetImg(temp);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(266.f, 596.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		temp = Resources::Load<Texture>(L"PlayerRightIdle", L"..\\Resources\\Player\\Basic\\Idle\\CharRightIdleSheet.bmp");
		Animator* animator = player->AddComponent<Animator>();
		animator->CreateAnimation(L"PlayerRightIdle", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 5, 0.1f);
		animator->PlayAnimation(L"PlayerRightIdle", true);

		temp = Resources::Load<Texture>(L"PlayerRightRun", L"..\\Resources\\Player\\Basic\\Run\\CharRightRunSheet.bmp");
		animator->CreateAnimation(L"PlayerRightRun", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

		temp = Resources::Load<Texture>(L"PlayerRightDie", L"..\\Resources\\Player\\Basic\\Die\\CharRightDie.bmp");
		animator->CreateAnimation(L"PlayerRightDie", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);

		temp = Resources::Load<Texture>(L"PlayerRightJump", L"..\\Resources\\Player\\Basic\\Jump\\CharRightJump.bmp");
		animator->CreateAnimation(L"PlayerRightJump", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);

		// Left
		temp = Resources::Load<Texture>(L"PlayerLeftIdle", L"..\\Resources\\Player\\Basic\\Idle\\CharLeftIdleSheet.bmp");
		animator->CreateAnimation(L"PlayerLeftIdle", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 5, 0.1f);

		temp = Resources::Load<Texture>(L"PlayerLeftRun", L"..\\Resources\\Player\\Basic\\Run\\CharLeftRunSheet.bmp");
		animator->CreateAnimation(L"PlayerLeftRun", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

		temp = Resources::Load<Texture>(L"PlayerLeftDie", L"..\\Resources\\Player\\Basic\\Die\\CharLeftDie.bmp");
		animator->CreateAnimation(L"PlayerLeftDie", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);

		temp = Resources::Load<Texture>(L"PlayerLeftJump", L"..\\Resources\\Player\\Basic\\Jump\\CharLeftJump.bmp");
		animator->CreateAnimation(L"PlayerLeftJump", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);

		//player->GetComponent<SpriteRenderer>()->SetImg(temp);
	}

	void JailScene18::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailPrevBossScene");
		}
		Scene::Update();
	}

	void JailScene18::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene", 10);
	}

}