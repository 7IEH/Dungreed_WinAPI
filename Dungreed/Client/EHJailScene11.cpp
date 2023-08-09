#include "EHJailScene11.h"
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
	void JailScene11::Initialize()
	{
		SetSize(Math::Vector2<float>(1600.f, 768.f));
		BackGround* JailBG11 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG11->GetComponent<Transform>()->SetPos(Math::Vector2<float>(800.f, 384.f));
		JailBG11->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1600.f, 768.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG11", L"..\\Resources\\Dungeon\\JailBackGround\\11\\JailField11.bmp");
		JailBG11->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG11->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// Floor
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(90.f, 544.f));
		floor1->AddComponent<Collider>();
		floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(180.f, 64.f));
		floor1->GetComponent<Collider>()->SetAffectedCamera(true);
		floor1->SetDownFloor(true);

		Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(802.f, 672.f));
		floor2->AddComponent<Collider>();
		floor2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(988.f, 64.f));
		floor2->GetComponent<Collider>()->SetAffectedCamera(true);
		floor2->SetDownFloor(true);

		Floor* floor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1512.f, 544.f));
		floor3->AddComponent<Collider>();
		floor3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(184.f, 64.f));
		floor3->GetComponent<Collider>()->SetAffectedCamera(true);
		floor3->SetDownFloor(true);

		Floor* floor4 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(804.f, 296.f));
		floor4->AddComponent<Collider>();
		floor4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1088.f, 64.f));
		floor4->GetComponent<Collider>()->SetAffectedCamera(true);
		floor4->SetDownFloor(true);

		// Slope
		Slope* slope1 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(212.f, 544.f));
		slope1->AddComponent<Collider>();
		slope1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope1->GetComponent<Collider>()->SetAffectedCamera(true);
		slope1->SetIntercept(-332.f);
		slope1->SetCorrection(90.f);

		Slope* slope2 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(276.f, 608.f));
		slope2->AddComponent<Collider>();
		slope2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope2->GetComponent<Collider>()->SetAffectedCamera(true);
		slope2->SetIntercept(-332.f);
		slope2->SetCorrection(90.f);

		Slope* slope3 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1324.f, 608.f));
		slope3->AddComponent<Collider>();
		slope3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope3->GetComponent<Collider>()->SetAffectedCamera(true);
		slope3->SetIntercept(1932.f);
		slope3->SetCorrection(90.f);
		slope3->SetRight(true);

		Slope* slope4 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1388.f, 544.f));
		slope4->AddComponent<Collider>();
		slope4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope4->GetComponent<Collider>()->SetAffectedCamera(true);
		slope4->SetIntercept(1932.f);
		slope4->SetCorrection(90.f);
		slope4->SetRight(true);

		// Ceil
		Ceil* ceil1 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(62.f, 224.f));
		ceil1->AddComponent<Collider>();
		ceil1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 64.f));
		ceil1->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil2 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(800.f, 64.f));
		ceil2->AddComponent<Collider>();
		ceil2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1344.f, 64.f));
		ceil2->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil3 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1538.f, 224.f));
		ceil3->AddComponent<Collider>();
		ceil3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 64.f));
		ceil3->GetComponent<Collider>()->SetAffectedCamera(true);

		// Wall
		Wall* wall1 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(96.f, 126.f));
		wall1->AddComponent<Collider>();
		wall1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 252.f));
		wall1->GetComponent<Collider>()->SetAffectedCamera(true);
		wall1->SetRight(false);

		Wall* wall2 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1504.f, 126.f));
		wall2->AddComponent<Collider>();
		wall2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f,252.f));
		wall2->GetComponent<Collider>()->SetAffectedCamera(true);

		// Trigger
		Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 384.f));
		trigger1->AddComponent<Collider>();
		trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger1->SetType(Trigger::eTriggertype::Scenechange);
		trigger1->SetScenename(L"JailScene10");

		Trigger* trigger2 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1564.f, 384.f));
		trigger2->AddComponent<Collider>();
		trigger2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger2->SetType(Trigger::eTriggertype::Scenechange);
		trigger2->SetScenename(L"JailScene12");

		// Steel
		Wall* steel2 = object::Instantiate<Wall>(enums::eLayerType::Steel);
		steel2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 384.f));
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
		steel3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1564.f, 384.f));
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

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailScene11::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene12");
		}
		Scene::Update();
	}

	void JailScene11::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene11", 11);
	}
}