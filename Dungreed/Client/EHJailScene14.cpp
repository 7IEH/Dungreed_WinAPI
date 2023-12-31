#include "EHJailScene14.h"
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
#include "EHJailArchor.h"

namespace EH
{
	void JailScene14::Initialize()
	{
		Sound* BGM = Resources::Load<Sound>(L"JailFieldBGM", L"..\\Resources\\Sound\\BGM\\1.JailField.wav");
		SetBGM(BGM);

		SetSize(Math::Vector2<float>(1280.f, 1024.f));
		BackGround* JailBG14 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG14->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 512.f));
		JailBG14->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 1024.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG14", L"..\\Resources\\Dungeon\\JailBackGround\\14\\JailField14-1.bmp");
		JailBG14->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG14->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// Floor
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(544.f, 928.f));
		floor1->AddComponent<Collider>();
		floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(576.f, 64.f));
		floor1->GetComponent<Collider>()->SetAffectedCamera(true);
		floor1->SetDownFloor(true);

		Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(668.f, 748.f));
		floor2->AddComponent<Collider>();
		floor2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(192.f, 64.f));
		floor2->GetComponent<Collider>()->SetAffectedCamera(true);
		floor2->SetDownFloor(true);

		Floor* floor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(668.f, 576.f));
		floor3->AddComponent<Collider>();
		floor3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(192.f, 64.f));
		floor3->GetComponent<Collider>()->SetAffectedCamera(true);
		floor3->SetDownFloor(true);

		Floor* floor4 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(668.f, 416.f));
		floor4->AddComponent<Collider>();
		floor4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(192.f, 64.f));
		floor4->GetComponent<Collider>()->SetAffectedCamera(true);
		floor4->SetDownFloor(true);

		Floor* floor5 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(928.f, 416.f));
		floor5->AddComponent<Collider>();
		floor5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(192.f, 64.f));
		floor5->GetComponent<Collider>()->SetAffectedCamera(true);
		floor5->SetDownFloor(true);

		// Ceil
		Ceil* ceil1 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(350.f, 608.f));
		ceil1->AddComponent<Collider>();
		ceil1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(188.f, 64.f));
		ceil1->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil2 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(736.f, 96.f));
		ceil2->AddComponent<Collider>();
		ceil2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(576.f, 64.f));
		ceil2->GetComponent<Collider>()->SetAffectedCamera(true);

		// Wall
		Wall* wall1 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(864.f, 706.f));
		wall1->AddComponent<Collider>();
		wall1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 636.f));
		wall1->GetComponent<Collider>()->SetAffectedCamera(true);

		Wall* wall2 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(544.f, 962.f));
		wall2->AddComponent<Collider>();
		wall2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 124.f));
		wall2->GetComponent<Collider>()->SetAffectedCamera(true);
		wall2->SetRight(false);

		Wall* wall3 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(416.f, 350.f));
		wall3->AddComponent<Collider>();
		wall3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 572.f));
		wall3->GetComponent<Collider>()->SetAffectedCamera(true);
		wall3->SetRight(false);


		// Trigger
		Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(288.f, 768.f));
		trigger1->AddComponent<Collider>();
		trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger1->SetType(Trigger::eTriggertype::Scenechange);
		trigger1->SetScenename(L"JailScene15");

		Trigger* trigger2 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(704.f, 988.f));
		trigger2->AddComponent<Collider>();
		trigger2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 64.f));
		trigger2->SetType(Trigger::eTriggertype::Scenechange);
		trigger2->SetScenename(L"JailScene13");

		Trigger* trigger3 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(988.f, 256.f));
		trigger3->AddComponent<Collider>();
		trigger3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger3->SetType(Trigger::eTriggertype::Scenechange);
		trigger3->SetScenename(L"JailScene16");

		// Steel
		Wall* steel2 = object::Instantiate<Wall>(enums::eLayerType::Steel);
		steel2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(288.f, 768.f));
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
		steel3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(988.f, 256.f));
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
		steel4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(704.f, 988.f));
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

		// Enemy
		JailArchor* archor1 = object::Instantiate<JailArchor>(enums::eLayerType::Enemy);
		archor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(672.f, 648.f));
		archor1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		Collider* col = archor1->AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(128.f, 128.f));
		archor1->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"GreySkelRightIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Right\\GraySkelIdle.bmp");
		archor1->GetComponent<Animator>()->CreateAnimation(L"GreySkelRightIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		texture = Resources::Load<Texture>(L"GreySkelLeftIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Left\\GraySkelIdle.bmp");
		archor1->GetComponent<Animator>()->CreateAnimation(L"GreySkelLeftIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		archor1->GetComponent<Animator>()->PlayAnimation(L"GreySkelRightIdle", true);

		JailArchor* archor2 = object::Instantiate<JailArchor>(enums::eLayerType::Enemy);
		archor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(672.f, 476.f));
		archor2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		col = archor2->AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(128.f, 128.f));
		archor2->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"GreySkelRightIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Right\\GraySkelIdle.bmp");
		archor2->GetComponent<Animator>()->CreateAnimation(L"GreySkelRightIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		texture = Resources::Load<Texture>(L"GreySkelLeftIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Left\\GraySkelIdle.bmp");
		archor2->GetComponent<Animator>()->CreateAnimation(L"GreySkelLeftIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		archor2->GetComponent<Animator>()->PlayAnimation(L"GreySkelRightIdle", true);

		JailArchor* archor3 = object::Instantiate<JailArchor>(enums::eLayerType::Enemy);
		archor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(672.f, 316.f));
		archor3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		col = archor3->AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(128.f, 128.f));
		archor3->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"GreySkelRightIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Right\\GraySkelIdle.bmp");
		archor3->GetComponent<Animator>()->CreateAnimation(L"GreySkelRightIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		texture = Resources::Load<Texture>(L"GreySkelLeftIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Left\\GraySkelIdle.bmp");
		archor3->GetComponent<Animator>()->CreateAnimation(L"GreySkelLeftIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		archor3->GetComponent<Animator>()->PlayAnimation(L"GreySkelRightIdle", true);

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailScene14::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene15");
		}
		Scene::Update();
	}

	void JailScene14::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}
