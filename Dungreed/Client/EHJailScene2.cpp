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
