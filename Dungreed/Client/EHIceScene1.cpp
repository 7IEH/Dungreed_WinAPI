#include "EHIceScene1.h"
#include "EHResources.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHFloor.h"
#include "EHCeil.h"
#include "EHWall.h"
#include "EHTrigger.h"
#include "EHPlayer.h"
#include "EHCamera.h"
#include "EHSkelIceMagician.h"
#include "EHBigGrayIceSkel.h"

namespace EH
{
	void IceScene1::Initialize()
	{
		// Sound
		Sound* BGM = Resources::Load<Sound>(L"IceFieldBGM", L"..\\Resources\\Sound\\BGM\\2.IceField.wav");
		SetBGM(BGM);
		mEnterSound = Resources::Load<Sound>(L"JailDoorSound", L"..\\Resources\\Sound\\Structure\\JailDoorSound.wav");

		SetSize(Math::Vector2<float>(1280.f, 1216.f));

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(820.f, 300.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// SceneChanger Player
		SetPlayer(player);

		BackGround* IceSubBG = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		IceSubBG->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 520.f));
		IceSubBG->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 1040.f));
		Texture* texture = Resources::Load<Texture>(L"IceSubBG", L"..\\Resources\\Dungeon\\IceBackGround\\IceLayer\\BGLayer_0.bmp");
		IceSubBG->GetComponent<SpriteRenderer>()->SetImg(texture);
		IceSubBG->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* IceBG1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		IceBG1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 608.f));
		IceBG1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 1216.f));
		texture = Resources::Load<Texture>(L"IceBG1", L"..\\Resources\\Dungeon\\IceBackGround\\1\\IceScene1.bmp");
		IceBG1->GetComponent<SpriteRenderer>()->SetImg(texture);
		IceBG1->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Floor
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(512.f, 1120.f));
		floor1->AddComponent<Collider>();
		floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1024.f, 64.f));
		floor1->GetComponent<Collider>()->SetAffectedCamera(true);
		floor1->SetDownFloor(false);

		Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(928.f, 936.f));
		floor2->AddComponent<Collider>();
		floor2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(192.f, 56.f));
		floor2->GetComponent<Collider>()->SetAffectedCamera(true);
		floor2->SetDownFloor(true);

		Floor* floor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1056.f, 732.f));
		floor3->AddComponent<Collider>();
		floor3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(448.f, 56.f));
		floor3->GetComponent<Collider>()->SetAffectedCamera(true);
		floor3->SetDownFloor(true);

		// Ceil
		Ceil* ceil1 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(62.f, 800.f));
		ceil1->AddComponent<Collider>();
		ceil1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 64.f));
		ceil1->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil2 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(158.f, 480.f));
		ceil2->AddComponent<Collider>();
		ceil2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(60.f, 64.f));
		ceil2->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil3 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(222.f, 416.f));
		ceil3->AddComponent<Collider>();
		ceil3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(60.f, 64.f));
		ceil3->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil4 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(286.f, 224.f));
		ceil4->AddComponent<Collider>();
		ceil4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(60.f, 64.f));
		ceil4->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil5 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(382.f, 160.f));
		ceil5->AddComponent<Collider>();
		ceil5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 64.f));
		ceil5->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil6 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(510.f, 96.f));
		ceil6->AddComponent<Collider>();
		ceil6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(124.f, 64.f));
		ceil6->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil7 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil7->GetComponent<Transform>()->SetPos(Math::Vector2<float>(648.f, 32.f));
		ceil7->AddComponent<Collider>();
		ceil7->GetComponent<Collider>()->SetScale(Math::Vector2<float>(384.f, 64.f));
		ceil7->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil8 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil8->GetComponent<Transform>()->SetPos(Math::Vector2<float>(994.f, 96.f));
		ceil8->AddComponent<Collider>();
		ceil8->GetComponent<Collider>()->SetScale(Math::Vector2<float>(60.f, 64.f));
		ceil8->GetComponent<Collider>()->SetAffectedCamera(true);

		Ceil* ceil9 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil9->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1154.f, 416.f));
		ceil9->AddComponent<Collider>();
		ceil9->GetComponent<Collider>()->SetScale(Math::Vector2<float>(252.f, 64.f));
		ceil9->GetComponent<Collider>()->SetAffectedCamera(true);


		// Wall
		Wall* wall1 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(96.f, 640.f));
		wall1->AddComponent<Collider>();
		wall1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 384.f));
		wall1->GetComponent<Collider>()->SetAffectedCamera(true);
		wall1->SetRight(false);

		Wall* wall2 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(160.f, 448.f));
		wall2->AddComponent<Collider>();
		wall2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 128.f));
		wall2->GetComponent<Collider>()->SetAffectedCamera(true);
		wall2->SetRight(false);

		Wall* wall3 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(216.f, 320.f));
		wall3->AddComponent<Collider>();
		wall3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		wall3->GetComponent<Collider>()->SetAffectedCamera(true);
		wall3->SetRight(false);

		Wall* wall4 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(288.f, 160.f));
		wall4->AddComponent<Collider>();
		wall4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 192.f));
		wall4->GetComponent<Collider>()->SetAffectedCamera(true);
		wall4->SetRight(false);

		Wall* wall5 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(416.f, 96.f));
		wall5->AddComponent<Collider>();
		wall5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 192.f));
		wall5->GetComponent<Collider>()->SetAffectedCamera(true);
		wall5->SetRight(false);

		Wall* wall6 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(544.f, 32.f));
		wall6->AddComponent<Collider>();
		wall6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 192.f));
		wall6->GetComponent<Collider>()->SetAffectedCamera(true);
		wall6->SetRight(false);

		Wall* wall7 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall7->GetComponent<Transform>()->SetPos(Math::Vector2<float>(992.f, 32.f));
		wall7->AddComponent<Collider>();
		wall7->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 192.f));
		wall7->GetComponent<Collider>()->SetAffectedCamera(true);
		wall7->SetRight(true);

		Wall* wall8 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall8->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1056.f, 256.f));
		wall8->AddComponent<Collider>();
		wall8->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 384.f));
		wall8->GetComponent<Collider>()->SetAffectedCamera(true);
		wall8->SetRight(true);

		Wall* wall9 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall9->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1056.f, 900.f));
		wall9->AddComponent<Collider>();
		wall9->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 376.f));
		wall9->GetComponent<Collider>()->SetAffectedCamera(true);
		wall9->SetRight(true);

		// Trigger
		Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 960.f));
		trigger1->AddComponent<Collider>();
		trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger1->SetType(Trigger::eTriggertype::Scenechange);
		trigger1->SetScenename(L"IceScene2");

		Trigger* trigger2 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1248.f, 576.f));
		trigger2->AddComponent<Collider>();
		trigger2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger2->SetType(Trigger::eTriggertype::Scenechange);
		trigger2->SetScenename(L"IceScene17");

		GameObject* obj = object::Instantiate<GameObject>(enums::eLayerType::BackGround);
		Transform* tr = obj->GetComponent<Transform>();
		Animator* ani = obj->AddComponent<Animator>();
		tr->SetPos(Math::Vector2<float>(552.f, 958.f));
		tr->SetScale(Math::Vector2<float>(228.f, 260.f));
		texture = Resources::Load<Texture>(L"IceDoor", L"..\\Resources\\Dungeon\\IceBackGround\\IceLayer\\IceDoor.bmp");
		ani->CreateAnimation(L"IceDoor", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(57.f, 65.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		ani->PlayAnimation(L"IceDoor", false);

		// Enemy
	    /*SkelIceMagician* magician1 = object::Instantiate<SkelIceMagician>(enums::eLayerType::Enemy);
		Transform* tr = magician1->GetComponent<Transform>();
		tr->SetPos(Math::Vector2<float>(400.f, 500.f));
		tr->SetScale(Math::Vector2<float>(128.f, 120.f));*/

		/*BigGrayIceSkel* biggrayiceskel = object::Instantiate<BigGrayIceSkel>(enums::eLayerType::Enemy);
		Transform* tr = biggrayiceskel->GetComponent<Transform>();
		tr->SetPos(Math::Vector2<float>(400.f, 300.f));
		tr->SetScale(Math::Vector2<float>(132.f, 120.f));*/

		Camera::SetTarget(player);
	}

	void IceScene1::Update()
	{
		Scene::Update();
		if (mCheck1 == 0)
		{
			mEnterSound->Play(false);
			mCheck1++;
		}
	}

	void IceScene1::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}
