#include "EHTownScene.h"
#include "EHImage.h"
#include "EHObject.h"
#include "EHGameObject.h"
#include "EHPlayer.h"

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
        // sky
        Image* Sky = object::Instantiate<Image>(enums::eLayerType::BackGround);
        Sky->GetComponent<Transform>()->SetPos(Math::Vector2<float>(0.f,0.f));
        Sky->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
        Sky->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
        Sky->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(319.f, 179.f));
        Sky->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\TownScene\\Sky_Day.png", L"Sky");
        Sky->GetComponent<SpriteRenderer>()->SetImg(L"Sky");

        // Back
        Image* Back = object::Instantiate<Image>(enums::eLayerType::BackGround);
        Back->GetComponent<Transform>()->SetPos(Math::Vector2<float>(0.f, 152.f));
        Back->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 568.f));
        Back->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
        Back->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(319.f, 141.f));
        Back->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\TownScene\\TownBG_Day.png", L"Back");
        Back->GetComponent<SpriteRenderer>()->SetImg(L"Back");

        // Tree
        Image* Tree = object::Instantiate<Image>(enums::eLayerType::BackGround);
        Tree->GetComponent<Transform>()->SetPos(Math::Vector2<float>(0.f, 440.f));
        Tree->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 280.f));
        Tree->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
        Tree->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(319.f, 94.f));
        Tree->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\TownScene\\TownLayer_Day.png", L"Tree");
        Tree->GetComponent<SpriteRenderer>()->SetImg(L"Tree");

        // HP
        Image* HPBack = object::Instantiate<Image>(enums::eLayerType::UI);
        HPBack->GetComponent<Transform>()->SetPos(Math::Vector2<float>(9.f, 10.f));
        HPBack->GetComponent<Transform>()->SetScale(Math::Vector2<float>(300.f, 66.f));
        HPBack->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
        HPBack->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(74.f, 16.f));
        HPBack->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\UI\\PlayerLifeBack.png", L"HPBack");
        HPBack->GetComponent<SpriteRenderer>()->SetImg(L"HPBack");

        Image* HPBase = object::Instantiate<Image>(enums::eLayerType::UI);
        HPBase->GetComponent<Transform>()->SetPos(Math::Vector2<float>(9.f, 10.f));
        HPBase->GetComponent<Transform>()->SetScale(Math::Vector2<float>(300.f, 66.f));
        HPBase->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
        HPBase->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(74.f, 16.f));
        HPBase->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\UI\\PlayerLifeBase 1.png", L"HPBase");
        HPBase->GetComponent<SpriteRenderer>()->SetImg(L"HPBase");

        // DASH
        Image* DashBase = object::Instantiate<Image>(enums::eLayerType::UI);
        DashBase->GetComponent<Transform>()->SetPos(Math::Vector2<float>(9.f, 80.f));
        DashBase->GetComponent<Transform>()->SetScale(Math::Vector2<float>(252.f, 34.f));
        DashBase->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
        DashBase->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(63.f, 8.f));
        DashBase->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\UI\\DashCountBase.png", L"DashBase");
        DashBase->GetComponent<SpriteRenderer>()->SetImg(L"DashBase");

        // COIN
        Image* Coin = object::Instantiate<Image>(enums::eLayerType::UI);
        Coin->GetComponent<Transform>()->SetPos(Math::Vector2<float>(20.f, 650.f));
        Coin->GetComponent<Transform>()->SetScale(Math::Vector2<float>(17.f, 14.f));
        Coin->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
        Coin->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(17.f, 14.f));
        Coin->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\UI\\Coin.png", L"Coin");
        Coin->GetComponent<SpriteRenderer>()->SetImg(L"Coin");

        // FOOD
        Image* Food = object::Instantiate<Image>(enums::eLayerType::UI);
        Food->GetComponent<Transform>()->SetPos(Math::Vector2<float>(12.f, 676.f));
        Food->GetComponent<Transform>()->SetScale(Math::Vector2<float>(34.f, 28.f));
        Food->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
        Food->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(17.f, 14.f));
        Food->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\UI\\Food.png", L"Food");
        Food->GetComponent<SpriteRenderer>()->SetImg(L"Food");

        // Weapon Swap
        Image* WeaponSlot = object::Instantiate<Image>(enums::eLayerType::UI);
        WeaponSlot->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1140.f, 590.f));
        WeaponSlot->GetComponent<Transform>()->SetScale(Math::Vector2<float>(140.f, 102.f));
        WeaponSlot->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
        WeaponSlot->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(34.f, 24.f));
        WeaponSlot->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\UI\\EquippedWeaponBase.png", L"WeaponSlot");
        WeaponSlot->GetComponent<SpriteRenderer>()->SetImg(L"WeaponSlot");

        Image* WeaponSlot2 = object::Instantiate<Image>(enums::eLayerType::UI);
        WeaponSlot2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1120.f, 606.f));
        WeaponSlot2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(140.f, 102.f));
        WeaponSlot2->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
        WeaponSlot2->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(34.f, 24.f));
        WeaponSlot2->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\UI\\EquippedWeaponBase.png", L"WeaponSlot2");
        WeaponSlot2->GetComponent<SpriteRenderer>()->SetImg(L"WeaponSlot2");

        Image* Minimap = object::Instantiate<Image>(enums::eLayerType::UI);
        Minimap->GetComponent<Transform>()->SetPos(Math::Vector2<float>(930.f, 15.f));
        Minimap->GetComponent<Transform>()->SetScale(Math::Vector2<float>(350.f, 85.f));
        Minimap->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
        Minimap->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(34.f, 24.f));

        Image* Floor1 = object::Instantiate<Image>(enums::eLayerType::BackGround);
        Floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(0.f, 510.f));
        Floor1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(320.f, 120.f));
        Floor1->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(352.f, 0.f));
        Floor1->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(79.f, 30.f));
        Floor1->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\TownScene\\Map.png", L"Floor1");
        Floor1->GetComponent<SpriteRenderer>()->SetImg(L"Floor1");

        Image* Floor2 = object::Instantiate<Image>(enums::eLayerType::BackGround);
        Floor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(320.f, 510.f));
        Floor2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(320.f, 120.f));
        Floor2->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(352.f, 0.f));
        Floor2->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(79.f, 30.f));
        Floor2->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\TownScene\\Map.png", L"Floor2");
        Floor2->GetComponent<SpriteRenderer>()->SetImg(L"Floor2");

        Image* Floor3 = object::Instantiate<Image>(enums::eLayerType::BackGround);
        Floor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 510.f));
        Floor3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(320.f, 120.f));
        Floor3->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(352.f, 0.f));
        Floor3->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(79.f, 30.f));
        Floor3->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\TownScene\\Map.png", L"Floor3");
        Floor3->GetComponent<SpriteRenderer>()->SetImg(L"Floor3");

        Image* Floor4 = object::Instantiate<Image>(enums::eLayerType::BackGround);
        Floor4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(960.f, 510.f));
        Floor4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(320.f, 120.f));
        Floor4->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(352.f, 0.f));
        Floor4->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(79.f, 30.f));
        Floor4->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\TownScene\\Map.png", L"Floor4");
        Floor4->GetComponent<SpriteRenderer>()->SetImg(L"Floor4");

        Image* FloorUnder = object::Instantiate<Image>(enums::eLayerType::BackGround);
        FloorUnder->GetComponent<Transform>()->SetPos(Math::Vector2<float>(0.f, 630.f));
        FloorUnder->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 90.f));
        FloorUnder->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
        FloorUnder->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(1280.f, 90.f));
        FloorUnder->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\TownScene\\Map2.png", L"FloorUnder");
        FloorUnder->GetComponent<SpriteRenderer>()->SetImg(L"FloorUnder");

        // Player
        Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
        player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(300.f, 630.f));
        player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(52.f, 84.f));
        player->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
        player->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(32.f, 32.f));
        player->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\Player\\Basic\\Idle\\CharIdle0.png", L"player");
        player->GetComponent<SpriteRenderer>()->SetImg(L"player");
        player->SetName(L"Player");
    }

    void TownScene::Update()
    {
        if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
        {
            SceneManager::LoadScene(L"TitleScene");
        }
        Scene::Update();
    }

    void TownScene::Render(HDC hdc)
    {
        Scene::Render(hdc);
    }
}