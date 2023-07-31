#include "EHJailScene1.h"
#include "EHObject.h"
#include "EHBackGround.h"
#include "EHResources.h"
#include "EHCollisionManager.h"
#include "EHPlayer.h"
#include "EHFloor.h"
#include "EHTrigger.h"
#include "EHCamera.h"

namespace EH
{
	void JailScene1::Initialize()
	{
		SetSize(Math::Vector2<float>(1280.f, 720.f));

		BackGround* JailBG1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		JailBG1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG1", L"..\\Resources\\Dungeon\\JailBackGround\\1\\JailField1.bmp");
		JailBG1->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG1->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// SceneChanger Player
		SetPlayer(player);

		// Floor
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(638.f, 620.f));
		floor1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1012.f, 64.f));
		floor1->AddComponent<Collider>();
		floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1012.f, 64.f));
		floor1->GetComponent<Collider>()->SetAffectedCamera(true);
		floor1->SetDownFloor(false);

		Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1210.f, 556.f));
		floor2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(140.f, 64.f));
		floor2->AddComponent<Collider>();
		floor2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(140.f, 64.f));
		floor2->GetComponent<Collider>()->SetAffectedCamera(true);
		floor2->SetDownFloor(false);

		// Trigger
		Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(832.f,112.f));
		trigger1->AddComponent<Collider>();
		trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f,64.f));
		trigger1->SetType(Trigger::eTriggertype::Scenechange);
		trigger1->SetScenename(L"JailScene2");

		Trigger* trigger2 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1244.f,400.f));
		trigger2->AddComponent<Collider>();
		trigger2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f,256.f));
		trigger2->SetType(Trigger::eTriggertype::Scenechange);
		trigger2->SetScenename(L"JailBossScene");


		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Trigger, true);
	}

	void JailScene1::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene2");
		}
		Scene::Update();
	}

	void JailScene1::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene1", 10);
	}
}
