#include "EHTownScene.h"
#include "EHTexture.h"
#include "EHObject.h"
#include "EHGameObject.h"
#include "EHPlayer.h"
#include "EHBackGround.h"
#include "EHResources.h"

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
        Texture* temp = nullptr;
        // sky
        BackGround* Sky = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Sky->GetComponent<Transform>()->SetPos(Math::Vector2<float>(0.f,0.f));
        Sky->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
        temp = Resources::Load<Texture>(L"Sky", L"..\\Resources\\TownScene\\Sky_Day.png");
        Sky->GetComponent<SpriteRenderer>()->SetImg(temp);

        // Back
        BackGround* Back = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Back->GetComponent<Transform>()->SetPos(Math::Vector2<float>(0.f, 152.f));
        Back->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 568.f));
        temp = Resources::Load<Texture>(L"Back", L"..\\Resources\\TownScene\\TownBG_Day.png");
        Back->GetComponent<SpriteRenderer>()->SetImg(temp);

        // Tree
        BackGround* Tree = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Tree->GetComponent<Transform>()->SetPos(Math::Vector2<float>(0.f, 440.f));
        Tree->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 280.f));
        temp = Resources::Load<Texture>(L"TownTree", L"..\\Resources\\TownScene\\TownLayer_Day.png");
        Tree->GetComponent<SpriteRenderer>()->SetImg(temp);

        // HP
        BackGround* HPBack = object::Instantiate<BackGround>(enums::eLayerType::UI);
        HPBack->GetComponent<Transform>()->SetPos(Math::Vector2<float>(9.f, 10.f));
        HPBack->GetComponent<Transform>()->SetScale(Math::Vector2<float>(300.f, 66.f));
        temp = Resources::Load<Texture>(L"HPBack", L"..\\Resources\\UI\\PlayerLifeBack.png");
        HPBack->GetComponent<SpriteRenderer>()->SetImg(temp);


        BackGround* HPBase = object::Instantiate<BackGround>(enums::eLayerType::UI);
        HPBase->GetComponent<Transform>()->SetPos(Math::Vector2<float>(9.f, 10.f));
        HPBase->GetComponent<Transform>()->SetScale(Math::Vector2<float>(300.f, 66.f));
        temp = Resources::Load<Texture>(L"HPBase", L"..\\Resources\\UI\\PlayerLifeBase 1.png");
        HPBase->GetComponent<SpriteRenderer>()->SetImg(temp);

        // DASH
        BackGround* DashBase = object::Instantiate<BackGround>(enums::eLayerType::UI);
        DashBase->GetComponent<Transform>()->SetPos(Math::Vector2<float>(9.f, 80.f));
        DashBase->GetComponent<Transform>()->SetScale(Math::Vector2<float>(252.f, 34.f));
        temp = Resources::Load<Texture>(L"DashBase", L"..\\Resources\\UI\\DashCountBase.png");
        DashBase->GetComponent<SpriteRenderer>()->SetImg(temp);

        // COIN
        BackGround* Coin = object::Instantiate<BackGround>(enums::eLayerType::UI);
        Coin->GetComponent<Transform>()->SetPos(Math::Vector2<float>(20.f, 650.f));
        Coin->GetComponent<Transform>()->SetScale(Math::Vector2<float>(17.f, 14.f));
        temp = Resources::Load<Texture>(L"CoinUI", L"..\\Resources\\UI\\Coin.png");
        Coin->GetComponent<SpriteRenderer>()->SetImg(temp);

        // FOOD
        BackGround* Food = object::Instantiate<BackGround>(enums::eLayerType::UI);
        Food->GetComponent<Transform>()->SetPos(Math::Vector2<float>(12.f, 676.f));
        Food->GetComponent<Transform>()->SetScale(Math::Vector2<float>(34.f, 28.f));
        temp = Resources::Load<Texture>(L"FoodUI", L"..\\Resources\\UI\\Food.png");
        Food->GetComponent<SpriteRenderer>()->SetImg(temp);

        // Weapon Swap
        BackGround* WeaponSlot = object::Instantiate<BackGround>(enums::eLayerType::UI);
        WeaponSlot->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1140.f, 590.f));
        WeaponSlot->GetComponent<Transform>()->SetScale(Math::Vector2<float>(140.f, 102.f));
        temp = Resources::Load<Texture>(L"WeaponSlot", L"..\\Resources\\UI\\EquippedWeaponBase.png");
        WeaponSlot->GetComponent<SpriteRenderer>()->SetImg(temp);


        BackGround* WeaponSlot2 = object::Instantiate<BackGround>(enums::eLayerType::UI);
        WeaponSlot2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1120.f, 606.f));
        WeaponSlot2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(140.f, 102.f));
        temp = Resources::Load<Texture>(L"WeaponSlot", L"..\\Resources\\UI\\EquippedWeaponBase.png");
        WeaponSlot2->GetComponent<SpriteRenderer>()->SetImg(temp);

        BackGround* Minimap = object::Instantiate<BackGround>(enums::eLayerType::UI);
        Minimap->GetComponent<Transform>()->SetPos(Math::Vector2<float>(930.f, 15.f));
        Minimap->GetComponent<Transform>()->SetScale(Math::Vector2<float>(350.f, 85.f));

        BackGround* Floor1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(0.f, 510.f));
        Floor1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(320.f, 120.f));
        temp = Resources::Load<Texture>(L"TownFloor", L"..\\Resources\\TownScene\\Map.png");
        Floor1->GetComponent<SpriteRenderer>()->SetImg(temp);

        BackGround* Floor2 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Floor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(320.f, 510.f));
        Floor2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(320.f, 120.f));
        temp = Resources::Load<Texture>(L"TownFloor", L"..\\Resources\\TownScene\\Map.png");
        Floor2->GetComponent<SpriteRenderer>()->SetImg(temp);

        BackGround* Floor3 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Floor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 510.f));
        Floor3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(320.f, 120.f));
        temp = Resources::Load<Texture>(L"TownFloor", L"..\\Resources\\TownScene\\Map.png");
        Floor3->GetComponent<SpriteRenderer>()->SetImg(temp);

        BackGround* Floor4 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Floor4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(960.f, 510.f));
        Floor4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(320.f, 120.f));
        temp = Resources::Load<Texture>(L"TownFloor", L"..\\Resources\\TownScene\\Map.png");
        Floor4->GetComponent<SpriteRenderer>()->SetImg(temp);

        BackGround* FloorUnder = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        FloorUnder->GetComponent<Transform>()->SetPos(Math::Vector2<float>(0.f, 630.f));
        FloorUnder->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 90.f));
        temp = Resources::Load<Texture>(L"FloorUnder", L"..\\Resources\\TownScene\\Map2.png");
        FloorUnder->GetComponent<SpriteRenderer>()->SetImg(temp);

        // Player
        Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
        player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(300.f, 630.f));
        player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(52.f, 84.f));
        temp = Resources::Load<Texture>(L"player", L"..\\Resources\\Player\\Basic\\Idle\\CharIdle0.png");
        player->GetComponent<SpriteRenderer>()->SetImg(temp);
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