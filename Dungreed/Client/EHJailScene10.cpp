#include "EHJailScene10.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"
#include "EHPlayer.h"
#include "EHCanvas.h"
#include "EHFloor.h"
#include "EHTrigger.h"
#include "EHWall.h"
#include "EHCeil.h"
#include "EHBanshee.h"
#include "EHJailWarrior.h"
#include "EHJailDog.h"

namespace EH
{
	void JailScene10::Initialize()
	{
		SetSize(Math::Vector2<float>(2176.f, 720.f));

		BackGround* JailSubBG10 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailSubBG10->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		JailSubBG10->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		Texture* texture = Resources::Load<Texture>(L"JailSubBG", L"..\\Resources\\Dungeon\\JailBackGround\\4\\SubBG.bmp");
		JailSubBG10->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailSubBG10->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailBG10 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG10->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1088.f, 360.f));
		JailBG10->GetComponent<Transform>()->SetScale(Math::Vector2<float>(2176.f, 720.f));
		texture = Resources::Load<Texture>(L"JailBG10", L"..\\Resources\\Dungeon\\JailBackGround\\10\\JailField10.bmp");
		JailBG10->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG10->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// Floor
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1088.f, 612.f));
		floor1->AddComponent<Collider>();
		floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(2176.f, 64.f));
		floor1->GetComponent<Collider>()->SetAffectedCamera(true);
		floor1->SetDownFloor(true);

		// Ceil
		Ceil* ceil1 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(62.f, 292.f));
		ceil1->AddComponent<Collider>();
		ceil1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 64.f));
		ceil1->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil2 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1088.f, 96.f));
		ceil2->AddComponent<Collider>();
		ceil2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1920.f, 64.f));
		ceil2->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil3 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2114.f, 292.f));
		ceil3->AddComponent<Collider>();
		ceil3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 64.f));
		ceil3->GetComponent<Collider>()->SetAffectedCamera(true);

		// Wall
		Wall* wall1 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(96.f, 192.f));
		wall1->AddComponent<Collider>();
		wall1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		wall1->GetComponent<Collider>()->SetAffectedCamera(true);
		wall1->SetRight(false);

		Wall* wall2 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2080.f, 192.f));
		wall2->AddComponent<Collider>();
		wall2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		wall2->GetComponent<Collider>()->SetAffectedCamera(true);

		// Trigger
		Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 452.f));
		trigger1->AddComponent<Collider>();
		trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger1->SetType(Trigger::eTriggertype::Scenechange);
		trigger1->SetScenename(L"JailScene1");

		Trigger* trigger2 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2140.f, 452.f));
		trigger2->AddComponent<Collider>();
		trigger2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger2->SetType(Trigger::eTriggertype::Scenechange);
		trigger2->SetScenename(L"JailScene11");

		// Steel
		Wall* steel2 = object::Instantiate<Wall>(enums::eLayerType::Steel);
		steel2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 452.f));
		steel2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 264.f));
		steel2->AddComponent<Collider>();
		steel2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 264.f));
		steel2->SetRight(false);
		Animator* ani = steel2->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"SteelRightOpen", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Left\\SteelOpenSheet.bmp");
		ani->CreateAnimation(L"SteelOpen", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 66.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelRightExit", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Left\\SteelExitSheet.bmp");
		ani->CreateAnimation(L"SteelExit", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 66.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelRightIdle", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Left\\SteelIdleSheet.bmp");
		ani->CreateAnimation(L"SteelIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 66.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

		Wall* steel3 = object::Instantiate<Wall>(enums::eLayerType::Steel);
		steel3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2140.f, 452.f));
		steel3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 264.f));
		steel3->AddComponent<Collider>();
		steel3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 264.f));
		ani = steel3->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"SteelRightOpen", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Right\\SteelOpenSheet.bmp");
		ani->CreateAnimation(L"SteelOpen", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 66.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelRightExit", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Right\\SteelExitSheet.bmp");
		ani->CreateAnimation(L"SteelExit", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 66.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelRightIdle", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Right\\SteelIdleSheet.bmp");
		ani->CreateAnimation(L"SteelIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 66.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

		Banshee* banshee1 = object::Instantiate<Banshee>(enums::eLayerType::Enemy);
		banshee1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1092.f, 348.f));
		banshee1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 88.f));
		banshee1->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"BansheeIdle", L"..\\Resources\\Enemy\\JailField\\Banshee\\Idle\\BansheeIdleSheet.bmp");
		banshee1->GetComponent<Animator>()->CreateAnimation(L"BansheeIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 22.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		texture = Resources::Load<Texture>(L"BansheeAttack", L"..\\Resources\\Enemy\\JailField\\Banshee\\Attack\\BansheeAttackSheet.bmp");
		banshee1->GetComponent<Animator>()->CreateAnimation(L"BansheeAttack", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 22.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		banshee1->GetComponent<Animator>()->PlayAnimation(L"BansheeIdle", true);
		banshee1->SetTarget(player);
		banshee1->SetDelayTime(2.f);

		JailWarrior* warrior1 = object::Instantiate<JailWarrior>(enums::eLayerType::Enemy);
		warrior1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(856.f, 508.f));
		warrior1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		Collider* col = warrior1->AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(128.f, 128.f));
		warrior1->GetComponent<Animator>()->PlayAnimation(L"GreySkelRightIdle", true);

		JailWarrior* warrior2 = object::Instantiate<JailWarrior>(enums::eLayerType::Enemy);
		warrior2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1644.f, 508.f));
		warrior2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		col = warrior2->AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(128.f, 128.f));
		warrior2->GetComponent<Animator>()->PlayAnimation(L"GreySkelRightIdle", true);

		JailDog* dog1 = object::Instantiate<JailDog>(enums::eLayerType::Enemy);
		dog1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(508.f, 536.f));
		dog1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 72.f));
		dog1->GetComponent<Animator>()->PlayAnimation(L"SkelDogRightIdle", true);

		JailDog* dog2 = object::Instantiate<JailDog>(enums::eLayerType::Enemy);
		dog2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1400.f, 536.f));
		dog2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 72.f));
		dog2->GetComponent<Animator>()->PlayAnimation(L"SkelDogRightIdle", true);

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailScene10::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene11");
		}
		Scene::Update();
	}

	void JailScene10::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene10", 11);
	}
}
