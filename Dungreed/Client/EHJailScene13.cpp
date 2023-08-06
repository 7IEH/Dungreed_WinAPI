#include "EHJailScene13.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"
#include "EHPlayer.h"
#include "EHCanvas.h"
#include "EHFloor.h"
#include "EHSlope.h"
#include "EHTrigger.h"
#include "EHWall.h"
#include "EHCeil.h"


namespace EH
{
	void JailScene13::Initialize()
	{
		SetSize(Math::Vector2<float>(1920.f, 1152.f));

		BackGround* JailSubBG13 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailSubBG13->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		JailSubBG13->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		Texture* texture = Resources::Load<Texture>(L"JailSubBG", L"..\\Resources\\Dungeon\\JailBackGround\\4\\SubBG.bmp");
		JailSubBG13->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailSubBG13->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailBG13 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG13->GetComponent<Transform>()->SetPos(Math::Vector2<float>(960.f, 576.f));
		JailBG13->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1920.f, 1152.f));
		texture = Resources::Load<Texture>(L"JailBG13", L"..\\Resources\\Dungeon\\JailBackGround\\13\\JailField13.bmp");
		JailBG13->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG13->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// Floor
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(576.f, 928.f));
		floor1->AddComponent<Collider>();
		floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1152.f, 64.f));
		floor1->GetComponent<Collider>()->SetAffectedCamera(true);
		floor1->SetDownFloor(false);

		Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1536.f, 1056.f));
		floor2->AddComponent<Collider>();
		floor2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1152.f, 64.f));
		floor2->GetComponent<Collider>()->SetAffectedCamera(true);
		floor2->SetDownFloor(false);

		Floor* floor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1472.f, 416.f));
		floor3->AddComponent<Collider>();
		floor3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(640.f, 64.f));
		floor3->GetComponent<Collider>()->SetAffectedCamera(true);
		floor3->SetDownFloor(false);

		Floor* floor4 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(608.f, 648.f));
		floor4->AddComponent<Collider>();
		floor4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(960.f, 64.f));
		floor4->GetComponent<Collider>()->SetAffectedCamera(true);
		floor4->SetDownFloor(true);

		// Slope
		Slope* slope1 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1184.f, 928.f));
		slope1->AddComponent<Collider>();
		slope1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope1->GetComponent<Collider>()->SetAffectedCamera(true);
		slope1->SetIntercept(256.f);
		slope1->SetCorrection(90.f);

		Slope* slope2 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1248.f, 992.f));
		slope2->AddComponent<Collider>();
		slope2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope2->GetComponent<Collider>()->SetAffectedCamera(true);
		slope2->SetIntercept(256.f);
		slope2->SetCorrection(90.f);

		Slope* slope3 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1120.f, 416.f));
		slope3->AddComponent<Collider>();
		slope3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope3->GetComponent<Collider>()->SetAffectedCamera(true);
		slope3->SetIntercept(1536.f);
		slope3->SetCorrection(90.f);
		slope3->SetRight(true);

		// Ceil
		Ceil* ceil1 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(62.f, 608.f));
		ceil1->AddComponent<Collider>();
		ceil1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 64.f));
		ceil1->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil2 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(448.f, 352.f));
		ceil2->AddComponent<Collider>();
		ceil2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(120.f, 64.f));
		ceil2->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil3 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1152.f, 96.f));
		ceil3->AddComponent<Collider>();
		ceil3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1280.f, 64.f));
		ceil3->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil4 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1442.f, 608.f));
		ceil4->AddComponent<Collider>();
		ceil4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(700.f, 64.f));
		ceil4->GetComponent<Collider>()->SetAffectedCamera(true);

		// Wall
		Wall* wall1 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(96.f, 318.f));
		wall1->AddComponent<Collider>();
		wall1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 636.f));
		wall1->GetComponent<Collider>()->SetAffectedCamera(true);
		wall1->SetRight(false);

		Wall* wall2 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(416.f, 188.f));
		wall2->AddComponent<Collider>();
		wall2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 384.f));
		wall2->GetComponent<Collider>()->SetAffectedCamera(true);

		Wall* wall3 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(480.f, 222.f));
		wall3->AddComponent<Collider>();
		wall3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 316.f));
		wall3->GetComponent<Collider>()->SetAffectedCamera(true);
		wall3->SetRight(false);

		Wall* wall4 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1824.f, 224.f));
		wall4->AddComponent<Collider>();
		wall4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 320.f));
		wall4->GetComponent<Collider>()->SetAffectedCamera(true);

		Wall* wall5 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1120.f, 540.f));
		wall5->AddComponent<Collider>();
		wall5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 184.f));
		wall5->GetComponent<Collider>()->SetAffectedCamera(true);

		Wall* wall6 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1824.f, 544.f));
		wall6->AddComponent<Collider>();
		wall6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 960.f));
		wall6->GetComponent<Collider>()->SetAffectedCamera(true);


		// Trigger
		Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 768.f));
		trigger1->AddComponent<Collider>();
		trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger1->SetType(Trigger::eTriggertype::Scenechange);
		trigger1->SetScenename(L"JailScene12");

		Trigger* trigger2 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(256.f, 32.f));
		trigger2->AddComponent<Collider>();
		trigger2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 64.f));
		trigger2->SetType(Trigger::eTriggertype::Scenechange);
		trigger2->SetScenename(L"JailScene14");

		// Steel
		Ceil* steel1 = object::Instantiate<Ceil>(enums::eLayerType::Steel);
		steel1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(256.f, 32.f));
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
		steel2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 768.f));
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

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailScene13::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene14");
		}
		Scene::Update();
	}

	void JailScene13::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene13", 11);
	}
}