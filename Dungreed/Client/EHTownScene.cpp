#include "EHTownScene.h"
#include "EHTexture.h"
#include "EHObject.h"
#include "EHGameObject.h"
#include "EHPlayer.h"
#include "EHBackGround.h"
#include "EHResources.h"
#include "EHSound.h"
#include "EHCamera.h"
#include "EHNpc.h"
#include "EHFloor.h"
#include "EHCollisionManager.h"

namespace EH
{
    TownScene::TownScene()
    {
    }

    TownScene::~TownScene()
    {
    }

    void TownScene::Initialize()
    {
        //Sound* pSound = Resources::Load<Sound>(L"TownBGM", L"..\\Resources\\Sound\\0.Town.wav");
        //pSound->Play();

        SetSize(Math::Vector2<float>(7540.f, 1440.f));
        Texture* temp = nullptr;
        // sky
        BackGround* Sky = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Sky->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f,360.f));
        Sky->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
        temp = Resources::Load<Texture>(L"Sky", L"..\\Resources\\TownScene\\Sky_Day.bmp");
        Sky->GetComponent<SpriteRenderer>()->SetImg(temp);
        Sky->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

        // Back
        BackGround* Back = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Back->GetComponent<Transform>()->SetPos(Math::Vector2<float>(3770.f, 720.f));
        Back->GetComponent<Transform>()->SetScale(Math::Vector2<float>(7540.f, 1440.f));
        temp = Resources::Load<Texture>(L"TownBG", L"..\\Resources\\TownScene\\TownBG.bmp");
        Back->GetComponent<SpriteRenderer>()->SetImg(temp);

        // Tree
        BackGround* Tree = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Tree->GetComponent<Transform>()->SetPos(Math::Vector2<float>(3770.f, 720.f));
        Tree->GetComponent<Transform>()->SetScale(Math::Vector2<float>(7540.f, 1440.f));
        temp = Resources::Load<Texture>(L"TownLayer", L"..\\Resources\\TownScene\\TownLayer.bmp");
        Tree->GetComponent<SpriteRenderer>()->SetImg(temp);

        BackGround* Tree1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Tree1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2162.f, 1146.f));
        Tree1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(268.f, 308.f));
        temp = Resources::Load<Texture>(L"Tree1", L"..\\Resources\\TownScene\\Tree1.bmp");
        Tree1->GetComponent<SpriteRenderer>()->SetImg(temp);

        BackGround* TownBackGround = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        TownBackGround->GetComponent<Transform>()->SetPos(Math::Vector2<float>(3770.f, 720.f));
        TownBackGround->GetComponent<Transform>()->SetScale(Math::Vector2<float>(7540.f, 1440.f));
        temp = Resources::Load<Texture>(L"TownBackGround", L"..\\Resources\\TownScene\\TownBackGround.bmp");
        TownBackGround->GetComponent<SpriteRenderer>()->SetImg(temp);
        TownBackGround->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

        // HP
        BackGround* HPBack = object::Instantiate<BackGround>(enums::eLayerType::UI);
        HPBack->GetComponent<Transform>()->SetPos(Math::Vector2<float>(157.f, 42.f));
        HPBack->GetComponent<Transform>()->SetScale(Math::Vector2<float>(296.f, 64.f));
        temp = Resources::Load<Texture>(L"HPBack", L"..\\Resources\\UI\\PlayerLifeBack.png");
        HPBack->GetComponent<SpriteRenderer>()->SetImg(temp);
        HPBack->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

        BackGround* HPBase = object::Instantiate<BackGround>(enums::eLayerType::UI);
        HPBase->GetComponent<Transform>()->SetPos(Math::Vector2<float>(157.f, 42.f));
        HPBase->GetComponent<Transform>()->SetScale(Math::Vector2<float>(296.f, 64.f));
        temp = Resources::Load<Texture>(L"HPBase", L"..\\Resources\\UI\\PlayerLifeBase 1.png");
        HPBase->GetComponent<SpriteRenderer>()->SetImg(temp);
        HPBase->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

        // DASH
        BackGround* DashBase = object::Instantiate<BackGround>(enums::eLayerType::UI);
        DashBase->GetComponent<Transform>()->SetPos(Math::Vector2<float>(135.f, 97.f));
        DashBase->GetComponent<Transform>()->SetScale(Math::Vector2<float>(252.f, 34.f));
        temp = Resources::Load<Texture>(L"DashBase", L"..\\Resources\\UI\\DashCountBase.png");
        DashBase->GetComponent<SpriteRenderer>()->SetImg(temp);
        DashBase->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

        // COIN
        BackGround* Coin = object::Instantiate<BackGround>(enums::eLayerType::UI);
        Coin->GetComponent<Transform>()->SetPos(Math::Vector2<float>(29.f, 657.f));
        Coin->GetComponent<Transform>()->SetScale(Math::Vector2<float>(17.f, 14.f));
        temp = Resources::Load<Texture>(L"CoinUI", L"..\\Resources\\UI\\Coin.png");
        Coin->GetComponent<SpriteRenderer>()->SetImg(temp);
        Coin->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

        // FOOD
        BackGround* Food = object::Instantiate<BackGround>(enums::eLayerType::UI);
        Food->GetComponent<Transform>()->SetPos(Math::Vector2<float>(29.f, 690.f));
        Food->GetComponent<Transform>()->SetScale(Math::Vector2<float>(34.f, 28.f));
        temp = Resources::Load<Texture>(L"FoodUI", L"..\\Resources\\UI\\Food.png");
        Food->GetComponent<SpriteRenderer>()->SetImg(temp);
        Food->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

        // Weapon Swap
        BackGround* WeaponSlot = object::Instantiate<BackGround>(enums::eLayerType::UI);
        WeaponSlot->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1210.f, 641.f));
        WeaponSlot->GetComponent<Transform>()->SetScale(Math::Vector2<float>(140.f, 102.f));
        temp = Resources::Load<Texture>(L"WeaponSlot", L"..\\Resources\\UI\\EquippedWeaponBase.png");
        WeaponSlot->GetComponent<SpriteRenderer>()->SetImg(temp);
        WeaponSlot->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

        BackGround* WeaponSlot2 = object::Instantiate<BackGround>(enums::eLayerType::UI);
        WeaponSlot2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1190.f, 657.f));
        WeaponSlot2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(140.f, 102.f));
        temp = Resources::Load<Texture>(L"WeaponSlot", L"..\\Resources\\UI\\EquippedWeaponBase.png");
        WeaponSlot2->GetComponent<SpriteRenderer>()->SetImg(temp);
        WeaponSlot2->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

        BackGround* Minimap = object::Instantiate<BackGround>(enums::eLayerType::UI);
        Minimap->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1105.f, 58.f));
        Minimap->GetComponent<Transform>()->SetScale(Math::Vector2<float>(350.f, 85.f));
        Minimap->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

        // Town structure
        BackGround* TrainingSchool = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        TrainingSchool->GetComponent<Transform>()->SetPos(Math::Vector2<float>(632.f, 1146.f));
        TrainingSchool->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1080.f, 308.f));
        temp = Resources::Load<Texture>(L"TrainingSchool", L"..\\Resources\\TownScene\\TrainingSchool.bmp");
        TrainingSchool->GetComponent<SpriteRenderer>()->SetImg(temp);

        BackGround* StreetLight1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        StreetLight1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(64.f, 1180.f));
        StreetLight1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(120.f, 240.f));
        temp = Resources::Load<Texture>(L"StreetLight1", L"..\\Resources\\TownScene\\StreetLight.bmp");
        temp->SetWidth(30);
        temp->SetHeight(60);
        StreetLight1->GetComponent<SpriteRenderer>()->SetImg(temp);

        BackGround* StreetLight2 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        StreetLight2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1824.f, 1180.f));
        StreetLight2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(120.f, 240.f));
        temp = Resources::Load<Texture>(L"StreetLight1", L"..\\Resources\\TownScene\\StreetLight.bmp");
        StreetLight2->GetComponent<SpriteRenderer>()->SetImg(temp);

        BackGround* Well1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Well1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(5758.f, 1202.f));
        Well1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(196.f, 196.f));
        temp = Resources::Load<Texture>(L"Well", L"..\\Resources\\TownScene\\Well.bmp");
        Well1->GetComponent<SpriteRenderer>()->SetImg(temp);

        BackGround* DungeonSign1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        DungeonSign1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(3212.f, 1256.f));
        DungeonSign1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 88.f));
        temp = Resources::Load<Texture>(L"DungeonSign", L"..\\Resources\\TownScene\\DungeonSign.bmp");
        DungeonSign1->GetComponent<SpriteRenderer>()->SetImg(temp);

        BackGround* DungeonSign2 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        DungeonSign2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(4392.f, 1256.f));
        DungeonSign2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 88.f));
        temp = Resources::Load<Texture>(L"DungeonSignReverse", L"..\\Resources\\TownScene\\DungeonSignReverse.bmp");
        DungeonSign2->GetComponent<SpriteRenderer>()->SetImg(temp);

        BackGround* Tree2 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Tree2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(5094.f, 1084.f));
        Tree2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(268.f, 308.f));
        temp = Resources::Load<Texture>(L"Tree1", L"..\\Resources\\TownScene\\Tree1.bmp");
        Tree2->GetComponent<SpriteRenderer>()->SetImg(temp);

        BackGround* Tree3 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Tree3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(5626.f, 1178.f));
        Tree3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(204.f, 244.f));
        temp = Resources::Load<Texture>(L"Tree2", L"..\\Resources\\TownScene\\Tree0.bmp");
        Tree3->GetComponent<SpriteRenderer>()->SetImg(temp);

        // °íÃÄ¾ßµÊ
        BackGround* Tree4 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Tree4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(7086.f, 1206.f));
        Tree4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(204.f, 244.f));
        temp = Resources::Load<Texture>(L"Tree2", L"..\\Resources\\TownScene\\Tree0.bmp");
        Tree4->GetComponent<SpriteRenderer>()->SetImg(temp);

        /*BackGround* OneWay1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        OneWay1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1226.f, 205.f));
        OneWay1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(256.f, 64.f));
        temp = Resources::Load<Texture>(L"OneWay", L"..\\Resources\\TownScene\\SecondFloor_OneWay.png");
        temp->SetWidth(64);
        temp->SetHeight(16);
        OneWay1->GetComponent<SpriteRenderer>()->SetImg(temp);*/

        //Npc
        Npc* Commander = object::Instantiate<Npc>(enums::eLayerType::Npc);
        Commander->GetComponent<Transform>()->SetPos(Math::Vector2<float>(638.f, 1250.f));
        Commander->GetComponent<Transform>()->SetScale(Math::Vector2<float>(92.f, 100.f));
        temp = Resources::Load<Texture>(L"Commander0", L"..\\Resources\\NPC\\NPC_CommanderSheet.bmp");
        Commander->AddComponent<Animator>();
        Commander->GetComponent<Animator>()->CreateAnimation(L"CommanderIdle", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(23.f, 25.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
        Commander->GetComponent<Animator>()->PlayAnimation(L"CommanderIdle", true);

        // Player
        Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
        player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(256.f, 500.f));
        player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
        temp = Resources::Load<Texture>(L"PlayerRightIdle", L"..\\Resources\\Player\\Basic\\Idle\\CharRightIdleSheet.bmp");
        Animator* animator = player->AddComponent<Animator>();
        animator->CreateAnimation(L"PlayerRightIdle", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 5, 0.1f);
        animator->PlayAnimation(L"PlayerRightIdle", true);

        temp = Resources::Load<Texture>(L"PlayerRightRun", L"..\\Resources\\Player\\Basic\\Run\\CharRightRunSheet.bmp");
        animator->CreateAnimation(L"PlayerRightRun", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

        temp = Resources::Load<Texture>(L"PlayerRightDie", L"..\\Resources\\Player\\Basic\\Die\\CharRightDie.bmp");
        animator->CreateAnimation(L"PlayerRightDie", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);

        temp = Resources::Load<Texture>(L"PlayerRightJump", L"..\\Resources\\Player\\Basic\\Jump\\CharRightJump.bmp");
        animator->CreateAnimation(L"PlayerRightJump", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);

        // Left
        temp = Resources::Load<Texture>(L"PlayerLeftIdle", L"..\\Resources\\Player\\Basic\\Idle\\CharLeftIdleSheet.bmp");
        animator->CreateAnimation(L"PlayerLeftIdle", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 5, 0.1f);

        temp = Resources::Load<Texture>(L"PlayerLeftRun", L"..\\Resources\\Player\\Basic\\Run\\CharLeftRunSheet.bmp");
        animator->CreateAnimation(L"PlayerLeftRun", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

        temp = Resources::Load<Texture>(L"PlayerLeftDie", L"..\\Resources\\Player\\Basic\\Die\\CharLeftDie.bmp");
        animator->CreateAnimation(L"PlayerLeftDie", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);

        temp = Resources::Load<Texture>(L"PlayerLeftJump", L"..\\Resources\\Player\\Basic\\Jump\\CharLeftJump.bmp");
        animator->CreateAnimation(L"PlayerLeftJump", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
        player->AddComponent<Collider>();
        player->GetComponent<Collider>()->SetScale(Math::Vector2<float>(128.f, 128.f));
        player->GetComponent<Animator>()->SetAffectedCamera(true);
        player->GetComponent<Collider>()->SetAffectedCamera(true);
    
        Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(3768.f, 1332.f));
        floor1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(7536.f, 64.f));
        floor1->AddComponent<Collider>();
        floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(7536.f, 64.f));
        floor1->GetComponent<Collider>()->SetAffectedCamera(true);
        
        CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Floor,true);
        Camera::SetTarget(player);
    }

    void TownScene::Update()
    {
        if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
        {
            Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
            SceneManager::LoadScene(L"JailScene1");
        }
        Scene::Update();
    }

    void TownScene::Render(HDC hdc)
    {
        Scene::Render(hdc);
    }
}