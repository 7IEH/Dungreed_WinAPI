#include "EHJailScene12.h"
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
#include "EHRedGiantBat.h"
#include "EHJailDog.h"

namespace EH
{
	void JailScene12::Initialize()
	{
		Sound* BGM = Resources::Load<Sound>(L"JailFieldBGM", L"..\\Resources\\Sound\\BGM\\1.JailField.wav");
		SetBGM(BGM);

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
		floor1->SetDownFloor(true);

		// Ceil
		Ceil* ceil1 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(30.f, 608.f));
		ceil1->AddComponent<Collider>();
		ceil1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(60.f, 64.f));
		ceil1->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil2 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 32.f));
		ceil2->AddComponent<Collider>();
		ceil2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1152.f, 64.f));
		ceil2->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil3 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1250.f, 608.f));
		ceil3->AddComponent<Collider>();
		ceil3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(60.f, 64.f));
		ceil3->GetComponent<Collider>()->SetAffectedCamera(true);

		// Wall
		Wall* wall1 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 318.f));
		wall1->AddComponent<Collider>();
		wall1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 636.f));
		wall1->GetComponent<Collider>()->SetAffectedCamera(true);
		wall1->SetRight(false);

		Wall* wall2 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1248, 318.f));
		wall2->AddComponent<Collider>();
		wall2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 636.f));
		wall2->GetComponent<Collider>()->SetAffectedCamera(true);

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

		// Steel
		Wall* steel2 = object::Instantiate<Wall>(enums::eLayerType::Steel);
		steel2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 768.f));
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
		steel3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1244.f, 768.f));
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

		JailDog* dog1 = object::Instantiate<JailDog>(enums::eLayerType::Enemy);
		dog1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(272.f, 852.f));
		dog1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 72.f));
		dog1->GetComponent<Animator>()->PlayAnimation(L"SkelDogRightIdle", true);

		JailDog* dog2 = object::Instantiate<JailDog>(enums::eLayerType::Enemy);
		dog2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(412.f, 852.f));
		dog2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 72.f));
		dog2->GetComponent<Animator>()->PlayAnimation(L"SkelDogRightIdle", true);

		JailDog* dog3 = object::Instantiate<JailDog>(enums::eLayerType::Enemy);
		dog3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(904.f, 852.f));
		dog3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 72.f));
		dog3->GetComponent<Animator>()->PlayAnimation(L"SkelDogRightIdle", true);

		JailDog* dog4 = object::Instantiate<JailDog>(enums::eLayerType::Enemy);
		dog4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1028.f, 852.f));
		dog4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 72.f));
		dog4->GetComponent<Animator>()->PlayAnimation(L"SkelDogRightIdle", true);

		RedGiantBat* redgiantbat1 = object::Instantiate<RedGiantBat>(enums::eLayerType::Enemy);
		redgiantbat1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(668.f, 528.f));
		redgiantbat1->GetComponent<Animator>()->PlayAnimation(L"RedGiantRightIdle", true);

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