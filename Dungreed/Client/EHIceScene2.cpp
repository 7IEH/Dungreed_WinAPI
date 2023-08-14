#include "EHIceScene2.h"
#include "EHResources.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHFloor.h"
#include "EHCeil.h"
#include "EHWall.h"
#include "EHTrigger.h"
#include "EHPlayer.h"

namespace EH
{
	void IceScene2::Initialize()
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

        SetSize(Math::Vector2<float>(1344.f, 1024.f));

        BackGround* IceSubBG = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        IceSubBG->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 520.f));
        IceSubBG->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 1040.f));
        Texture* texture = Resources::Load<Texture>(L"IceSubBG", L"..\\Resources\\Dungeon\\IceBackGround\\IceLayer\\BGLayer_0.bmp");
        IceSubBG->GetComponent<SpriteRenderer>()->SetImg(texture);
        IceSubBG->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

        BackGround* IceBG1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
        IceBG1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(672.f, 512.f));
        IceBG1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1344.f, 1024.f));
        texture = Resources::Load<Texture>(L"IceBG2", L"..\\Resources\\Dungeon\\IceBackGround\\2\\IceScene2.bmp");
        IceBG1->GetComponent<SpriteRenderer>()->SetImg(texture);
        IceBG1->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

        // Floor
        Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(384.f, 928.f));
        floor1->AddComponent<Collider>();
        floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(768.f, 64.f));
        floor1->GetComponent<Collider>()->SetAffectedCamera(true);
        floor1->SetDownFloor(false);

        Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(832.f, 864.f));
        floor2->AddComponent<Collider>();
        floor2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(128.f, 64.f));
        floor2->GetComponent<Collider>()->SetAffectedCamera(true);
        floor2->SetDownFloor(true);

        Floor* floor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1120.f, 928.f));
        floor3->AddComponent<Collider>();
        floor3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(448.f, 64.f));
        floor3->GetComponent<Collider>()->SetAffectedCamera(true);
        floor3->SetDownFloor(true);

        Floor* floor4 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1056.f, 544.f));
        floor4->AddComponent<Collider>();
        floor4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(192.f, 64.f));
        floor4->GetComponent<Collider>()->SetAffectedCamera(true);
        floor4->SetDownFloor(true);

        Floor* floor5 = object::Instantiate<Floor>(enums::eLayerType::Floor);
        floor5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(224.f, 480.f));
        floor5->AddComponent<Collider>();
        floor5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(320.f, 64.f));
        floor5->GetComponent<Collider>()->SetAffectedCamera(true);
        floor5->SetDownFloor(true);

        // Ceil
        Ceil* ceil1 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
        ceil1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(94.f, 608.f));
        ceil1->AddComponent<Collider>();
        ceil1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(188.f, 64.f));
        ceil1->GetComponent<Collider>()->SetAffectedCamera(true);

        Ceil* ceil2 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
        ceil2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(286.f, 544.f));
        ceil2->AddComponent<Collider>();
        ceil2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(188.f, 64.f));
        ceil2->GetComponent<Collider>()->SetAffectedCamera(true);

        Ceil* ceil3 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
        ceil3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 96.f));
        ceil3->AddComponent<Collider>();
        ceil3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(192.f, 64.f));
        ceil3->GetComponent<Collider>()->SetAffectedCamera(true);

        Ceil* ceil4 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
        ceil4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(548.f, 224.f));
        ceil4->AddComponent<Collider>();
        ceil4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(192.f, 64.f));
        ceil4->GetComponent<Collider>()->SetAffectedCamera(true);

        Ceil* ceil5 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
        ceil5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 288.f));
        ceil5->AddComponent<Collider>();
        ceil5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(120.f, 64.f));
        ceil5->GetComponent<Collider>()->SetAffectedCamera(true);

        Ceil* ceil6 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
        ceil6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(800.f, 96.f));
        ceil6->AddComponent<Collider>();
        ceil6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(192.f, 64.f));
        ceil6->GetComponent<Collider>()->SetAffectedCamera(true);

        Ceil* ceil7 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
        ceil7->GetComponent<Transform>()->SetPos(Math::Vector2<float>(960.f, 224.f));
        ceil7->AddComponent<Collider>();
        ceil7->GetComponent<Collider>()->SetScale(Math::Vector2<float>(120.f, 64.f));
        ceil7->GetComponent<Collider>()->SetAffectedCamera(true);

        Ceil* ceil8 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
        ceil8->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1088.f, 96.f));
        ceil8->AddComponent<Collider>();
        ceil8->GetComponent<Collider>()->SetScale(Math::Vector2<float>(128.f, 64.f));
        ceil8->GetComponent<Collider>()->SetAffectedCamera(true);

        Ceil* ceil9 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
        ceil9->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1154.f, 608.f));
        ceil9->AddComponent<Collider>();
        ceil9->GetComponent<Collider>()->SetScale(Math::Vector2<float>(380.f, 64.f));
        ceil9->GetComponent<Collider>()->SetAffectedCamera(true);


        // Wall
        Wall* wall1 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(800.f, 900.f));
        wall1->AddComponent<Collider>();
        wall1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 128.f));
        wall1->GetComponent<Collider>()->SetAffectedCamera(true);
        wall1->SetRight(true);

        Wall* wall2 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(864.f, 930.f));
        wall2->AddComponent<Collider>();
        wall2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 188.f));
        wall2->GetComponent<Collider>()->SetAffectedCamera(true);
        wall2->SetRight(false);

        Wall* wall3 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1184.f, 962.f));
        wall3->AddComponent<Collider>();
        wall3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 124.f));
        wall3->GetComponent<Collider>()->SetAffectedCamera(true);
        wall3->SetRight(true);

        Wall* wall4 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(992.f, 576.f));
        wall4->AddComponent<Collider>();
        wall4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 120.f));
        wall4->GetComponent<Collider>()->SetAffectedCamera(true);
        wall4->SetRight(true);

        Wall* wall5 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1184.f, 348.f));
        wall5->AddComponent<Collider>();
        wall5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 448.f));
        wall5->GetComponent<Collider>()->SetAffectedCamera(true);
        wall5->SetRight(true);

        Wall* wall6 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(992.f, 156.f));
        wall6->AddComponent<Collider>();
        wall6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 192.f));
        wall6->GetComponent<Collider>()->SetAffectedCamera(true);
        wall6->SetRight(false);

        Wall* wall7 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall7->GetComponent<Transform>()->SetPos(Math::Vector2<float>(928.f, 156.f));
        wall7->AddComponent<Collider>();
        wall7->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 192.f));
        wall7->GetComponent<Collider>()->SetAffectedCamera(true);
        wall7->SetRight(false);

        Wall* wall8 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall8->GetComponent<Transform>()->SetPos(Math::Vector2<float>(672.f, 188.f));
        wall8->AddComponent<Collider>();
        wall8->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
        wall8->GetComponent<Collider>()->SetAffectedCamera(true);
        wall8->SetRight(false);

        Wall* wall9 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall9->GetComponent<Transform>()->SetPos(Math::Vector2<float>(608.f, 252.f));
        wall9->AddComponent<Collider>();
        wall9->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 128.f));
        wall9->GetComponent<Collider>()->SetAffectedCamera(true);
        wall9->SetRight(true);

        Wall* wall10 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall10->GetComponent<Transform>()->SetPos(Math::Vector2<float>(480.f, 156.f));
        wall10->AddComponent<Collider>();
        wall10->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 192.f));
        wall10->GetComponent<Collider>()->SetAffectedCamera(true);
        wall10->SetRight(true);

        Wall* wall11 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall11->GetComponent<Transform>()->SetPos(Math::Vector2<float>(352.f, 62.f));
        wall11->AddComponent<Collider>();
        wall11->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 124.f));
        wall11->GetComponent<Collider>()->SetAffectedCamera(true);
        wall11->SetRight(true);

        Wall* wall12 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall12->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 256.f));
        wall12->AddComponent<Collider>();
        wall12->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 512.f));
        wall12->GetComponent<Collider>()->SetAffectedCamera(true);
        wall12->SetRight(false);

        Wall* wall13 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall13->GetComponent<Transform>()->SetPos(Math::Vector2<float>(352.f, 512.f));
        wall13->AddComponent<Collider>();
        wall13->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 120.f));
        wall13->GetComponent<Collider>()->SetAffectedCamera(true);
        wall13->SetRight(false);

        Wall* wall14 = object::Instantiate<Wall>(enums::eLayerType::Floor);
        wall14->GetComponent<Transform>()->SetPos(Math::Vector2<float>(160.f, 572.f));
        wall14->AddComponent<Collider>();
        wall14->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 128.f));
        wall14->GetComponent<Collider>()->SetAffectedCamera(true);
        wall14->SetRight(false);

        // Trigger
        Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
        trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1024.f, 992.f));
        trigger1->AddComponent<Collider>();
        trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 64.f));
        trigger1->SetType(Trigger::eTriggertype::Scenechange);
        trigger1->SetScenename(L"IceScene5");

        Trigger* trigger2 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
        trigger2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1312.f, 768.f));
        trigger2->AddComponent<Collider>();
        trigger2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
        trigger2->SetType(Trigger::eTriggertype::Scenechange);
        trigger2->SetScenename(L"IceScene1");

        Trigger* trigger3 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
        trigger3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 768.f));
        trigger3->AddComponent<Collider>();
        trigger3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
        trigger3->SetType(Trigger::eTriggertype::Scenechange);
        trigger3->SetScenename(L"IceScene3");

        Trigger* trigger4 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
        trigger4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(192.f, 32.f));
        trigger4->AddComponent<Collider>();
        trigger4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 64.f));
        trigger4->SetType(Trigger::eTriggertype::Scenechange);
        trigger4->SetScenename(L"IceScene14");
	}

	void IceScene2::Update()
	{
		Scene::Update();
	}

	void IceScene2::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}