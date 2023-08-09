#include "EHJailScene17.h"
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
	void JailScene17::Initialize()
	{
		SetSize(Math::Vector2<float>(1280.f,896.f));
		BackGround* JailBG17 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG17->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f,448.f));
		JailBG17->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 896.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG17", L"..\\Resources\\Dungeon\\JailBackGround\\17\\JailField17.bmp");
		JailBG17->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG17->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// Floor
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(576.f, 800.f));
		floor1->AddComponent<Collider>();
		floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1152.f, 64.f));
		floor1->GetComponent<Collider>()->SetAffectedCamera(true);
		floor1->SetDownFloor(true);

		// Ceil
		Ceil* ceil1 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(62.f, 480.f));
		ceil1->AddComponent<Collider>();
		ceil1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 64.f));
		ceil1->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil2 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(158.f, 160.f));
		ceil2->AddComponent<Collider>();
		ceil2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(60.f, 64.f));
		ceil2->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil3 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(222.f, 96.f));
		ceil3->AddComponent<Collider>();
		ceil3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(60.f, 64.f));
		ceil3->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil4 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 64.f));
		ceil4->AddComponent<Collider>();
		ceil4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(768.f, 64.f));
		ceil4->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil5 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1058.f, 96.f));
		ceil5->AddComponent<Collider>();
		ceil5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(60.f, 64.f));
		ceil5->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil6 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1122.f, 160.f));
		ceil6->AddComponent<Collider>();
		ceil6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(60.f, 64.f));
		ceil6->GetComponent<Collider>()->SetAffectedCamera(true);

		// Wall
		Wall* wall1 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(96.f, 318.f));
		wall1->AddComponent<Collider>();
		wall1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 380.f));
		wall1->GetComponent<Collider>()->SetAffectedCamera(true);
		wall1->SetRight(false);

		Wall* wall2 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(160.f, 124.f));
		wall2->AddComponent<Collider>();
		wall2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 128.f));
		wall2->GetComponent<Collider>()->SetAffectedCamera(true);
		wall2->SetRight(false);

		Wall* wall3 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(224.f, 60.f));
		wall3->AddComponent<Collider>();
		wall3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 128.f));
		wall3->GetComponent<Collider>()->SetAffectedCamera(true);
		wall3->SetRight(false);

		Wall* wall4 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1056.f, 60.f));
		wall4->AddComponent<Collider>();
		wall4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 128.f));
		wall4->GetComponent<Collider>()->SetAffectedCamera(true);

		Wall* wall5 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1120.f, 124.f));
		wall5->AddComponent<Collider>();
		wall5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 128.f));
		wall5->GetComponent<Collider>()->SetAffectedCamera(true);

		Wall* wall6 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1184.f, 448.f));
		wall6->AddComponent<Collider>();
		wall6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 640.f));
		wall6->GetComponent<Collider>()->SetAffectedCamera(true);

		// Trigger
		Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 640.f));
		trigger1->AddComponent<Collider>();
		trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger1->SetType(Trigger::eTriggertype::Scenechange);
		trigger1->SetScenename(L"JailScene16");

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailScene17::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt((640.f, 360.f));
			SceneManager::LoadScene(L"JailScene18");
		}
		Scene::Update();
	}

	void JailScene17::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene17", 11);
	}
}