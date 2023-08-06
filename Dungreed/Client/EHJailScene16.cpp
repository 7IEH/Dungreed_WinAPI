#include "EHJailScene16.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"
#include "EHPlayer.h"
#include "EHCanvas.h"
#include "EHTrigger.h"
#include "EHFloor.h"
#include "EHWall.h"
#include "EHCeil.h"


namespace EH
{
	void JailScene16::Initialize()
	{
		SetSize(Math::Vector2<float>(1280.f, 1024.f));
		BackGround* JailBG16 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG16->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 512.f));
		JailBG16->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 1024.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG16", L"..\\Resources\\Dungeon\\JailBackGround\\16\\JailField16.bmp");
		JailBG16->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG16->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// Floor
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 608.f));
		floor1->AddComponent<Collider>();
		floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1280.f, 64.f));
		floor1->GetComponent<Collider>()->SetAffectedCamera(true);
		floor1->SetDownFloor(true);

		Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(256.f, 816.f));
		floor2->AddComponent<Collider>();
		floor2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(128.f, 64.f));
		floor2->GetComponent<Collider>()->SetAffectedCamera(true);
		floor2->SetDownFloor(false);

		Floor* floor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1036.f, 804.f));
		floor3->AddComponent<Collider>();
		floor3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(128.f, 64.f));
		floor3->GetComponent<Collider>()->SetAffectedCamera(true);
		floor3->SetDownFloor(false);

		Floor* floor4 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 928.f));
		floor4->AddComponent<Collider>();
		floor4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1024.f, 64.f));
		floor4->GetComponent<Collider>()->SetAffectedCamera(true);
		floor4->SetDownFloor(true);

		// Ceil
		Ceil* ceil1 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(62.f, 288.f));
		ceil1->AddComponent<Collider>();
		ceil1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 64.f));
		ceil1->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil2 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(608.f, 96.f));
		ceil2->AddComponent<Collider>();
		ceil2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(960.f, 64.f));
		ceil2->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil3 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1186.f, 288.f));
		ceil3->AddComponent<Collider>();
		ceil3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(188.f, 64.f));
		ceil3->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil4 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 612.f));
		ceil4->AddComponent<Collider>();
		ceil4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(504.f, 56.f));
		ceil4->GetComponent<Collider>()->SetAffectedCamera(true);

		// Wall
		Wall* wall1 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(96.f, 190.f));
		wall1->AddComponent<Collider>();
		wall1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 252.f));
		wall1->GetComponent<Collider>()->SetAffectedCamera(true);
		wall1->SetRight(false);

		Wall* wall2 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1120.f, 190.f));
		wall2->AddComponent<Collider>();
		wall2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 252.f));
		wall2->GetComponent<Collider>()->SetAffectedCamera(true);

		Wall* wall3 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(96.f, 742.f));
		wall3->AddComponent<Collider>();
		wall3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 316.f));
		wall3->GetComponent<Collider>()->SetAffectedCamera(true);
		wall3->SetRight(false);

		Wall* wall4 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1184.f, 742.f));
		wall4->AddComponent<Collider>();
		wall4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 316.f));
		wall4->GetComponent<Collider>()->SetAffectedCamera(true);

		Wall* wall5 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(480.f, 962.f));
		wall5->AddComponent<Collider>();
		wall5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 124.f));
		wall5->GetComponent<Collider>()->SetAffectedCamera(true);
		wall5->SetRight(false);

		Wall* wall6 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(800.f, 962.f));
		wall6->AddComponent<Collider>();
		wall6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 124.f));
		wall6->GetComponent<Collider>()->SetAffectedCamera(true);
		wall6->SetRight(false);

		Wall* wall7 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall7->GetComponent<Transform>()->SetPos(Math::Vector2<float>(416.f, 610.f));
		wall7->AddComponent<Collider>();
		wall7->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 60.f));
		wall7->GetComponent<Collider>()->SetAffectedCamera(true);
		wall7->SetRight(false);

		Wall* wall8 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall8->GetComponent<Transform>()->SetPos(Math::Vector2<float>(864.f, 610.f));
		wall8->AddComponent<Collider>();
		wall8->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 60.f));
		wall8->GetComponent<Collider>()->SetAffectedCamera(true);
		wall8->SetRight(false);

		// Trigger
		Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 448.f));
		trigger1->AddComponent<Collider>();
		trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger1->SetType(Trigger::eTriggertype::Scenechange);
		trigger1->SetScenename(L"JailScene14");

		Trigger* trigger2 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1244.f, 448.f));
		trigger2->AddComponent<Collider>();
		trigger2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger2->SetType(Trigger::eTriggertype::Scenechange);
		trigger2->SetScenename(L"JailScene17");

		Trigger* trigger3 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 988.f));
		trigger3->AddComponent<Collider>();
		trigger3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 64.f));
		trigger3->SetType(Trigger::eTriggertype::Scenechange);
		trigger3->SetScenename(L"JailScene18");

		// Steel
		Wall* steel2 = object::Instantiate<Wall>(enums::eLayerType::Steel);
		steel2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 448.f));
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
		steel3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1244.f, 448.f));
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

		Floor* steel4 = object::Instantiate<Floor>(enums::eLayerType::Steel);
		steel4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 988.f));
		steel4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(264.f, 80.f));
		steel4->AddComponent<Collider>();
		steel4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 64.f));
		ani = steel4->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"SteelFloorOpen", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Floor\\SteelOpenSheet.bmp");
		ani->CreateAnimation(L"SteelOpen", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(66.f, 20.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelFloorExit", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Floor\\SteelExitSheet.bmp");
		ani->CreateAnimation(L"SteelExit", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(66.f, 20.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelFloorIdle", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Floor\\SteelIdleSheet.bmp");
		ani->CreateAnimation(L"SteelIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(66.f, 20.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailScene16::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene17");
		}
		Scene::Update();
	}

	void JailScene16::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene16", 11);
	}
}
