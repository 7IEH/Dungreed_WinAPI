#include "EHIceScene3.h"
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
	void IceScene3::Initialize()
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

        SetSize(Math::Vector2<float>(1536.f, 720.f));

        BackGround* IceSubBG = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        IceSubBG->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 520.f));
        IceSubBG->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 1040.f));
        Texture* texture = Resources::Load<Texture>(L"IceSubBG", L"..\\Resources\\Dungeon\\IceBackGround\\IceLayer\\BGLayer_0.bmp");
        IceSubBG->GetComponent<SpriteRenderer>()->SetImg(texture);
        IceSubBG->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

        BackGround* IceBG1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        IceBG1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(768.f, 360.f));
        IceBG1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1536.f, 720.f));
        texture = Resources::Load<Texture>(L"IceBG3", L"..\\Resources\\Dungeon\\IceBackGround\\3\\IceScene3.bmp");
        IceBG1->GetComponent<SpriteRenderer>()->SetImg(texture);
        IceBG1->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

        // Floor
        Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(768.f, 560.f));
        floor1->AddComponent<Collider>();
        floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1536.f, 64.f));
        floor1->GetComponent<Collider>()->SetAffectedCamera(true);
        floor1->SetDownFloor(false);

        // Ceil
        Ceil* ceil1 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
        ceil1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(158.f, 240.f));
        ceil1->AddComponent<Collider>();
        ceil1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(316.f, 64.f));
        ceil1->GetComponent<Collider>()->SetAffectedCamera(true);

        Ceil* ceil2 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
        ceil2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(414.f, 112.f));
        ceil2->AddComponent<Collider>();
        ceil2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(188.f, 64.f));
        ceil2->GetComponent<Collider>()->SetAffectedCamera(true);

        Ceil* ceil3 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
        ceil3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(768.f, 48.f));
        ceil3->AddComponent<Collider>();
        ceil3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(512.f, 64.f));
        ceil3->GetComponent<Collider>()->SetAffectedCamera(true);

        Ceil* ceil4 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
        ceil4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1122.f, 112.f));
        ceil4->AddComponent<Collider>();
        ceil4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(188.f, 64.f));
        ceil4->GetComponent<Collider>()->SetAffectedCamera(true);

        Ceil* ceil5 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
        ceil5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1378.f, 240.f));
        ceil5->AddComponent<Collider>();
        ceil5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(316.f, 64.f));
        ceil5->GetComponent<Collider>()->SetAffectedCamera(true);

        // Wall
        Wall* wall1 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(288.f, 172.f));
        wall1->AddComponent<Collider>();
        wall1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 192.f));
        wall1->GetComponent<Collider>()->SetAffectedCamera(true);
        wall1->SetRight(false);

        Wall* wall2 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(480.f, 76.f));
        wall2->AddComponent<Collider>();
        wall2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 128.f));
        wall2->GetComponent<Collider>()->SetAffectedCamera(true);
        wall2->SetRight(false);

        Wall* wall3 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1056.f, 76.f));
        wall3->AddComponent<Collider>();
        wall3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 128.f));
        wall3->GetComponent<Collider>()->SetAffectedCamera(true);
        wall3->SetRight(true);

        Wall* wall4 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1248.f, 172.f));
        wall4->AddComponent<Collider>();
        wall4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 192.f));
        wall4->GetComponent<Collider>()->SetAffectedCamera(true);
        wall4->SetRight(true);

        // Trigger
        Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
        trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 400.f));
        trigger1->AddComponent<Collider>();
        trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
        trigger1->SetType(Trigger::eTriggertype::Scenechange);
        trigger1->SetScenename(L"IceScene4");

        Trigger* trigger2 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
        trigger2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1504.f, 400.f));
        trigger2->AddComponent<Collider>();
        trigger2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
        trigger2->SetType(Trigger::eTriggertype::Scenechange);
        trigger2->SetScenename(L"IceScene2");

        // Steel
        Wall* steel2 = object::Instantiate<Wall>(enums::eLayerType::Steel);
        steel2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(40.f, 404.f));
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
        steel3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1496.f, 404.f));
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
        GiantBat* giantbat1 = object::Instantiate<GiantBat>(enums::eLayerType::Enemy);
        giantbat1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(452.f, 288.f));
        giantbat1->GetComponent<Animator>()->PlayAnimation(L"GiantRightIdle", true);

        RedGiantBat* redgiantbat1 = object::Instantiate<RedGiantBat>(enums::eLayerType::Enemy);
        redgiantbat1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1108.f, 288.f));
        redgiantbat1->GetComponent<Animator>()->PlayAnimation(L"RedGiantRightIdle", true);

        Banshee* banshee1 = object::Instantiate<Banshee>(enums::eLayerType::Enemy);
        banshee1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(780.f, 228.f));
        banshee1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 88.f));
        banshee1->AddComponent<Animator>();
        texture = Resources::Load<Texture>(L"BansheeIdle", L"..\\Resources\\Enemy\\JailField\\Banshee\\Idle\\BansheeIdleSheet.bmp");
        banshee1->GetComponent<Animator>()->CreateAnimation(L"BansheeIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 22.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
        texture = Resources::Load<Texture>(L"BansheeAttack", L"..\\Resources\\Enemy\\JailField\\Banshee\\Attack\\BansheeAttackSheet.bmp");
        banshee1->GetComponent<Animator>()->CreateAnimation(L"BansheeAttack", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 22.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
        banshee1->GetComponent<Animator>()->PlayAnimation(L"BansheeIdle", true);
        banshee1->SetTarget(player);
        banshee1->SetDelayTime(2.f);

        BigGrayIceSkel* biggrayiceskel = object::Instantiate<BigGrayIceSkel>(enums::eLayerType::Enemy);
        Transform* tr = biggrayiceskel->GetComponent<Transform>();
        tr->SetPos(Math::Vector2<float>(644.f, 460.f));
        tr->SetScale(Math::Vector2<float>(132.f, 120.f));
	}

	void IceScene3::Update()
	{
		Scene::Update();
	}

	void IceScene3::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}