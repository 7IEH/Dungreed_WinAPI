#include "EHJailField5.h"
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


namespace EH
{
	void JailField5::Initialize()
	{
		Sound* BGM = Resources::Load<Sound>(L"JailFieldBGM", L"..\\Resources\\Sound\\BGM\\1.JailField.wav");
		SetBGM(BGM);

		SetSize(Math::Vector2<float>(1280.f,720.f));
		BackGround* JailBG5 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		JailBG5->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG5", L"..\\Resources\\Dungeon\\JailBackGround\\5\\JailField5.bmp");
		JailBG5->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG5->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// Ceil
		Ceil* ceil1 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(192.f, 100.f));
		ceil1->AddComponent<Collider>();
		ceil1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(128.f, 64.f));
		ceil1->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil2 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(642.f, 164.f));
		ceil2->AddComponent<Collider>();
		ceil2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(764.f, 64.f));
		ceil2->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil3 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1092.f, 100.f));
		ceil3->AddComponent<Collider>();
		ceil3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(128.f, 64.f));
		ceil3->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil4 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1218.f, 284.f));
		ceil4->AddComponent<Collider>();
		ceil4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 64.f));
		ceil4->GetComponent<Collider>()->SetAffectedCamera(true);

		// Wall
		Wall* wall1 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(96.f, 320.f));
		wall1->AddComponent<Collider>();
		wall1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 504.f));
		wall1->GetComponent<Collider>()->SetAffectedCamera(true);
		wall1->SetRight(false);

		Wall* wall2 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(288.f, 130.f));
		wall2->AddComponent<Collider>();
		wall2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 124.f));
		wall2->GetComponent<Collider>()->SetAffectedCamera(true);

		Wall* wall3 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(996.f, 130.f));
		wall3->AddComponent<Collider>();
		wall3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 124.f));
		wall3->GetComponent<Collider>()->SetAffectedCamera(true);
		wall3->SetRight(false);

		Wall* wall4 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1184.f, 190.f));
		wall4->AddComponent<Collider>();
		wall4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 244.f));
		wall4->GetComponent<Collider>()->SetAffectedCamera(true);

		// Floor
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(704.f, 604.f));
		floor1->AddComponent<Collider>();
		floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1152.f, 64.f));
		floor1->GetComponent<Collider>()->SetAffectedCamera(true);
		floor1->SetDownFloor(false);

		// Trigger
		Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1244.f, 444.f));
		trigger1->AddComponent<Collider>();
		trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger1->SetType(Trigger::eTriggertype::Scenechange);
		trigger1->SetScenename(L"JailScene4");

		Trigger* trigger2 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(688.f, 540.f));
		trigger2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(84.f, 64.f));
		trigger2->AddComponent<Collider>();
		trigger2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(84.f, 64.f));
		trigger2->SetType(Trigger::eTriggertype::Tresure);
		Animator* ani = trigger2->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"OpenTresure", L"..\\Resources\\Item\\Chest\\GoldTresureOpened.bmp");
		ani->CreateAnimation(L"OpenTresure", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(21.f, 16.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		texture = Resources::Load<Texture>(L"CloseTresure", L"..\\Resources\\Item\\Chest\\GoldTresureClosed.bmp");
		ani->CreateAnimation(L"CloseTresure", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(21.f, 16.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		ani->PlayAnimation(L"CloseTresure", false);

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailField5::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene6");
		}
		Scene::Update();
	}

	void JailField5::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene5", 10);
	}
}