#include "EHJailScene2.h"
#include "EHSceneManager.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHFloor.h"
#include "EHTrigger.h"
#include "EHPlayer.h"
#include "EHCamera.h"
#include "EHCanvas.h"
#include "EHWall.h"
#include "EHCeil.h"
#include "EHBanshee.h"

namespace EH
{
	void JailScene2::Initialize()
	{
		SetSize(Math::Vector2<float>(1280.f, 896.f));
		BackGround* JailBG2 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 448.f));
		JailBG2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 896.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG2", L"..\\Resources\\Dungeon\\JailBackGround\\2\\JailField2.bmp");
		JailBG2->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG2->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// Floor
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(240.f, 796.f));
		floor1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(480.f, 64.f));
		floor1->AddComponent<Collider>();
		floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(480.f, 64.f));
		floor1->GetComponent<Collider>()->SetAffectedCamera(true);
		floor1->SetDownFloor(false);

		Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 796.f));
		floor2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(320.f, 64.f));
		floor2->AddComponent<Collider>();
		floor2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(320.f, 64.f));
		floor2->GetComponent<Collider>()->SetAffectedCamera(true);
		floor2->SetDownFloor(false);

		Floor* floor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(976.f, 796.f));
		floor3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(352.f, 64.f));
		floor3->AddComponent<Collider>();
		floor3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(352.f, 64.f));
		floor3->GetComponent<Collider>()->SetAffectedCamera(true);
		floor3->SetDownFloor(false);

		// Wall
		Wall* wall1 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(96.f, 380.f));
		wall1->AddComponent<Collider>();
		wall1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		wall1->GetComponent<Collider>()->SetAffectedCamera(true);
		wall1->SetRight(false);

		Wall* wall2 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(160.f, 252.f));
		wall2->AddComponent<Collider>();
		wall2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 128.f));
		wall2->GetComponent<Collider>()->SetAffectedCamera(true);
		wall2->SetRight(false);

		Wall* wall3 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(288.f, 188.f));
		wall3->AddComponent<Collider>();
		wall3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 128.f));
		wall3->GetComponent<Collider>()->SetAffectedCamera(true);
		wall3->SetRight(false);

		Wall* wall4 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(480.f, 92.f));
		wall4->AddComponent<Collider>();
		wall4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 192.f));
		wall4->GetComponent<Collider>()->SetAffectedCamera(true);
		wall4->SetRight(false);

		Wall* wall5 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(800.f, 96.f));
		wall5->AddComponent<Collider>();
		wall5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 192.f));
		wall5->GetComponent<Collider>()->SetAffectedCamera(true);

		Wall* wall6 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(992.f, 192.f));
		wall6->AddComponent<Collider>();
		wall6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 128.f));
		wall6->GetComponent<Collider>()->SetAffectedCamera(true);

		Wall* wall7 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall7->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1120.f, 256.f));
		wall7->AddComponent<Collider>();
		wall7->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 128.f));
		wall7->GetComponent<Collider>()->SetAffectedCamera(true);

		Wall* wall8 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall8->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1184.f, 508.f));
		wall8->AddComponent<Collider>();
		wall8->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 512.f));
		wall8->GetComponent<Collider>()->SetAffectedCamera(true);

		// Ceil
		Ceil* ceil1 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(64.f, 476.f));
		ceil1->AddComponent<Collider>();
		ceil1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(128.f, 64.f));
		ceil1->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil2 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(160.f, 284.f));
		ceil2->AddComponent<Collider>();
		ceil2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		ceil2->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil3 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(256.f, 220.f));
		ceil3->AddComponent<Collider>();
		ceil3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(128.f, 64.f));
		ceil3->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil4 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(416.f, 156.f));
		ceil4->AddComponent<Collider>();
		ceil4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(192.f, 64.f));
		ceil4->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil5 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(896.f, 160.f));
		ceil5->AddComponent<Collider>();
		ceil5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 64.f));
		ceil5->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil6 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1024.f, 224.f));
		ceil6->AddComponent<Collider>();
		ceil6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(128.f, 64.f));
		ceil6->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil7 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil7->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1112.f, 288.f));
		ceil7->AddComponent<Collider>();
		ceil7->GetComponent<Collider>()->SetScale(Math::Vector2<float>(128.f, 64.f));
		ceil7->GetComponent<Collider>()->SetAffectedCamera(true);

		// Trigger
		Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 636.f));
		trigger1->AddComponent<Collider>();
		trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger1->SetType(Trigger::eTriggertype::Scenechange);
		trigger1->SetScenename(L"JailScene6");

		Trigger* trigger2 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 96.f));
		trigger2->AddComponent<Collider>();
		trigger2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 64.f));
		trigger2->SetType(Trigger::eTriggertype::Scenechange);
		trigger2->SetScenename(L"JailScene3");

		Trigger* trigger3 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f,864.f));
		trigger3->AddComponent<Collider>();
		trigger3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(320.f, 64.f));
		trigger3->SetType(Trigger::eTriggertype::Scenechange);
		trigger3->SetScenename(L"JailScene1");

		// Steel
		Ceil* steel1 = object::Instantiate<Ceil>(enums::eLayerType::Steel);
		steel1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 160.f));
		steel1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(264.f, 80.f));
		steel1->AddComponent<Collider>();
		steel1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 64.f));
		Animator* ani = steel1->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"SteelOpen", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Ceil\\SteelOpenSheet2.bmp");
		ani->CreateAnimation(L"SteelOpen", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(66.f, 20.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelExit", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Ceil\\SteelExitSheet.bmp");
		ani->CreateAnimation(L"SteelExit", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(66.f, 20.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelIdle", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Ceil\\SteelIdleSheet.bmp");
		ani->CreateAnimation(L"SteelIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(66.f, 20.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

		Wall* steel2 = object::Instantiate<Wall>(enums::eLayerType::Steel);
		steel2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(96.f, 636.f));
		steel2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 264.f));
		steel2->AddComponent<Collider>();
		steel2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 264.f));
		steel2->SetRight(false);
		ani = steel2->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"SteelRightOpen", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Left\\SteelOpenSheet.bmp");
		ani->CreateAnimation(L"SteelOpen", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 66.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelRightExit", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Left\\SteelExitSheet.bmp");
		ani->CreateAnimation(L"SteelExit", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 66.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelRightIdle", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Left\\SteelIdleSheet.bmp");
		ani->CreateAnimation(L"SteelIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 66.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

		Floor* steel3 = object::Instantiate<Floor>(enums::eLayerType::Steel);
		steel3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 864.f));
		steel3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(264.f, 80.f));
		steel3->AddComponent<Collider>();
		steel3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 64.f));
		ani = steel3->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"SteelFloorOpen", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Floor\\SteelOpenSheet.bmp");
		ani->CreateAnimation(L"SteelOpen", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(66.f, 20.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelFloorExit", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Floor\\SteelExitSheet.bmp");
		ani->CreateAnimation(L"SteelExit", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(66.f, 20.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelFloorIdle", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Floor\\SteelIdleSheet.bmp");
		ani->CreateAnimation(L"SteelIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(66.f, 20.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

		// Enemy
		Banshee* banshee1 = object::Instantiate<Banshee>(enums::eLayerType::Enemy);
		banshee1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(400.f, 300.f));
		banshee1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 88.f));
		banshee1->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"BansheeIdle", L"..\\Resources\\Enemy\\JailField\\Banshee\\Idle\\BansheeIdleSheet.bmp");
		banshee1->GetComponent<Animator>()->CreateAnimation(L"BansheeIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 22.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		texture = Resources::Load<Texture>(L"BansheeAttack", L"..\\Resources\\Enemy\\JailField\\Banshee\\Attack\\BansheeAttackSheet.bmp");
		banshee1->GetComponent<Animator>()->CreateAnimation(L"BansheeAttack", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 22.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		banshee1->GetComponent<Animator>()->PlayAnimation(L"BansheeIdle", true);
		banshee1->SetTarget(player);
		banshee1->SetDelayTime(2.f);

		// SceneChanger Player
		SetPlayer(player);
	}
	void JailScene2::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene3");
		}
		Scene::Update();
	}
	void JailScene2::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene2", 10);
	}
}
