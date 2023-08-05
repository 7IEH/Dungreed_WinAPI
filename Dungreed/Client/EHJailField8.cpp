#include "EHJailField8.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"
#include "EHPlayer.h"
#include "EHCanvas.h"
#include "EHFloor.h"
#include "EHTrigger.h"
#include "EHSlope.h"
#include "EHWall.h"
#include "EHCeil.h"


namespace EH
{
	void JailField8::Initialize()
	{
		SetSize(Math::Vector2<float>(2752.f, 1088.f));
		BackGround* JailBG8 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG8->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1376.f, 544.f));
		JailBG8->GetComponent<Transform>()->SetScale(Math::Vector2<float>(2752.f, 1088.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG8", L"..\\Resources\\Dungeon\\JailBackGround\\8\\JailField8.bmp");
		JailBG8->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG8->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// Floor
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1234.f, 352.f));
		floor1->AddComponent<Collider>();
		floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(2212.f, 64.f));
		floor1->GetComponent<Collider>()->SetAffectedCamera(true);
		floor1->SetDownFloor(false);

		Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1518.f, 672.f));
		floor2->AddComponent<Collider>();
		floor2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(2212.f, 64.f));
		floor2->GetComponent<Collider>()->SetAffectedCamera(true);
		floor2->SetDownFloor(false);

		Floor* floor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(248.f, 1056.f));
		floor3->AddComponent<Collider>();
		floor3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(240.f, 64.f));
		floor3->GetComponent<Collider>()->SetAffectedCamera(true);
		floor3->SetDownFloor(false);

		Floor* floor4 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(522.f, 992.f));
		floor4->AddComponent<Collider>();
		floor4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(180.f, 64.f));
		floor4->GetComponent<Collider>()->SetAffectedCamera(true);
		floor4->SetDownFloor(false);

		Floor* floor5 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1220.f, 1056.f));
		floor5->AddComponent<Collider>();
		floor5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1088.f, 64.f));
		floor5->GetComponent<Collider>()->SetAffectedCamera(true);
		floor5->SetDownFloor(false);

		Floor* floor6 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1888.f, 992.f));
		floor6->AddComponent<Collider>();
		floor6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(120.f, 64.f));
		floor6->GetComponent<Collider>()->SetAffectedCamera(true);
		floor6->SetDownFloor(false);

		Floor* floor7 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor7->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2318.f, 1056.f));
		floor7->AddComponent<Collider>();
		floor7->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1152.f, 64.f));
		floor7->GetComponent<Collider>()->SetAffectedCamera(true);
		floor7->SetDownFloor(true);

		// Ceil
		Ceil* ceil1 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(190.f, 32.f));
		ceil1->AddComponent<Collider>();
		ceil1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 64.f));
		ceil1->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil2 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1572.f, 32.f));
		ceil2->AddComponent<Collider>();
		ceil2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(2112.f, 64.f));
		ceil2->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil3 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(414.f, 416.f));
		ceil3->AddComponent<Collider>();
		ceil3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(572.f, 64.f));
		ceil3->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil4 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1650.f, 416.f));
		ceil4->AddComponent<Collider>();
		ceil4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1372.f, 64.f));
		ceil4->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil5 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1102.f, 736.f));
		ceil5->AddComponent<Collider>();
		ceil5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1372.f, 64.f));
		ceil5->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil6 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2338.f, 736.f));
		ceil6->AddComponent<Collider>();
		ceil6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(572.f, 64.f));
		ceil6->GetComponent<Collider>()->SetAffectedCamera(true);

		// Wall
		Wall* wall1 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(96.f, 512.f));
		wall1->AddComponent<Collider>();
		wall1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 1024.f));
		wall1->GetComponent<Collider>()->SetAffectedCamera(true);
		wall1->SetRight(false);

		Wall* wall2 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2656.f, 512.f));
		wall2->AddComponent<Collider>();
		wall2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 1024.f));
		wall2->GetComponent<Collider>()->SetAffectedCamera(true);

		Wall* wall3 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(224.f, 30.f));
		wall3->AddComponent<Collider>();
		wall3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 60.f));
		wall3->GetComponent<Collider>()->SetAffectedCamera(true);
		wall3->SetRight(false);

		Wall* wall4 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(512.f, 30.f));
		wall4->AddComponent<Collider>();
		wall4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 60.f));
		wall4->GetComponent<Collider>()->SetAffectedCamera(true);

		Wall* wall5 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(672.f, 384.f));
		wall5->AddComponent<Collider>();
		wall5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 120.f));
		wall5->GetComponent<Collider>()->SetAffectedCamera(true);
		wall5->SetRight(false);

		Wall* wall6 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(992.f, 384.f));
		wall6->AddComponent<Collider>();
		wall6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 120.f));
		wall6->GetComponent<Collider>()->SetAffectedCamera(true);

		Wall* wall7 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall7->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2308.f, 384.f));
		wall7->AddComponent<Collider>();
		wall7->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 120.f));
		wall7->GetComponent<Collider>()->SetAffectedCamera(true);
		wall7->SetRight(false);

		Wall* wall8 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall8->GetComponent<Transform>()->SetPos(Math::Vector2<float>(444.f, 704.f));
		wall8->AddComponent<Collider>();
		wall8->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 120.f));
		wall8->GetComponent<Collider>()->SetAffectedCamera(true);

		Wall* wall9 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall9->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1760.f, 704.f));
		wall9->AddComponent<Collider>();
		wall9->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 120.f));
		wall9->GetComponent<Collider>()->SetAffectedCamera(true);
		wall9->SetRight(false);

		Wall* wall10 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall10->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2080.f, 704.f));
		wall10->AddComponent<Collider>();
		wall10->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 120.f));
		wall10->GetComponent<Collider>()->SetAffectedCamera(true);

		Wall* wall11 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall11->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2224.f, 1058.f));
		wall11->AddComponent<Collider>();
		wall11->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 60.f));
		wall11->GetComponent<Collider>()->SetAffectedCamera(true);
		wall11->SetRight(false);

		Wall* wall12 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall12->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2544.f, 1058.f));
		wall12->AddComponent<Collider>();
		wall12->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 60.f));
		wall12->GetComponent<Collider>()->SetAffectedCamera(true);

		// Slope
		Slope* slope1 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(400.f, 992.f));
		slope1->AddComponent<Collider>();
		slope1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope1->GetComponent<Collider>()->SetAffectedCamera(true);
		slope1->SetIntercept(1392.f);
		slope1->SetCorrection(90.f);
		slope1->SetRight(true);
		
		Slope* slope2 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(644.f, 992.f));
		slope2->AddComponent<Collider>();
		slope2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope2->GetComponent<Collider>()->SetAffectedCamera(true);
		slope2->SetIntercept(-348.f);
		slope2->SetCorrection(90.f);

		Slope* slope3 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1796.f, 992.f));
		slope3->AddComponent<Collider>();
		slope3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope3->GetComponent<Collider>()->SetAffectedCamera(true);
		slope3->SetIntercept(2788.f);
		slope3->SetCorrection(90.f);
		slope3->SetRight(true);

		Slope* slope4 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1980.f, 992.f));
		slope4->AddComponent<Collider>();
		slope4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope4->GetComponent<Collider>()->SetAffectedCamera(true);
		slope4->SetIntercept(988.f);
		slope4->SetCorrection(90.f);

		// Trigger
		Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(384.f, 16.f));
		trigger1->AddComponent<Collider>();
		trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 32.f));
		trigger1->SetType(Trigger::eTriggertype::Scenechange);
		trigger1->SetScenename(L"JailScene7");

		Trigger* trigger2 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2384.f, 1068.f));
		trigger2->AddComponent<Collider>();
		trigger2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 32.f));
		trigger2->SetType(Trigger::eTriggertype::Scenechange);
		trigger2->SetScenename(L"JailScene9");

		// SceneChanger Player
		SetPlayer(player);
	}
	void JailField8::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene9");
		} 
		Scene::Update();
	}
	void JailField8::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene8", 10);
	}
}