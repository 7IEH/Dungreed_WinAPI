#include "EHIceScene8.h"
#include "EHResources.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHFloor.h"
#include "EHCeil.h"
#include "EHWall.h"
#include "EHTrigger.h"
#include "EHPlayer.h"
#include "EHJailArchor.h"
#include "EHJailDog.h"
#include "EHJailWarrior.h"
#include "EHGiantBat.h"
#include "EHRedGiantBat.h"
#include "EHSkelIceMagician.h"
#include "EHBigGrayIceSkel.h"
#include "EHBanshee.h"

namespace EH
{
	void IceScene8::Initialize()
	{
        // Sound
        Sound* BGM = Resources::Load<Sound>(L"IceFieldBGM", L"..\\Resources\\Sound\\BGM\\2.IceField.wav");
        SetBGM(BGM);
        //mEnterSound = Resources::Load<Sound>(L"JailDoorSound", L"..\\Resources\\Sound\\Structure\\JailDoorSound.wav");

        // Player
        Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
        player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 800.f));
        player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

        // SceneChanger Player
        SetPlayer(player);

        SetSize(Math::Vector2<float>(1600.f, 1088.f));

        BackGround* IceSubBG = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        IceSubBG->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 520.f));
        IceSubBG->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 1040.f));
        Texture* texture = Resources::Load<Texture>(L"IceSubBG", L"..\\Resources\\Dungeon\\IceBackGround\\IceLayer\\BGLayer_0.bmp");
        IceSubBG->GetComponent<SpriteRenderer>()->SetImg(texture);
        IceSubBG->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

        BackGround* IceBG1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        IceBG1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(800.f, 544.f));
        IceBG1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1600.f, 1088.f));
        texture = Resources::Load<Texture>(L"IceBG8", L"..\\Resources\\Dungeon\\IceBackGround\\8\\IceScene8.bmp");
        IceBG1->GetComponent<SpriteRenderer>()->SetImg(texture);
        IceBG1->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Floor
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(800.f, 992.f));
		floor1->AddComponent<Collider>();
		floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1600.f, 64.f));
		floor1->GetComponent<Collider>()->SetAffectedCamera(true);
		floor1->SetDownFloor(false);

		Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(226.f, 484.f));
		floor2->AddComponent<Collider>();
		floor2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(188.f, 56.f));
		floor2->GetComponent<Collider>()->SetAffectedCamera(true);
		floor2->SetDownFloor(true);

		Floor* floor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(478.f, 672.f));
		floor3->AddComponent<Collider>();
		floor3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(188.f, 56.f));
		floor3->GetComponent<Collider>()->SetAffectedCamera(true);
		floor3->SetDownFloor(true);

		Floor* floor4 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(810.f, 796.f));
		floor4->AddComponent<Collider>();
		floor4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(188.f, 56.f));
		floor4->GetComponent<Collider>()->SetAffectedCamera(true);
		floor4->SetDownFloor(true);

		Floor* floor5 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1102.f, 672.f));
		floor5->AddComponent<Collider>();
		floor5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(188.f, 56.f));
		floor5->GetComponent<Collider>()->SetAffectedCamera(true);
		floor5->SetDownFloor(true);

		Floor* floor6 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1378.f, 484.f));
		floor6->AddComponent<Collider>();
		floor6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(188.f, 56.f));
		floor6->GetComponent<Collider>()->SetAffectedCamera(true);
		floor6->SetDownFloor(true);

		Floor* floor7 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor7->GetComponent<Transform>()->SetPos(Math::Vector2<float>(830.f, 268.f));
		floor7->AddComponent<Collider>();
		floor7->GetComponent<Collider>()->SetScale(Math::Vector2<float>(188.f, 56.f));
		floor7->GetComponent<Collider>()->SetAffectedCamera(true);
		floor7->SetDownFloor(true);

		// Ceil
		Ceil* ceil1 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(62.f, 672.f));
		ceil1->AddComponent<Collider>();
		ceil1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 64.f));
		ceil1->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil2 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(190.f, 224.f));
		ceil2->AddComponent<Collider>();
		ceil2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 64.f));
		ceil2->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil3 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(318.f, 160.f));
		ceil3->AddComponent<Collider>();
		ceil3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 64.f));
		ceil3->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil4 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(896.f, 96.f));
		ceil4->AddComponent<Collider>();
		ceil4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1024.f, 64.f));
		ceil4->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil5 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1476.f, 160.f));
		ceil5->AddComponent<Collider>();
		ceil5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(128.f, 64.f));
		ceil5->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil6 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1538.f, 672.f));
		ceil6->AddComponent<Collider>();
		ceil6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 64.f));
		ceil6->GetComponent<Collider>()->SetAffectedCamera(true);

		// Wall
		Wall* wall1 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(96.f, 444.f));
		wall1->AddComponent<Collider>();
		wall1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 512.f));
		wall1->GetComponent<Collider>()->SetAffectedCamera(true);
		wall1->SetRight(false);

		Wall* wall2 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(224.f, 188.f));
		wall2->AddComponent<Collider>();
		wall2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 128.f));
		wall2->GetComponent<Collider>()->SetAffectedCamera(true);
		wall2->SetRight(false);

		Wall* wall3 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(352.f, 124.f));
		wall3->AddComponent<Collider>();
		wall3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 128.f));
		wall3->GetComponent<Collider>()->SetAffectedCamera(true);
		wall3->SetRight(false);

		Wall* wall4 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1440.f, 124.f));
		wall4->AddComponent<Collider>();
		wall4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 128.f));
		wall4->GetComponent<Collider>()->SetAffectedCamera(true);
		wall4->SetRight(true);

		Wall* wall5 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1504.f, 412.f));
		wall5->AddComponent<Collider>();
		wall5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 576.f));
		wall5->GetComponent<Collider>()->SetAffectedCamera(true);
		wall5->SetRight(true);

		// Trigger
		Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 832.f));
		trigger1->AddComponent<Collider>();
		trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger1->SetType(Trigger::eTriggertype::Scenechange);
		trigger1->SetScenename(L"IceScene7");

		Trigger* trigger2 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1568.f, 832.f));
		trigger2->AddComponent<Collider>();
		trigger2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger2->SetType(Trigger::eTriggertype::Scenechange);
		trigger2->SetScenename(L"IceScene9");

		Wall* steel2 = object::Instantiate<Wall>(enums::eLayerType::Steel);
		steel2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(40.f, 836.f));
		steel2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 264.f));
		steel2->AddComponent<Collider>();
		steel2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		Animator* ani = steel2->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"SteelRightOpen", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Right\\SteelOpenSheet.bmp");
		ani->CreateAnimation(L"SteelOpen", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 60.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelRightExit", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Right\\SteelExitSheet.bmp");
		ani->CreateAnimation(L"SteelExit", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 60.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelRightIdle", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Right\\SteelIdleSheet.bmp");
		ani->CreateAnimation(L"SteelIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 60.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

		Wall* steel3 = object::Instantiate<Wall>(enums::eLayerType::Steel);
		steel3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1560.f, 836.f));
		steel3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 264.f));
		steel3->AddComponent<Collider>();
		steel3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		steel3->SetRight(true);
		ani = steel3->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"SteelRightOpen", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Right\\SteelOpenSheet.bmp");
		ani->CreateAnimation(L"SteelOpen", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 60.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelRightExit", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Right\\SteelExitSheet.bmp");
		ani->CreateAnimation(L"SteelExit", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 60.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelRightIdle", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Right\\SteelIdleSheet.bmp");
		ani->CreateAnimation(L"SteelIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 60.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

		// Enemy
		JailArchor* archor1 = object::Instantiate<JailArchor>(enums::eLayerType::Enemy);
		archor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1100.f, 572.f));
		archor1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		Collider* col = archor1->AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(128.f, 128.f));
		archor1->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"GreySkelRightIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Right\\GraySkelIdle.bmp");
		archor1->GetComponent<Animator>()->CreateAnimation(L"GreySkelRightIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		texture = Resources::Load<Texture>(L"GreySkelLeftIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Left\\GraySkelIdle.bmp");
		archor1->GetComponent<Animator>()->CreateAnimation(L"GreySkelLeftIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		archor1->GetComponent<Animator>()->PlayAnimation(L"GreySkelRightIdle", true);

		JailArchor* archor2 = object::Instantiate<JailArchor>(enums::eLayerType::Enemy);
		archor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(480.f, 572.f));
		archor2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		col = archor2->AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(128.f, 128.f));
		archor2->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"GreySkelRightIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Right\\GraySkelIdle.bmp");
		archor2->GetComponent<Animator>()->CreateAnimation(L"GreySkelRightIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		texture = Resources::Load<Texture>(L"GreySkelLeftIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Left\\GraySkelIdle.bmp");
		archor2->GetComponent<Animator>()->CreateAnimation(L"GreySkelLeftIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		archor2->GetComponent<Animator>()->PlayAnimation(L"GreySkelRightIdle", true);

		SkelIceMagician* magician1 = object::Instantiate<SkelIceMagician>(enums::eLayerType::Enemy);
		Transform* tr = magician1->GetComponent<Transform>();
		tr->SetPos(Math::Vector2<float>(812.f, 440.f));
		tr->SetScale(Math::Vector2<float>(128.f, 120.f));

		BigGrayIceSkel* biggrayiceskel = object::Instantiate<BigGrayIceSkel>(enums::eLayerType::Enemy);
		tr = biggrayiceskel->GetComponent<Transform>();
		tr->SetPos(Math::Vector2<float>(432.f, 892.f));
		tr->SetScale(Math::Vector2<float>(132.f, 120.f));

		BigGrayIceSkel* biggrayiceskel2 = object::Instantiate<BigGrayIceSkel>(enums::eLayerType::Enemy);
		tr = biggrayiceskel2->GetComponent<Transform>();
		tr->SetPos(Math::Vector2<float>(1160.f, 892.f));
		tr->SetScale(Math::Vector2<float>(132.f, 120.f));
	}

	void IceScene8::Update()
	{
		Scene::Update();
	}

	void IceScene8::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}