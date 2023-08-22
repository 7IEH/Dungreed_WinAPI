#include "EHIceBossScene.h"
#include "EHResources.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHFloor.h"
#include "EHCeil.h"
#include "EHWall.h"
#include "EHTrigger.h"
#include "EHPlayer.h"
#include "EHCamera.h"
#include "EHIntro.h"
#include "EHNiflheim.h"

namespace EH
{
	void IceBossScene::Initialize()
	{
		// Sound
		Sound* BGM = Resources::Load<Sound>(L"IceBossBGM", L"..\\Resources\\Sound\\BGM\\2.IceBoss.wav");
		SetBGM(BGM);
		//mEnterSound = Resources::Load<Sound>(L"JailDoorSound", L"..\\Resources\\Sound\\Structure\\JailDoorSound.wav");

		SetSize(Math::Vector2<float>(1984.f, 1024.f));

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(410.f, 200.f));
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
		IceBG1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(992.f, 512.f));
		IceBG1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1984.f, 1024.f));
		texture = Resources::Load<Texture>(L"IceBossBG", L"..\\Resources\\Dungeon\\IceBackGround\\BossScene\\IceBossScene.bmp");
		IceBG1->GetComponent<SpriteRenderer>()->SetImg(texture);
		IceBG1->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Intro
		Intro* intro1 = object::Instantiate<Intro>(enums::eLayerType::Detect);
		intro1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 45.f));
		intro1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 90.f));
		texture = Resources::Load<Texture>(L"introupper", L"..\\Resources\\Dungeon\\Belial\\Intro\\Upper.bmp");
		intro1->GetComponent<SpriteRenderer>()->SetImg(texture);
		intro1->GetComponent<SpriteRenderer>()->SetAlpha(0.f);
		intro1->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		Intro* intro2 = object::Instantiate<Intro>(enums::eLayerType::Detect);
		intro2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 642.f));
		intro2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 156.f));
		texture = Resources::Load<Texture>(L"introdown", L"..\\Resources\\Dungeon\\Belial\\Intro\\Down.bmp");
		intro2->GetComponent<SpriteRenderer>()->SetImg(texture);
		intro2->GetComponent<SpriteRenderer>()->SetAlpha(0.f);
		intro2->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		Intro* intro3 = object::Instantiate<Intro>(enums::eLayerType::Detect);
		intro3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(200.f, 450.f));
		intro3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(298.f, 186.f));
		texture = Resources::Load<Texture>(L"NiflheimName", L"..\\Resources\\Dungeon\\Niflheim\\Name.bmp");
		intro3->GetComponent<SpriteRenderer>()->SetImg(texture);
		intro3->GetComponent<SpriteRenderer>()->SetAlpha(0.f);
		intro3->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// Floor
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(960.f, 928.f));
		floor1->AddComponent<Collider>();
		floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1920.f, 64.f));
		floor1->GetComponent<Collider>()->SetAffectedCamera(true);
		floor1->SetDownFloor(false);

		Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1952.f, 416.f));
		floor2->AddComponent<Collider>();
		floor2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		floor2->GetComponent<Collider>()->SetAffectedCamera(true);
		floor2->SetDownFloor(false);

		Floor* floor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(386.f, 476.f));
		floor3->AddComponent<Collider>();
		floor3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(252.f, 56.f));
		floor3->GetComponent<Collider>()->SetAffectedCamera(true);
		floor3->SetDownFloor(false);

		Floor* floor4 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(386.f, 616.f));
		floor4->AddComponent<Collider>();
		floor4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(252.f, 56.f));
		floor4->GetComponent<Collider>()->SetAffectedCamera(true);
		floor4->SetDownFloor(false);

		Floor* floor5 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1626.f, 476.f));
		floor5->AddComponent<Collider>();
		floor5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(252.f, 56.f));
		floor5->GetComponent<Collider>()->SetAffectedCamera(true);
		floor5->SetDownFloor(false);

		Floor* floor6 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1626.f, 616.f));
		floor6->AddComponent<Collider>();
		floor6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(252.f, 56.f));
		floor6->GetComponent<Collider>()->SetAffectedCamera(true);
		floor6->SetDownFloor(false);

		Floor* floor7 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor7->GetComponent<Transform>()->SetPos(Math::Vector2<float>(994.f, 740.f));
		floor7->AddComponent<Collider>();
		floor7->GetComponent<Collider>()->SetScale(Math::Vector2<float>(572.f, 56.f));
		floor7->GetComponent<Collider>()->SetAffectedCamera(true);
		floor7->SetDownFloor(false);

		Floor* floor8= object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor8->GetComponent<Transform>()->SetPos(Math::Vector2<float>(994.f, 532.f));
		floor8->AddComponent<Collider>();
		floor8->GetComponent<Collider>()->SetScale(Math::Vector2<float>(572.f, 56.f));
		floor8->GetComponent<Collider>()->SetAffectedCamera(true);
		floor8->SetDownFloor(false);

		Floor* floor9 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor9->GetComponent<Transform>()->SetPos(Math::Vector2<float>(994.f, 348.f));
		floor9->AddComponent<Collider>();
		floor9->GetComponent<Collider>()->SetScale(Math::Vector2<float>(572.f, 56.f));
		floor9->GetComponent<Collider>()->SetAffectedCamera(true);
		floor9->SetDownFloor(false);

		// Steel
		Wall* steel2 = object::Instantiate<Wall>(enums::eLayerType::Steel);
		steel2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(40.f, 772.f));
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
		steel3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1944.f, 260.f));
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
		Niflheim* nifleheim = object::Instantiate<Niflheim>(enums::eLayerType::Enemy);
		Transform* tr = nifleheim->GetComponent<Transform>();
		tr->SetPos(Math::Vector2<float>(992.f, 520.f));
		tr->SetScale(Math::Vector2<float>(168.f, 132.f));
	}

	void IceBossScene::Update()
	{
		Scene::Update();
		mCheckTime += Time::GetDeltaTime();
		mCheckTime += Time::GetDeltaTime();
		if (mIntro == 0 && 2.f < mCheckTime)
		{
			Camera::SetLookAt(Math::Vector2<float>(992.f, 512.f));
			mIntro++;
		}
		else if (mIntro == 1 && 11.f < mCheckTime)
		{
			Camera::SetTarget(GetPlayer());
			mCheck3++;
		}
		else if (mIntro == 1 && 6.f < mCheckTime)
		{
			Math::Vector2<float> camerapos = Camera::GetLookAt();
			Math::Vector2<float> playerpos = GetPlayer()->GetComponent<Transform>()->Getpos();

			if (mCheck3 == 0)
			{
				mCheck2 = playerpos - camerapos;
				mCheck3++;
			}

			camerapos += mCheck2.normalized<float>() * 300.f * Time::GetDeltaTime();
			Camera::SetLookAt(camerapos);
		}
		else if (mIntro == 0 && 1.f < mCheckTime)
		{
			Camera::SetTarget(nullptr);
			Math::Vector2<float> camerapos = Camera::GetLookAt();
			Math::Vector2<float> playerpos = GetPlayer()->GetComponent<Transform>()->Getpos();

			if (mCheck1 == 0)
			{
				mCheck2 = camerapos - playerpos;
				mCheck1++;
			}

			camerapos += mCheck2.normalized<float>() * 300.f * Time::GetDeltaTime();
			Camera::SetLookAt(camerapos);
		}
	}

	void IceBossScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}