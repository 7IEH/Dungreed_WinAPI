#include "EHIceScene5.h"
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
	void IceScene5::Initialize()
	{
        // Sound
        Sound* BGM = Resources::Load<Sound>(L"IceFieldBGM", L"..\\Resources\\Sound\\BGM\\2.IceField.wav");
        SetBGM(BGM);
        //mEnterSound = Resources::Load<Sound>(L"JailDoorSound", L"..\\Resources\\Sound\\Structure\\JailDoorSound.wav");

        // Player
        Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
        player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(820.f, 300.f));
        player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

        // SceneChanger Player
        SetPlayer(player);

        SetSize(Math::Vector2<float>(1280.f, 896.f));

        BackGround* IceSubBG = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        IceSubBG->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 520.f));
        IceSubBG->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 1040.f));
        Texture* texture = Resources::Load<Texture>(L"IceSubBG", L"..\\Resources\\Dungeon\\IceBackGround\\IceLayer\\BGLayer_0.bmp");
        IceSubBG->GetComponent<SpriteRenderer>()->SetImg(texture);
        IceSubBG->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

        BackGround* IceBG1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        IceBG1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 448.f));
        IceBG1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 896.f));
        texture = Resources::Load<Texture>(L"IceBG5", L"..\\Resources\\Dungeon\\IceBackGround\\5\\IceScene5.bmp");
        IceBG1->GetComponent<SpriteRenderer>()->SetImg(texture);
        IceBG1->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

        // Floor
        Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(576.f, 800.f));
        floor1->AddComponent<Collider>();
        floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1152.f, 64.f));
        floor1->GetComponent<Collider>()->SetAffectedCamera(true);
        floor1->SetDownFloor(false);

        Floor* floor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(246.f, 612.f));
        floor3->AddComponent<Collider>();
        floor3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 56.f));
        floor3->GetComponent<Collider>()->SetAffectedCamera(true);
        floor3->SetDownFloor(true);

        Floor* floor4 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1030.f, 608.f));
        floor4->AddComponent<Collider>();
        floor4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 56.f));
        floor4->GetComponent<Collider>()->SetAffectedCamera(true);
        floor4->SetDownFloor(true);

        Floor* floor5 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 544.f));
        floor5->AddComponent<Collider>();
        floor5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 64.f));
        floor5->GetComponent<Collider>()->SetAffectedCamera(true);
        floor5->SetDownFloor(true);

        Floor* floor6 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(630.f, 336.f));
        floor6->AddComponent<Collider>();
        floor6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(188.f, 56.f));
        floor6->GetComponent<Collider>()->SetAffectedCamera(true);
        floor6->SetDownFloor(true);

        Floor* floor7 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor7->GetComponent<Transform>()->SetPos(Math::Vector2<float>(448.f, 480.f));
        floor7->AddComponent<Collider>();
        floor7->GetComponent<Collider>()->SetScale(Math::Vector2<float>(128.f, 64.f));
        floor7->GetComponent<Collider>()->SetAffectedCamera(true);
        floor7->SetDownFloor(true);

        Floor* floor8 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor8->GetComponent<Transform>()->SetPos(Math::Vector2<float>(832.f, 480.f));
        floor8->AddComponent<Collider>();
        floor8->GetComponent<Collider>()->SetScale(Math::Vector2<float>(128.f, 64.f));
        floor8->GetComponent<Collider>()->SetAffectedCamera(true);
        floor8->SetDownFloor(true);

        // Ceil
        Ceil* ceil1 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
        ceil1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(318.f, 96.f));
        ceil1->AddComponent<Collider>();
        ceil1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(380.f, 64.f));
        ceil1->GetComponent<Collider>()->SetAffectedCamera(true);

        Ceil* ceil2 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
        ceil2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(962.f, 96.f));
        ceil2->AddComponent<Collider>();
        ceil2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(380.f, 64.f));
        ceil2->GetComponent<Collider>()->SetAffectedCamera(true);

        Ceil* ceil3 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
        ceil3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 608.f));
        ceil3->AddComponent<Collider>();
        ceil3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(504.f, 64.f));
        ceil3->GetComponent<Collider>()->SetAffectedCamera(true);

        Ceil* ceil4 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
        ceil4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(62.f, 480.f));
        ceil4->AddComponent<Collider>();
        ceil4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 64.f));
        ceil4->GetComponent<Collider>()->SetAffectedCamera(true);

        // Wall
        Wall* wall1 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(96.f, 284.f));
        wall1->AddComponent<Collider>();
        wall1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 448.f));
        wall1->GetComponent<Collider>()->SetAffectedCamera(true);
        wall1->SetRight(false);

        Wall* wall2 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(480.f, 62.f));
        wall2->AddComponent<Collider>();
        wall2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 124.f));
        wall2->GetComponent<Collider>()->SetAffectedCamera(true);
        wall2->SetRight(false);

        Wall* wall3 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(800.f, 62.f));
        wall3->AddComponent<Collider>();
        wall3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 124.f));
        wall3->GetComponent<Collider>()->SetAffectedCamera(true);
        wall3->SetRight(true);

        Wall* wall4 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1184.f, 476.f));
        wall4->AddComponent<Collider>();
        wall4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 704.f));
        wall4->GetComponent<Collider>()->SetAffectedCamera(true);
        wall4->SetRight(true);

        Wall* wall5 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(800.f, 834.f));
        wall5->AddComponent<Collider>();
        wall5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 124.f));
        wall5->GetComponent<Collider>()->SetAffectedCamera(true);
        wall5->SetRight(true);

        Wall* wall6 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(480.f, 834.f));
        wall6->AddComponent<Collider>();
        wall6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 124.f));
        wall6->GetComponent<Collider>()->SetAffectedCamera(true);
        wall6->SetRight(false);

        Wall* wall7 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall7->GetComponent<Transform>()->SetPos(Math::Vector2<float>(416.f, 544.f));
        wall7->AddComponent<Collider>();
        wall7->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 184.f));
        wall7->GetComponent<Collider>()->SetAffectedCamera(true);
        wall7->SetRight(true);

        Wall* wall8 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall8->GetComponent<Transform>()->SetPos(Math::Vector2<float>(480.f, 516.f));
        wall8->AddComponent<Collider>();
        wall8->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 128.f));
        wall8->GetComponent<Collider>()->SetAffectedCamera(true);
        wall8->SetRight(false);

        Wall* wall9 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall9->GetComponent<Transform>()->SetPos(Math::Vector2<float>(800.f, 516.f));
        wall9->AddComponent<Collider>();
        wall9->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 128.f));
        wall9->GetComponent<Collider>()->SetAffectedCamera(true);
        wall9->SetRight(true);

        Wall* wall10 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall10->GetComponent<Transform>()->SetPos(Math::Vector2<float>(864.f, 544.f));
        wall10->AddComponent<Collider>();
        wall10->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 184.f));
        wall10->GetComponent<Collider>()->SetAffectedCamera(true);
        wall10->SetRight(false);

        // Trigger
        Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
        trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 640.f));
        trigger1->AddComponent<Collider>();
        trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
        trigger1->SetType(Trigger::eTriggertype::Scenechange);
        trigger1->SetScenename(L"IceScene12");

        Trigger* trigger2 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
        trigger2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 32.f));
        trigger2->AddComponent<Collider>();
        trigger2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 64.f));
        trigger2->SetType(Trigger::eTriggertype::Scenechange);
        trigger2->SetScenename(L"IceScene2");

        Trigger* trigger3 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
        trigger3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 864.f));
        trigger3->AddComponent<Collider>();
        trigger3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 64.f));
        trigger3->SetType(Trigger::eTriggertype::Scenechange);
        trigger3->SetScenename(L"IceScene6");

        // Steel
        Ceil* steel1 = object::Instantiate<Ceil>(enums::eLayerType::Steel);
        steel1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(644.f, 40.f));
        steel1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(264.f, 80.f));
        steel1->AddComponent<Collider>();
        steel1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 64.f));
        Animator* ani = steel1->AddComponent<Animator>();
        texture = Resources::Load<Texture>(L"SteelOpen", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Ceil\\SteelOpenSheet2.bmp");
        ani->CreateAnimation(L"SteelOpen", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(66.f, 20.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
        texture = Resources::Load<Texture>(L"SteelExit", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Ceil\\SteelExitSheet.bmp");
        ani->CreateAnimation(L"SteelExit", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(66.f, 20.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
        texture = Resources::Load<Texture>(L"SteelIdle", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Ceil\\SteelIdleSheet.bmp");
        ani->CreateAnimation(L"SteelIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(66.f, 20.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

        Wall* steel2 = object::Instantiate<Wall>(enums::eLayerType::Steel);
        steel2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(40.f, 644.f));
        steel2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 264.f));
        steel2->AddComponent<Collider>();
        steel2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
        ani = steel2->AddComponent<Animator>();
        texture = Resources::Load<Texture>(L"SteelRightOpen", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Right\\SteelOpenSheet.bmp");
        ani->CreateAnimation(L"SteelOpen", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 60.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
        texture = Resources::Load<Texture>(L"SteelRightExit", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Right\\SteelExitSheet.bmp");
        ani->CreateAnimation(L"SteelExit", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 60.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
        texture = Resources::Load<Texture>(L"SteelRightIdle", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Right\\SteelIdleSheet.bmp");
        ani->CreateAnimation(L"SteelIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 60.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

        Floor* steel4 = object::Instantiate<Floor>(enums::eLayerType::Steel);
        steel4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(644.f, 856.f));
        steel4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(264.f, 80.f));
        steel4->AddComponent<Collider>();
        steel4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 64.f));
        ani = steel4->AddComponent<Animator>();
        texture = Resources::Load<Texture>(L"SteelFloorOpen", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Floor\\SteelOpenSheet.bmp");
        ani->CreateAnimation(L"SteelOpen", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(66.f, 20.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
        texture = Resources::Load<Texture>(L"SteelFloorExit", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Floor\\SteelExitSheet.bmp");
        ani->CreateAnimation(L"SteelExit", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(66.f, 20.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
        texture = Resources::Load<Texture>(L"SteelFloorIdle", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Floor\\SteelIdleSheet.bmp");
        ani->CreateAnimation(L"SteelIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(66.f, 20.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

        // Enemy
        SkelIceMagician* magician1 = object::Instantiate<SkelIceMagician>(enums::eLayerType::Enemy);
        Transform* tr = magician1->GetComponent<Transform>();
        tr->SetPos(Math::Vector2<float>(636.f, 212.f));
        tr->SetScale(Math::Vector2<float>(128.f, 120.f));

        JailArchor* archor1 = object::Instantiate<JailArchor>(enums::eLayerType::Enemy);
        archor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(248.f, 520.f));
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
        archor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1024.f, 516.f));
        archor2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
        col = archor2->AddComponent<Collider>();
        col->SetScale(Math::Vector2<float>(128.f, 128.f));
        archor2->AddComponent<Animator>();
        texture = Resources::Load<Texture>(L"GreySkelRightIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Right\\GraySkelIdle.bmp");
        archor2->GetComponent<Animator>()->CreateAnimation(L"GreySkelRightIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
        texture = Resources::Load<Texture>(L"GreySkelLeftIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Left\\GraySkelIdle.bmp");
        archor2->GetComponent<Animator>()->CreateAnimation(L"GreySkelLeftIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
        archor2->GetComponent<Animator>()->PlayAnimation(L"GreySkelRightIdle", true);
	}

	void IceScene5::Update()
	{
		Scene::Update();
	}

	void IceScene5::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}