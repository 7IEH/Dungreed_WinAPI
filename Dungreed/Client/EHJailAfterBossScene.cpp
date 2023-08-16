#include "EHJailAfterBossScene.h"
#include "EHPlayer.h"
#include "EHResources.h"
#include "EHCanvas.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHFloor.h"
#include "EHTrigger.h"
#include "EHIceScene1.h"

namespace EH
{
	void JailAfterBossScene::Initialize()
	{
		Sound* BGM = Resources::Load<Sound>(L"JailFieldBGM", L"..\\Resources\\Sound\\BGM\\1.JailField.wav");
		SetBGM(BGM);

		SetSize(Math::Vector2<float>(1280.f, 720.f));

		Texture* texture = nullptr;

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(820.f, 300.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// SceneChanger Player
		SetPlayer(player);

		// UI Canvas
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
		PlayerUICanvas->AddImageObject(L"CoinUI", texture, false, Math::Vector2<float>(29.f, 657.f), Math::Vector2<float>(17.f, 14.f));

		texture = Resources::Load<Texture>(L"FoodUI", L"..\\Resources\\UI\\Food.png");
		PlayerUICanvas->AddImageObject(L"FoodUI", texture, false, Math::Vector2<float>(29.f, 690.f), Math::Vector2<float>(34.f, 28.f));

		texture = Resources::Load<Texture>(L"WeaponSlot", L"..\\Resources\\UI\\EquippedWeaponBase.png");
		PlayerUICanvas->AddImageObject(L"WeaponSlot", texture, false, Math::Vector2<float>(1210.f, 641.f), Math::Vector2<float>(140.f, 102.f));
		PlayerUICanvas->AddImageObject(L"WeaponSlot2", texture, false, Math::Vector2<float>(1190.f, 657.f), Math::Vector2<float>(140.f, 102.f));

		BackGround* JailBossAfterBackGround = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBossAfterBackGround->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		JailBossAfterBackGround->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		texture = Resources::Load<Texture>(L"JailBossAfterBackGround", L"..\\Resources\\Dungeon\\Belial\\BossAfter.bmp");
		JailBossAfterBackGround->GetComponent<SpriteRenderer>()->SetImg(texture);
		//JailBossPrevBackGround->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// Structure
		// Floor
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(608.f, 560.f));
		floor1->AddComponent<Collider>();
		floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1216.f, 64.f));
		floor1->GetComponent<Collider>()->SetAffectedCamera(true);
		floor1->SetDownFloor(false);

		Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(696.f, 398.f));
		trigger1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(228.f, 260.f));
		SpriteRenderer* sr = trigger1->AddComponent<SpriteRenderer>();
		texture = Resources::Load<Texture>(L"JailDoor0", L"..\\Resources\\Dungeon\\Belial\\Door0.bmp");
		sr->SetImg(texture);
		sr->SetAffectCamera(true);
		trigger1->AddComponent<Collider>();
		trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(228.f, 260.f));
		trigger1->SetType(Trigger::eTriggertype::Scenechange);
		trigger1->SetScenename(L"IceScene1");
		trigger1->SetKey(eKeyCode::W);
	}

	void JailAfterBossScene::Update()
	{
		Scene::Update();
	}

	void JailAfterBossScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}