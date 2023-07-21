#include "EHJailBossScene.h"
#include "EHSceneManager.h"
#include "EHBackGround.h"
#include "EHResources.h"
#include "EHObject.h"
#include "EHPlayer.h"
#include "EHCamera.h"


namespace EH
{
	JailBossScene::JailBossScene()
	{
	}

	JailBossScene::~JailBossScene()
	{
	}

	void JailBossScene::Initialize()
	{
		SetSize(Math::Vector2<float>(1440.f, 1320.f));
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

		BackGround* JailBossBackGround = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBossBackGround->GetComponent<Transform>()->SetPos(Math::Vector2<float>(720.f, 660.f));
		JailBossBackGround->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1440.f, 1320.f));
		temp = Resources::Load<Texture>(L"JailBossBackGround", L"..\\Resources\\Dungeon\\Belial\\Boss.bmp");
		JailBossBackGround->GetComponent<SpriteRenderer>()->SetImg(temp);
		//JailBossBackGround->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// Torch
		BackGround* Torch1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Torch1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(524.f, 804.f));
		Torch1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		temp = Resources::Load<Texture>(L"Torch", L"..\\Resources\\Dungeon\\Belial\\Torch0.png");
		Torch1->GetComponent<SpriteRenderer>()->SetImg(temp);
		//Torch1->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Torch2 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Torch2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(936.f, 804.f));
		Torch2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		temp = Resources::Load<Texture>(L"Torch", L"..\\Resources\\Dungeon\\Belial\\Torch0.png");
		Torch2->GetComponent<SpriteRenderer>()->SetImg(temp);
		//Torch2->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Torch3 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Torch3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(476.f, 320.f));
		Torch3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		temp = Resources::Load<Texture>(L"Torch", L"..\\Resources\\Dungeon\\Belial\\Torch0.png");
		Torch3->GetComponent<SpriteRenderer>()->SetImg(temp);
		//Torch3->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Torch4 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Torch4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(948.f, 320.f));
		Torch4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		temp = Resources::Load<Texture>(L"Torch", L"..\\Resources\\Dungeon\\Belial\\Torch0.png");
		Torch4->GetComponent<SpriteRenderer>()->SetImg(temp);
		//Torch4->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// Floor
		BackGround* JailFloor1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailFloor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(718.f, 224.f));
		JailFloor1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		temp = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor1->GetComponent<SpriteRenderer>()->SetImg(temp);
		//JailFloor1->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailFloor2 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailFloor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1166.f, 324.f));
		JailFloor2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		temp = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor2->GetComponent<SpriteRenderer>()->SetImg(temp);
		//JailFloor2->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailFloor3 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailFloor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(294.f, 324.f));
		JailFloor3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		temp = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor3->GetComponent<SpriteRenderer>()->SetImg(temp);
		//JailFloor3->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailFloor4 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailFloor4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1166.f, 552.f));
		JailFloor4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		temp = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor4->GetComponent<SpriteRenderer>()->SetImg(temp);
		//JailFloor4->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailFloor5 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailFloor5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(294.f, 552.f));
		JailFloor5->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		temp = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor5->GetComponent<SpriteRenderer>()->SetImg(temp);
		//JailFloor5->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailFloor6 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailFloor6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1094.f, 784.f));
		JailFloor6->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		temp = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor6->GetComponent<SpriteRenderer>()->SetImg(temp);
		//JailFloor6->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailFloor7 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailFloor7->GetComponent<Transform>()->SetPos(Math::Vector2<float>(334.f, 784.f));
		JailFloor7->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		temp = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor7->GetComponent<SpriteRenderer>()->SetImg(temp);
		//JailFloor7->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailFloor8 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailFloor8->GetComponent<Transform>()->SetPos(Math::Vector2<float>(734.f, 996.f));
		JailFloor8->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		temp = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor8->GetComponent<SpriteRenderer>()->SetImg(temp);
		//JailFloor8->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// Boss
		BackGround* Boss1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Boss1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(704.f, 598.f));
		Boss1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(280.f, 396.f));
		temp = Resources::Load<Texture>(L"BossIdle", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\Idle\\SkellBossIdleSheet.bmp");
		Boss1->AddComponent<Animator>();
		Boss1->GetComponent<Animator>()->CreateAnimation(L"BossIdle", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(70.f, 99.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		Boss1->GetComponent<Animator>()->PlayAnimation(L"BossIdle", true);
		Boss1->GetComponent<Animator>()->SetAffectedCamera(true);

		BackGround* BossLeftHand = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		BossLeftHand->GetComponent<Transform>()->SetPos(Math::Vector2<float>(370.f, 822.f));
		BossLeftHand->GetComponent<Transform>()->SetScale(Math::Vector2<float>(228.f, 276.f));
		temp = Resources::Load<Texture>(L"BossLeftHandIdle", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\HandleLeft\\SkellBossLeftHandIdleSheet.bmp");
		BossLeftHand->AddComponent<Animator>();
		BossLeftHand->GetComponent<Animator>()->CreateAnimation(L"BossLeftHandIdle", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(57.f, 69.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		BossLeftHand->GetComponent<Animator>()->PlayAnimation(L"BossLeftHandIdle", true);
		BossLeftHand->GetComponent<Animator>()->SetAffectedCamera(true);

		BackGround* BossRightHand = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		BossRightHand->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1106.f, 542.f));
		BossRightHand->GetComponent<Transform>()->SetScale(Math::Vector2<float>(228.f, 276.f));
		temp = Resources::Load<Texture>(L"BossRightHand", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\HandleRight\\SkellBossRightHandIdleSheet.bmp");
		BossRightHand->AddComponent<Animator>();
		BossRightHand->GetComponent<Animator>()->CreateAnimation(L"BossRightHand", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(57.f, 69.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		BossRightHand->GetComponent<Animator>()->PlayAnimation(L"BossRightHand", true);
		BossRightHand->GetComponent<Animator>()->SetAffectedCamera(true);

		// Player
		/*Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(300.f, 630.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		temp = Resources::Load<Texture>(L"player", L"..\\Resources\\Player\\Basic\\Idle\\CharIdle0.png");
		player->GetComponent<SpriteRenderer>()->SetImg(temp);*/

	}

	void JailBossScene::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"TitleScene");
		}
		Scene::Update();
	}

	void JailBossScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailBossScene", 13);
	}
}