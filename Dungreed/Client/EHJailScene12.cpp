#include "EHJailScene12.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"
#include "EHPlayer.h"
#include "EHCanvas.h"
#include "EHFloor.h"
#include "EHTrigger.h"

namespace EH
{
	void JailScene12::Initialize()
	{
		SetSize(Math::Vector2<float>(1280.f, 1088.f));

		BackGround* JailSubBG12 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailSubBG12->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		JailSubBG12->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		Texture* texture = Resources::Load<Texture>(L"JailSubBG", L"..\\Resources\\Dungeon\\JailBackGround\\4\\SubBG.bmp");
		JailSubBG12->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailSubBG12->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailBG12 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG12->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 544.f));
		JailBG12->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 1088.f));
		texture = Resources::Load<Texture>(L"JailBG12", L"..\\Resources\\Dungeon\\JailBackGround\\12\\JailField12.bmp");
		JailBG12->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG12->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// Floor
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 928.f));
		floor1->AddComponent<Collider>();
		floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1280.f, 64.f));
		floor1->GetComponent<Collider>()->SetAffectedCamera(true);
		floor1->SetDownFloor(false);

		// Trigger
		Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 768.f));
		trigger1->AddComponent<Collider>();
		trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger1->SetType(Trigger::eTriggertype::Scenechange);
		trigger1->SetScenename(L"JailScene11");

		Trigger* trigger2 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1244.f, 768.f));
		trigger2->AddComponent<Collider>();
		trigger2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger2->SetType(Trigger::eTriggertype::Scenechange);
		trigger2->SetScenename(L"JailScene13");

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailScene12::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene13");
		}
		Scene::Update();
	}

	void JailScene12::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene12", 11);
	}
}