#include "EHTownScene.h"
#include "EHImage.h"
#include "EHObject.h"
#include "EHGameObject.h"

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
        Sky->SetImagePath(L"\\Resources\\TownScene\\Sky_Day.png");

        // Back
        Image* Back = object::Instantiate<Image>(enums::eLayerType::BackGround);
        Back->GetComponent<Transform>()->SetPos(Math::Vector2<float>(0.f, 152.f));
        Back->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 568.f));
        Back->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
        Back->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(319.f, 141.f));
        Back->SetImagePath(L"\\Resources\\TownScene\\TownBG_Day.png");

        // Tree
        Image* Tree = object::Instantiate<Image>(enums::eLayerType::BackGround);
        Tree->GetComponent<Transform>()->SetPos(Math::Vector2<float>(0.f, 440.f));
        Tree->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 280.f));
        Tree->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
        Tree->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(319.f, 94.f));
        Tree->SetImagePath(L"\\Resources\\TownScene\\TownLayer_Day.png");

        // HP
        Image* HPBack = object::Instantiate<Image>(enums::eLayerType::UI);
        HPBack->GetComponent<Transform>()->SetPos(Math::Vector2<float>(9.f, 10.f));
        HPBack->GetComponent<Transform>()->SetScale(Math::Vector2<float>(300.f, 66.f));
        HPBack->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
        HPBack->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(74.f, 16.f));
        HPBack->SetImagePath(L"\\Resources\\UI\\PlayerLifeBack.png");

        Image* HPBase = object::Instantiate<Image>(enums::eLayerType::UI);
        HPBase->GetComponent<Transform>()->SetPos(Math::Vector2<float>(9.f, 10.f));
        HPBase->GetComponent<Transform>()->SetScale(Math::Vector2<float>(300.f, 66.f));
        HPBase->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
        HPBase->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(74.f, 16.f));
        HPBase->SetImagePath(L"\\Resources\\UI\\PlayerLifeBase 1.png");

        // DASH
        Image* DashBase = object::Instantiate<Image>(enums::eLayerType::UI);
        DashBase->GetComponent<Transform>()->SetPos(Math::Vector2<float>(9.f, 80.f));
        DashBase->GetComponent<Transform>()->SetScale(Math::Vector2<float>(252.f, 34.f));
        DashBase->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
        DashBase->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(63.f, 8.f));
        DashBase->SetImagePath(L"\\Resources\\UI\\DashCountBase.png");

        // COIN
        Image* Coin = object::Instantiate<Image>(enums::eLayerType::UI);
        Coin->GetComponent<Transform>()->SetPos(Math::Vector2<float>(20.f, 650.f));
        Coin->GetComponent<Transform>()->SetScale(Math::Vector2<float>(17.f, 14.f));
        Coin->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
        Coin->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(17.f, 14.f));
        Coin->SetImagePath(L"\\Resources\\UI\\Coin.png");

        // FOOD
        Image* Food = object::Instantiate<Image>(enums::eLayerType::UI);
        Food->GetComponent<Transform>()->SetPos(Math::Vector2<float>(12.f, 676.f));
        Food->GetComponent<Transform>()->SetScale(Math::Vector2<float>(34.f, 28.f));
        Food->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
        Food->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(17.f, 14.f));
        Food->SetImagePath(L"\\Resources\\UI\\Food.png");
    }

    void TownScene::Update()
    {
        Scene::Update();
    }

    void TownScene::Render(HDC hdc)
    {
        Scene::Render(hdc);
    }
}