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
#include "EHSlope.h"
#include "EHTrigger.h"
#include "EHCanvas.h"
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
        // Sound
        Sound* BGM = Resources::Load<Sound>(L"TownBGM", L"..\\Resources\\Sound\\BGM\\0.Town.wav");
        SetBGM(BGM);

        SetSize(Math::Vector2<float>(7540.f, 1440.f));
        Texture* texture = nullptr;

        // Player
        Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
        player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(256.f, 500.f));
        player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

        // sky
        BackGround* Sky = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Sky->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f,360.f));
        Sky->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
        texture = Resources::Load<Texture>(L"Sky", L"..\\Resources\\TownScene\\Sky_Day.bmp");
        Sky->GetComponent<SpriteRenderer>()->SetImg(texture);
        Sky->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

        // Back
        BackGround* Back = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Back->GetComponent<Transform>()->SetPos(Math::Vector2<float>(3770.f, 720.f));
        Back->GetComponent<Transform>()->SetScale(Math::Vector2<float>(7540.f, 1440.f));
        texture = Resources::Load<Texture>(L"TownBG", L"..\\Resources\\TownScene\\TownBG.bmp");
        Back->GetComponent<SpriteRenderer>()->SetImg(texture);

        // Tree
        BackGround* Tree = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Tree->GetComponent<Transform>()->SetPos(Math::Vector2<float>(3770.f, 720.f));
        Tree->GetComponent<Transform>()->SetScale(Math::Vector2<float>(7540.f, 1440.f));
        texture = Resources::Load<Texture>(L"TownLayer", L"..\\Resources\\TownScene\\TownLayer.bmp");
        Tree->GetComponent<SpriteRenderer>()->SetImg(texture);

        BackGround* Tree1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Tree1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2162.f, 1146.f));
        Tree1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(268.f, 308.f));
        texture = Resources::Load<Texture>(L"Tree1", L"..\\Resources\\TownScene\\Tree1.bmp");
        Tree1->GetComponent<SpriteRenderer>()->SetImg(texture);

        BackGround* TownBackGround = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        TownBackGround->GetComponent<Transform>()->SetPos(Math::Vector2<float>(3770.f, 720.f));
        TownBackGround->GetComponent<Transform>()->SetScale(Math::Vector2<float>(7540.f, 1440.f));
        texture = Resources::Load<Texture>(L"TownBackGround", L"..\\Resources\\TownScene\\TownBackGround.bmp");
        TownBackGround->GetComponent<SpriteRenderer>()->SetImg(texture);
        TownBackGround->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

        // Town structure
        BackGround* TrainingSchool = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        TrainingSchool->GetComponent<Transform>()->SetPos(Math::Vector2<float>(632.f, 1146.f));
        TrainingSchool->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1080.f, 308.f));
        texture = Resources::Load<Texture>(L"TrainingSchool", L"..\\Resources\\TownScene\\TrainingSchool.bmp");
        TrainingSchool->GetComponent<SpriteRenderer>()->SetImg(texture);

        BackGround* StreetLight1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        StreetLight1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(64.f, 1180.f));
        StreetLight1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(120.f, 240.f));
        texture = Resources::Load<Texture>(L"StreetLight1", L"..\\Resources\\TownScene\\StreetLight.bmp");
        texture->SetWidth(30);
        texture->SetHeight(60);
        StreetLight1->GetComponent<SpriteRenderer>()->SetImg(texture);

        BackGround* StreetLight2 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        StreetLight2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1824.f, 1180.f));
        StreetLight2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(120.f, 240.f));
        texture = Resources::Load<Texture>(L"StreetLight1", L"..\\Resources\\TownScene\\StreetLight.bmp");
        StreetLight2->GetComponent<SpriteRenderer>()->SetImg(texture);

        BackGround* Well1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Well1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(5758.f, 1202.f));
        Well1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(196.f, 196.f));
        texture = Resources::Load<Texture>(L"Well", L"..\\Resources\\TownScene\\Well.bmp");
        Well1->GetComponent<SpriteRenderer>()->SetImg(texture);

        BackGround* DungeonSign1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        DungeonSign1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(3212.f, 1256.f));
        DungeonSign1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 88.f));
        texture = Resources::Load<Texture>(L"DungeonSign", L"..\\Resources\\TownScene\\DungeonSign.bmp");
        DungeonSign1->GetComponent<SpriteRenderer>()->SetImg(texture);

        BackGround* DungeonSign2 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        DungeonSign2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(4392.f, 1256.f));
        DungeonSign2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 88.f));
        texture = Resources::Load<Texture>(L"DungeonSignReverse", L"..\\Resources\\TownScene\\DungeonSignReverse.bmp");
        DungeonSign2->GetComponent<SpriteRenderer>()->SetImg(texture);

        BackGround* Tree2 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Tree2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(5094.f, 1084.f));
        Tree2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(268.f, 308.f));
        texture = Resources::Load<Texture>(L"Tree1", L"..\\Resources\\TownScene\\Tree1.bmp");
        Tree2->GetComponent<SpriteRenderer>()->SetImg(texture);

        BackGround* Tree3 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Tree3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(5626.f, 1178.f));
        Tree3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(204.f, 244.f));
        texture = Resources::Load<Texture>(L"Tree2", L"..\\Resources\\TownScene\\Tree0.bmp");
        Tree3->GetComponent<SpriteRenderer>()->SetImg(texture);

        // °íÃÄ¾ßµÊ
        BackGround* Tree4 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        Tree4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(7086.f, 1206.f));
        Tree4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(204.f, 244.f));
        texture = Resources::Load<Texture>(L"Tree2", L"..\\Resources\\TownScene\\Tree0.bmp");
        Tree4->GetComponent<SpriteRenderer>()->SetImg(texture);

        //Npc
        Npc* Commander = object::Instantiate<Npc>(enums::eLayerType::Npc);
        Commander->GetComponent<Transform>()->SetPos(Math::Vector2<float>(638.f, 1250.f));
        Commander->GetComponent<Transform>()->SetScale(Math::Vector2<float>(92.f, 100.f));
        texture = Resources::Load<Texture>(L"Commander0", L"..\\Resources\\NPC\\NPC_CommanderSheet.bmp");
        Commander->AddComponent<Animator>();
        Commander->GetComponent<Animator>()->CreateAnimation(L"CommanderIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(23.f, 25.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
        Commander->GetComponent<Animator>()->PlayAnimation(L"CommanderIdle", true);
    
        // Downfloor
        Floor* Downfloor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        Downfloor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(3768.f, 1332.f));
        Downfloor1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(7536.f, 64.f));
        Downfloor1->AddComponent<Collider>();
        Downfloor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(7536.f, 64.f));
        Downfloor1->GetComponent<Collider>()->SetAffectedCamera(true);
        Downfloor1->SetDownFloor(false);

        GameObject* obj1 = object::Instantiate<GameObject>(enums::eLayerType::UI);
        obj1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(468.f, 340.f));
        Animator* ani1 = obj1->AddComponent<Animator>();
        texture = Resources::Load<Texture>(L"Dungeoneat", L"..\\Resources\\TownScene\\DungeonEat\\DungeonEatSheet.bmp");
        ani1->CreateAnimation(L"Dungeoneat", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(117.f, 85.f), Math::Vector2<float>(0.f, 0.f), 28, 0.1f);

        Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
        trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(3802.f, 1332.f));
        trigger1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1180.f, 64.f));
        trigger1->AddComponent<Collider>();
        trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1180.f, 64.f));
        trigger1->GetComponent<Collider>()->SetAffectedCamera(true);
        trigger1->SetType(Trigger::eTriggertype::Scenechange);
        trigger1->SetScenename(L"JailScene1");
        trigger1->SetDungeonEater(obj1);

        Floor* Downfloor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        Downfloor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(5964.f, 1332.f));
        Downfloor3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(3144.f, 64.f));
        Downfloor3->AddComponent<Collider>();
        Downfloor3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(3144.f, 64.f));
        Downfloor3->GetComponent<Collider>()->SetAffectedCamera(true);
        Downfloor3->SetDownFloor(false);

        Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(790.f, 756.f));
        floor2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1580.f, 64.f));
        floor2->AddComponent<Collider>();
        floor2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1580.f, 64.f));
        floor2->GetComponent<Collider>()->SetAffectedCamera(true);

        Floor* floor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2125.f, 1268.f));
        floor3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(60.f, 64.f));
        floor3->AddComponent<Collider>();
        floor3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(60.f, 64.f));
        floor3->GetComponent<Collider>()->SetAffectedCamera(true);

        Floor* floor4 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2474.f, 1268.f));
        floor4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(124.f, 64.f));
        floor4->AddComponent<Collider>();
        floor4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 64.f));
        floor4->GetComponent<Collider>()->SetAffectedCamera(true);

        Floor* floor5 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(3784.f, 884.f));
        floor5->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1728.f, 64.f));
        floor5->AddComponent<Collider>();
        floor5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1728.f, 64.f));
        floor5->GetComponent<Collider>()->SetAffectedCamera(true);

        Floor* floor6 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(5094.f, 1268.f));
        floor6->GetComponent<Transform>()->SetScale(Math::Vector2<float>(124.f, 64.f));
        floor6->AddComponent<Collider>();
        floor6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 64.f));
        floor6->GetComponent<Collider>()->SetAffectedCamera(true);

        Floor* floor7 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor7->GetComponent<Transform>()->SetPos(Math::Vector2<float>(5354.f, 1268.f));
        floor7->GetComponent<Transform>()->SetScale(Math::Vector2<float>(60.f, 64.f));
        floor7->AddComponent<Collider>();
        floor7->GetComponent<Collider>()->SetScale(Math::Vector2<float>(60.f, 64.f));
        floor7->GetComponent<Collider>()->SetAffectedCamera(true);

        Floor* floor8 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor8->GetComponent<Transform>()->SetPos(Math::Vector2<float>(6716.f, 756.f));
        floor8->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1640.f, 64.f));
        floor8->AddComponent<Collider>();
        floor8->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1640.f, 64.f));
        floor8->GetComponent<Collider>()->SetAffectedCamera(true);

        Floor* Secondfloor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        Secondfloor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1280.f, 884.f));
        Secondfloor1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(256.f, 56.f));
        Secondfloor1->AddComponent<SpriteRenderer>();
        texture = Resources::Load<Texture>(L"OneWay", L"..\\Resources\\TownScene\\SecondFloor_OneWay.bmp");
        Secondfloor1->GetComponent<SpriteRenderer>()->SetImg(texture);
        Secondfloor1->AddComponent<Collider>();
        Secondfloor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 56.f));
        Secondfloor1->GetComponent<Collider>()->SetAffectedCamera(true);

        Floor* Secondfloor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        Secondfloor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1544.f, 1048.f));
        Secondfloor2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(256.f, 56.f));
        Secondfloor2->AddComponent<SpriteRenderer>();
        texture = Resources::Load<Texture>(L"OneWay", L"..\\Resources\\TownScene\\SecondFloor_OneWay.bmp");
        Secondfloor2->GetComponent<SpriteRenderer>()->SetImg(texture);
        Secondfloor2->AddComponent<Collider>();
        Secondfloor2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 56.f));
        Secondfloor2->GetComponent<Collider>()->SetAffectedCamera(true);

        Floor* Secondfloor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        Secondfloor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1304.f, 1208.f));
        Secondfloor3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(256.f, 56.f));
        Secondfloor3->AddComponent<SpriteRenderer>();
        texture = Resources::Load<Texture>(L"OneWay", L"..\\Resources\\TownScene\\SecondFloor_OneWay.bmp");
        Secondfloor3->GetComponent<SpriteRenderer>()->SetImg(texture);
        Secondfloor3->AddComponent<Collider>();
        Secondfloor3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 56.f));
        Secondfloor3->GetComponent<Collider>()->SetAffectedCamera(true);

        Floor* Secondfloor4 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        Secondfloor4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(3472.f, 1176.f));
        Secondfloor4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(256.f, 56.f));
        Secondfloor4->AddComponent<SpriteRenderer>();
        texture = Resources::Load<Texture>(L"OneWay", L"..\\Resources\\TownScene\\SecondFloor_OneWay.bmp");
        Secondfloor4->GetComponent<SpriteRenderer>()->SetImg(texture);
        Secondfloor4->AddComponent<Collider>();
        Secondfloor4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 56.f));
        Secondfloor4->GetComponent<Collider>()->SetAffectedCamera(true);

        Floor* Secondfloor5 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        Secondfloor5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(3784.f, 1016.f));
        Secondfloor5->GetComponent<Transform>()->SetScale(Math::Vector2<float>(256.f, 56.f));
        Secondfloor5->AddComponent<SpriteRenderer>();
        texture = Resources::Load<Texture>(L"OneWay", L"..\\Resources\\TownScene\\SecondFloor_OneWay.bmp");
        Secondfloor5->GetComponent<SpriteRenderer>()->SetImg(texture);
        Secondfloor5->AddComponent<Collider>();
        Secondfloor5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 56.f));
        Secondfloor5->GetComponent<Collider>()->SetAffectedCamera(true);

        Floor* Secondfloor6 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        Secondfloor6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(6060.f, 1060.f));
        Secondfloor6->GetComponent<Transform>()->SetScale(Math::Vector2<float>(256.f, 56.f));
        Secondfloor6->AddComponent<SpriteRenderer>();
        texture = Resources::Load<Texture>(L"OneWay", L"..\\Resources\\TownScene\\SecondFloor_OneWay.bmp");
        Secondfloor6->GetComponent<SpriteRenderer>()->SetImg(texture);
        Secondfloor6->AddComponent<Collider>();
        Secondfloor6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 56.f));
        Secondfloor6->GetComponent<Collider>()->SetAffectedCamera(true);
        
        // Slope 1
        Slope* test1 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1612.f, 756.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test1->AddComponent<Collider>();
        test1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test1->GetComponent<Collider>()->SetAffectedCamera(true);
        test1->SetIntercept(856.f);
        test1->SetCorrection(64.f);

        Slope* test2 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1676.f, 820.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test2->AddComponent<Collider>();
        test2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test2->GetComponent<Collider>()->SetAffectedCamera(true);
        test2->SetIntercept(856.f);
        test2->SetCorrection(90.f);

        Slope* test3 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1740.f, 884.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test3->AddComponent<Collider>();
        test3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test3->GetComponent<Collider>()->SetAffectedCamera(true);
        test3->SetIntercept(856.f);
        test3->SetCorrection(90.f);

        Slope* test4 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1804.f, 948.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test4->AddComponent<Collider>();
        test4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test4->GetComponent<Collider>()->SetAffectedCamera(true);
        test4->SetIntercept(856.f);
        test4->SetCorrection(90.f);

        Slope* test5 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1870.f, 1012.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test5->AddComponent<Collider>();
        test5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test5->GetComponent<Collider>()->SetAffectedCamera(true);
        test5->SetIntercept(856.f);
        test5->SetCorrection(90.f);

        Slope* test6 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1934.f, 1078.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test6->AddComponent<Collider>();
        test6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test6->GetComponent<Collider>()->SetAffectedCamera(true);
        test6->SetIntercept(856.f);
        test6->SetCorrection(90.f);

        Slope* test7 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test7->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1998.f, 1142.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test7->AddComponent<Collider>();
        test7->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 80.f));
        test7->GetComponent<Collider>()->SetAffectedCamera(true);
        test7->SetIntercept(856.f);
        test7->SetCorrection(99.3f);

        Slope* test8 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test8->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2062.f, 1206.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test8->AddComponent<Collider>();
        test8->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 80.f));
        test8->GetComponent<Collider>()->SetAffectedCamera(true);
        test8->SetIntercept(856.f);
        test8->SetCorrection(99.3f);

        // slope 2
        Slope* test9 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test9->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2572.f, 1208.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test9->AddComponent<Collider>();
        test9->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 68.f));
        test9->GetComponent<Collider>()->SetAffectedCamera(true);
        test9->SetIntercept(3780.f);
        test9->SetCorrection(90.f);
        test9->SetRight(true);

        Slope* test10 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test10->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2636.f, 1144.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test10->AddComponent<Collider>();
        test10->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test10->GetComponent<Collider>()->SetAffectedCamera(true);
        test10->SetIntercept(3780.f);
        test10->SetCorrection(90.f);
        test10->SetRight(true);

        Slope* test11 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test11->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2700.f, 1080.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test11->AddComponent<Collider>();
        test11->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test11->GetComponent<Collider>()->SetAffectedCamera(true);
        test11->SetIntercept(3780.f);
        test11->SetCorrection(90.f);
        test11->SetRight(true);

        Slope* test12 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test12->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2764.f, 1016.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test12->AddComponent<Collider>();
        test12->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test12->GetComponent<Collider>()->SetAffectedCamera(true);
        test12->SetIntercept(3780.f);
        test12->SetCorrection(90.f);
        test12->SetRight(true);

        Slope* test13 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test13->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2828.f, 952.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test13->AddComponent<Collider>();
        test13->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test13->GetComponent<Collider>()->SetAffectedCamera(true);
        test13->SetIntercept(3780.f);
        test13->SetCorrection(90.f);
        test13->SetRight(true);

        Slope* test14 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test14->GetComponent<Transform>()->SetPos(Math::Vector2<float>(2892.f, 888.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test14->AddComponent<Collider>();
        test14->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test14->GetComponent<Collider>()->SetAffectedCamera(true);
        test14->SetIntercept(3780.f);
        test14->SetCorrection(90.f);
        test14->SetRight(true);

        // slope 3
        Slope* test15 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test15->GetComponent<Transform>()->SetPos(Math::Vector2<float>(4996.f, 1208.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test15->AddComponent<Collider>();
        test15->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test15->GetComponent<Collider>()->SetAffectedCamera(true);
        test15->SetIntercept(3788.f);
        test15->SetCorrection(90.f);

        Slope* test16 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test16->GetComponent<Transform>()->SetPos(Math::Vector2<float>(4932.f, 1144.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test16->AddComponent<Collider>();
        test16->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test16->GetComponent<Collider>()->SetAffectedCamera(true);
        test16->SetIntercept(3788.f);
        test16->SetCorrection(90.f);

        Slope* test17 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test17->GetComponent<Transform>()->SetPos(Math::Vector2<float>(4868.f, 1080.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test17->AddComponent<Collider>();
        test17->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test17->GetComponent<Collider>()->SetAffectedCamera(true);
        test17->SetIntercept(3788.f);
        test17->SetCorrection(90.f);

        Slope* test18 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test18->GetComponent<Transform>()->SetPos(Math::Vector2<float>(4804.f, 1016.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test18->AddComponent<Collider>();
        test18->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test18->GetComponent<Collider>()->SetAffectedCamera(true);
        test18->SetIntercept(3788.f);
        test18->SetCorrection(90.f);

        Slope* test19 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test19->GetComponent<Transform>()->SetPos(Math::Vector2<float>(4740.f, 952.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test19->AddComponent<Collider>();
        test19->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test19->GetComponent<Collider>()->SetAffectedCamera(true);
        test19->SetIntercept(3788.f);
        test19->SetCorrection(90.f);

        Slope* test20 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test20->GetComponent<Transform>()->SetPos(Math::Vector2<float>(4676.f, 888.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test20->AddComponent<Collider>();
        test20->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test20->GetComponent<Collider>()->SetAffectedCamera(true);
        test20->SetIntercept(3788.f);
        test20->SetCorrection(90.f);

        // slope4
        Slope* test21 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test21->GetComponent<Transform>()->SetPos(Math::Vector2<float>(5420.f, 1208.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test21->AddComponent<Collider>();
        test21->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test21->GetComponent<Collider>()->SetAffectedCamera(true);
        test21->SetIntercept(6628.f);
        test21->SetCorrection(90.f);
        test21->SetRight(true);

        Slope* test22 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test22->GetComponent<Transform>()->SetPos(Math::Vector2<float>(5484.f, 1144.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test22->AddComponent<Collider>();
        test22->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test22->GetComponent<Collider>()->SetAffectedCamera(true);
        test22->SetIntercept(6628.f);
        test22->SetCorrection(90.f);
        test22->SetRight(true);

        Slope* test23 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test23->GetComponent<Transform>()->SetPos(Math::Vector2<float>(5548.f, 1080.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test23->AddComponent<Collider>();
        test23->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test23->GetComponent<Collider>()->SetAffectedCamera(true);
        test23->SetIntercept(6628.f);
        test23->SetCorrection(90.f);
        test23->SetRight(true);

        Slope* test24 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test24->GetComponent<Transform>()->SetPos(Math::Vector2<float>(5612.f, 1016.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test24->AddComponent<Collider>();
        test24->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test24->GetComponent<Collider>()->SetAffectedCamera(true);
        test24->SetIntercept(6628.f);
        test24->SetCorrection(90.f);
        test24->SetRight(true);

        Slope* test25 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test25->GetComponent<Transform>()->SetPos(Math::Vector2<float>(5676.f, 952.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test25->AddComponent<Collider>();
        test25->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test25->GetComponent<Collider>()->SetAffectedCamera(true);
        test25->SetIntercept(6628.f);
        test25->SetCorrection(90.f);
        test25->SetRight(true);

        Slope* test26 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test26->GetComponent<Transform>()->SetPos(Math::Vector2<float>(5740.f, 888.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test26->AddComponent<Collider>();
        test26->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test26->GetComponent<Collider>()->SetAffectedCamera(true);
        test26->SetIntercept(6628.f);
        test26->SetCorrection(90.f);
        test26->SetRight(true);

        Slope* test27 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test27->GetComponent<Transform>()->SetPos(Math::Vector2<float>(5804.f, 824.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test27->AddComponent<Collider>();
        test27->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test27->GetComponent<Collider>()->SetAffectedCamera(true);
        test27->SetIntercept(6628.f);
        test27->SetCorrection(90.f);
        test27->SetRight(true);

        Slope* test28 = object::Instantiate<Slope>(enums::eLayerType::Floor);
        test28->GetComponent<Transform>()->SetPos(Math::Vector2<float>(5868.f, 760.f));
        //test->GetComponent<Transform>()->SetScale(Math::Vector2<float>(512.f, 512.f));
        test28->AddComponent<Collider>();
        test28->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
        test28->GetComponent<Collider>()->SetAffectedCamera(true);
        test28->SetIntercept(6628.f);
        test28->SetCorrection(90.f);
        test28->SetRight(true);

        SetPlayer(player);
        CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Floor,true);
        CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Trigger,true);
        //Camera::SetTarget(player);
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