#include "EHIceScene3.h"
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