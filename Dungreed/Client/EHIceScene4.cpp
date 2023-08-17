#include "EHIceScene4.h"
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
	void IceScene4::Initialize()
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

        SetSize(Math::Vector2<float>(1280.f, 720.f));

        BackGround* IceSubBG = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        IceSubBG->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 520.f));
        IceSubBG->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 1040.f));
        Texture* texture = Resources::Load<Texture>(L"IceSubBG", L"..\\Resources\\Dungeon\\IceBackGround\\IceLayer\\BGLayer_0.bmp");
        IceSubBG->GetComponent<SpriteRenderer>()->SetImg(texture);
        IceSubBG->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

        BackGround* IceBG1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        IceBG1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
        IceBG1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
        texture = Resources::Load<Texture>(L"IceBG4", L"..\\Resources\\Dungeon\\IceBackGround\\4\\IceScene4.bmp");
        IceBG1->GetComponent<SpriteRenderer>()->SetImg(texture);
        IceBG1->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

        // Floor
        Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(672.f, 624.f));
        floor1->AddComponent<Collider>();
        floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1216.f, 64.f));
        floor1->GetComponent<Collider>()->SetAffectedCamera(true);
        floor1->SetDownFloor(false);

        // Ceil
        Ceil* ceil1 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
        ceil1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(672.f, 48.f));
        ceil1->AddComponent<Collider>();
        ceil1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1088.f, 64.f));
        ceil1->GetComponent<Collider>()->SetAffectedCamera(true);

        Ceil* ceil2 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
        ceil2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1218.f, 304.f));
        ceil2->AddComponent<Collider>();
        ceil2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 64.f));
        ceil2->GetComponent<Collider>()->SetAffectedCamera(true);

        // Wall
        Wall* wall1 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(96.f, 364.f));
        wall1->AddComponent<Collider>();
        wall1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 576.f));
        wall1->GetComponent<Collider>()->SetAffectedCamera(true);
        wall1->SetRight(false);

        Wall* wall2 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1184.f, 204.f));
        wall2->AddComponent<Collider>();
        wall2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
        wall2->GetComponent<Collider>()->SetAffectedCamera(true);
        wall2->SetRight(true);

        // Trigger
        Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
        trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1248.f, 464.f));
        trigger1->AddComponent<Collider>();
        trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
        trigger1->SetType(Trigger::eTriggertype::Scenechange);
        trigger1->SetScenename(L"IceScene3");

        // Steel
        Wall* steel2 = object::Instantiate<Wall>(enums::eLayerType::Steel);
        steel2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1240.f, 468.f));
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

        GiantBat* giantbat1 = object::Instantiate<GiantBat>(enums::eLayerType::Enemy);
        giantbat1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(648.f, 288.f));
        giantbat1->GetComponent<Animator>()->PlayAnimation(L"GiantRightIdle", true);

        JailWarrior* warrior1 = object::Instantiate<JailWarrior>(enums::eLayerType::Enemy);
        warrior1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(448.f, 520.f));
        warrior1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
        Collider* col = warrior1->AddComponent<Collider>();
        col->SetScale(Math::Vector2<float>(128.f, 128.f));
        warrior1->GetComponent<Animator>()->PlayAnimation(L"GreySkelRightIdle", true);

        JailWarrior* warrior2 = object::Instantiate<JailWarrior>(enums::eLayerType::Enemy);
        warrior2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(860.f, 520.f));
        warrior2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
        col = warrior2->AddComponent<Collider>();
        col->SetScale(Math::Vector2<float>(128.f, 128.f));
        warrior2->GetComponent<Animator>()->PlayAnimation(L"GreySkelRightIdle", true);
	}

	void IceScene4::Update()
	{
		Scene::Update();
	}

	void IceScene4::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}
