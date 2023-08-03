#include "EHJailScene9.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"
#include "EHPlayer.h"
#include "EHCanvas.h"
#include "EHTrigger.h"
#include "EHFloor.h"
#include "EHSlope.h"

namespace EH
{
	void JailScene9::Initialize()
	{
		SetSize(Math::Vector2<float>(3136.f,896.f));
		BackGround* JailBG9 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG9->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1568.f, 448.f));
		JailBG9->GetComponent<Transform>()->SetScale(Math::Vector2<float>(3136.f, 896.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG9", L"..\\Resources\\Dungeon\\JailBackGround\\9\\JailField9.bmp");
		JailBG9->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG9->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// Floor
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(304.f, 800.f));
		floor1->AddComponent<Collider>();
		floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(352.f, 64.f));
		floor1->GetComponent<Collider>()->SetAffectedCamera(true);
		floor1->SetDownFloor(false);

		Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1568.f, 480.f));
		floor2->AddComponent<Collider>();
		floor2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1528.f, 64.f));
		floor2->GetComponent<Collider>()->SetAffectedCamera(true);
		floor2->SetDownFloor(false);

		Floor* floor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2830.f, 800.f));
		floor3->AddComponent<Collider>();
		floor3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(356.f, 64.f));
		floor3->GetComponent<Collider>()->SetAffectedCamera(true);
		floor3->SetDownFloor(false);

		Floor* floor4 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1564.f, 800.f));
		floor4->AddComponent<Collider>();
		floor4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1272.f, 64.f));
		floor4->GetComponent<Collider>()->SetAffectedCamera(true);
		floor4->SetDownFloor(false);

		// Slope1
		Slope* slope1 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(512.f, 736.f));
		slope1->AddComponent<Collider>();
		slope1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope1->GetComponent<Collider>()->SetAffectedCamera(true);
		slope1->SetIntercept(1248.f);
		slope1->SetCorrection(90.f);
		slope1->SetRight(true);

		Slope* slope2 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(576.f, 672.f));
		slope2->AddComponent<Collider>();
		slope2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope2->GetComponent<Collider>()->SetAffectedCamera(true);
		slope2->SetIntercept(1248.f);
		slope2->SetCorrection(90.f);
		slope2->SetRight(true);

		Slope* slope3 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 608.f));
		slope3->AddComponent<Collider>();
		slope3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope3->GetComponent<Collider>()->SetAffectedCamera(true);
		slope3->SetIntercept(1248.f);
		slope3->SetCorrection(90.f);
		slope3->SetRight(true);

		Slope* slope4 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(704.f, 544.f));
		slope4->AddComponent<Collider>();
		slope4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope4->GetComponent<Collider>()->SetAffectedCamera(true);
		slope4->SetIntercept(1248.f);
		slope4->SetCorrection(90.f);
		slope4->SetRight(true);

		Slope* slope5 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(768.f, 480.f));
		slope5->AddComponent<Collider>();
		slope5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope5->GetComponent<Collider>()->SetAffectedCamera(true);
		slope5->SetIntercept(1248.f);
		slope5->SetCorrection(90.f);
		slope5->SetRight(true);

		// Slope2
		Slope* slope6 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2364.f, 480.f));
		slope6->AddComponent<Collider>();
		slope6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope6->GetComponent<Collider>()->SetAffectedCamera(true);
		slope6->SetIntercept(1884.f);
		slope6->SetCorrection(90.f);

		Slope* slope7 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope7->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2428.f, 544.f));
		slope7->AddComponent<Collider>();
		slope7->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope7->GetComponent<Collider>()->SetAffectedCamera(true);
		slope7->SetIntercept(1884.f);
		slope7->SetCorrection(90.f);

		Slope* slope8 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope8->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2492.f, 608.f));
		slope8->AddComponent<Collider>();
		slope8->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope8->GetComponent<Collider>()->SetAffectedCamera(true);
		slope8->SetIntercept(1884.f);
		slope8->SetCorrection(90.f);

		Slope* slope9 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope9->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2556.f, 672.f));
		slope9->AddComponent<Collider>();
		slope9->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope9->GetComponent<Collider>()->SetAffectedCamera(true);
		slope9->SetIntercept(1884.f);
		slope9->SetCorrection(90.f);

		Slope* slope10 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope10->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2620.f, 736.f));
		slope10->AddComponent<Collider>();
		slope10->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope10->GetComponent<Collider>()->SetAffectedCamera(true);
		slope10->SetIntercept(1884.f);
		slope10->SetCorrection(90.f);

		// Trigger
		Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1472.f, 32.f));
		trigger1->AddComponent<Collider>();
		trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 64.f));
		trigger1->SetType(Trigger::eTriggertype::Scenechange);
		trigger1->SetScenename(L"JailScene8");

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailScene9::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene10");
		}
		Scene::Update();
	}

	void JailScene9::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene9", 10);
	}
}