#include "EHJailScene4.h"
#include "EHSceneManager.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"
#include "EHPlayer.h"
#include "EHFloor.h"
#include "EHTrigger.h"
#include "EHCanvas.h"

namespace EH
{
	void JailScene4::Initialize()
	{
		SetSize(Math::Vector2<float>(1472.f, 1088.f));
		BackGround* JailSubBG4 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailSubBG4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		JailSubBG4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		Texture* texture = Resources::Load<Texture>(L"JailSubBG", L"..\\Resources\\Dungeon\\JailBackGround\\4\\SubBG.bmp");
		JailSubBG4->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailSubBG4->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailBG4 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(736.f, 544.f));
		JailBG4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1472.f, 1088.f));
		texture = Resources::Load<Texture>(L"JailBG4", L"..\\Resources\\Dungeon\\JailBackGround\\4\\JailField4.bmp");
		JailBG4->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG4->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Floor
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(736.f, 992.f));
		floor1->AddComponent<Collider>();
		floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1472.f, 64.f));
		floor1->GetComponent<Collider>()->SetAffectedCamera(true);
		floor1->SetDownFloor(false);

		// Trigger
		Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 832.f));
		trigger1->AddComponent<Collider>();
		trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger1->SetType(Trigger::eTriggertype::Scenechange);
		trigger1->SetScenename(L"JailScene5");

		Trigger* trigger2 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1436.f, 832.f));
		trigger2->AddComponent<Collider>();
		trigger2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger2->SetType(Trigger::eTriggertype::Scenechange);
		trigger2->SetScenename(L"JailScene3");

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailScene4::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene5");
		}
		Scene::Update();
	}

	void JailScene4::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene4", 10);
	}
}