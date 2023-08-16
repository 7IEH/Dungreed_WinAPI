#include "EHJailBossScene.h"
#include "EHSceneManager.h"
#include "EHBackGround.h"
#include "EHResources.h"
#include "EHObject.h"
#include "EHPlayer.h"
#include "EHCamera.h"
#include "EHFloor.h"
#include "EHBoss.h"
#include "EHJailArchor.h"
#include "EHBanshee.h"
#include "EHCanvas.h"
#include "EHCollisionManager.h"
#include "EHIntro.h"
#include "EHWall.h"
#include "EHTrigger.h"

namespace EH
{
	JailBossScene::JailBossScene()
		:
		  mIntro(0)
		, mCheck2{}
		, mCheck1(0)
	{
	}

	JailBossScene::~JailBossScene()
	{
	}

	void JailBossScene::Initialize()
	{
		SetSize(Math::Vector2<float>(1440.f, 1320.f));

		Sound* BGM = Resources::Load<Sound>(L"BOSSBGM1", L"..\\Resources\\Sound\\BGM\\1.JailBoss.wav");
		SetBGM(BGM);
		mBelialLaugh = Resources::Load<Sound>(L"Beliallaugh", L"..\\Resources\\Sound\\Enemy\\JailField\\Belial\\beliallaugh_rev.wav");

		Texture* texture = nullptr;

		BackGround* JailBossBackGround = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBossBackGround->GetComponent<Transform>()->SetPos(Math::Vector2<float>(720.f, 660.f));
		JailBossBackGround->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1440.f, 1320.f));
		texture = Resources::Load<Texture>(L"JailBossBackGround", L"..\\Resources\\Dungeon\\Belial\\Boss.bmp");
		JailBossBackGround->GetComponent<SpriteRenderer>()->SetImg(texture);
		//JailBossBackGround->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

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
		intro3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(200.f, 500.f));
		intro3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(151.f, 118.f));
		texture = Resources::Load<Texture>(L"Name", L"..\\Resources\\Dungeon\\Belial\\Intro\\Name.bmp");
		intro3->GetComponent<SpriteRenderer>()->SetImg(texture);
		intro3->GetComponent<SpriteRenderer>()->SetAlpha(0.f);
		intro3->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// Torch
		BackGround* Torch1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Torch1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(524.f, 804.f));
		Torch1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		texture = Resources::Load<Texture>(L"Torch", L"..\\Resources\\Dungeon\\Belial\\Torch0.png");
		Torch1->GetComponent<SpriteRenderer>()->SetImg(texture);
		//Torch1->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Torch2 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Torch2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(936.f, 804.f));
		Torch2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		texture = Resources::Load<Texture>(L"Torch", L"..\\Resources\\Dungeon\\Belial\\Torch0.png");
		Torch2->GetComponent<SpriteRenderer>()->SetImg(texture);
		//Torch2->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Torch3 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Torch3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(476.f, 320.f));
		Torch3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		texture = Resources::Load<Texture>(L"Torch", L"..\\Resources\\Dungeon\\Belial\\Torch0.png");
		Torch3->GetComponent<SpriteRenderer>()->SetImg(texture);
		//Torch3->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Torch4 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Torch4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(948.f, 320.f));
		Torch4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		texture = Resources::Load<Texture>(L"Torch", L"..\\Resources\\Dungeon\\Belial\\Torch0.png");
		Torch4->GetComponent<SpriteRenderer>()->SetImg(texture);
		//Torch4->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// Floor
		Floor* JailFloor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		JailFloor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(718.f, 224.f));
		JailFloor1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		texture = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor1->AddComponent<SpriteRenderer>();
		JailFloor1->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailFloor1->AddComponent<Collider>();
		JailFloor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(188.f, 48.f));

		Floor* JailFloor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		JailFloor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1166.f, 324.f));
		JailFloor2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		texture = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor2->AddComponent<SpriteRenderer>();
		JailFloor2->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailFloor2->AddComponent<Collider>();
		JailFloor2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(188.f, 48.f));

		Floor* JailFloor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		JailFloor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(294.f, 324.f));
		JailFloor3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		texture = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor3->AddComponent<SpriteRenderer>();
		JailFloor3->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailFloor3->AddComponent<Collider>();
		JailFloor3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(188.f, 48.f));

		Floor* JailFloor4 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		JailFloor4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1166.f, 552.f));
		JailFloor4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		texture = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor4->AddComponent<SpriteRenderer>();
		JailFloor4->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailFloor4->AddComponent<Collider>();
		JailFloor4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(188.f, 48.f));

		Floor* JailFloor5 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		JailFloor5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(294.f, 552.f));
		JailFloor5->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		texture = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor5->AddComponent<SpriteRenderer>();
		JailFloor5->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailFloor5->AddComponent<Collider>();
		JailFloor5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(188.f, 48.f));

		Floor* JailFloor6 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		JailFloor6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1094.f, 784.f));
		JailFloor6->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		texture = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor6->AddComponent<SpriteRenderer>();
		JailFloor6->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailFloor6->AddComponent<Collider>();
		JailFloor6->GetComponent<Collider>()->SetScale(Math::Vector2<float>(188.f, 48.f));

		Floor* JailFloor7 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		JailFloor7->GetComponent<Transform>()->SetPos(Math::Vector2<float>(334.f, 784.f));
		JailFloor7->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		texture = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor7->AddComponent<SpriteRenderer>();
		JailFloor7->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailFloor7->AddComponent<Collider>();
		JailFloor7->GetComponent<Collider>()->SetScale(Math::Vector2<float>(188.f, 48.f));

		Floor* JailFloor8 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		JailFloor8->GetComponent<Transform>()->SetPos(Math::Vector2<float>(734.f, 996.f));
		JailFloor8->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		texture = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor8->AddComponent<SpriteRenderer>();
		JailFloor8->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailFloor8->AddComponent<Collider>();
		JailFloor8->GetComponent<Collider>()->SetScale(Math::Vector2<float>(188.f, 48.f));

		Floor* JailFloor9 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		JailFloor9->GetComponent<Transform>()->SetPos(Math::Vector2<float>(718.f, 1160.f));
		JailFloor9->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1436.f, 64.f));
		JailFloor9->AddComponent<Collider>();
		JailFloor9->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1436.f, 64.f));
		JailFloor9->GetComponent<Collider>()->SetAffectedCamera(true);

		// Trigger
		Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1408.f, 1000.f));
		trigger1->AddComponent<Collider>();
		trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger1->SetType(Trigger::eTriggertype::Scenechange);
		trigger1->SetScenename(L"JailAfterBossScene");

		// Steel
		Wall* steel1 = object::Instantiate<Wall>(enums::eLayerType::Steel);
		steel1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 1000.f));
		steel1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 264.f));
		steel1->AddComponent<Collider>();
		steel1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 264.f));
		steel1->SetRight(false);
		Animator* ani = steel1->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"SteelLeftOpen", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Left\\SteelOpenSheet.bmp");
		ani->CreateAnimation(L"SteelOpen", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 66.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelLeftExit", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Left\\SteelExitSheet.bmp");
		ani->CreateAnimation(L"SteelExit", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 66.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelLeftIdle", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Left\\SteelIdleSheet.bmp");
		ani->CreateAnimation(L"SteelIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 66.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

		Wall* steel2 = object::Instantiate<Wall>(enums::eLayerType::Steel);
		steel2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1408.f, 1000.f));
		steel2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 264.f));
		steel2->AddComponent<Collider>();
		steel2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		steel2->SetRight(true);
		ani = steel2->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"SteelRightOpen", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Right\\SteelOpenSheet.bmp");
		ani->CreateAnimation(L"SteelOpen", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 66.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelRightExit", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Right\\SteelExitSheet.bmp");
		ani->CreateAnimation(L"SteelExit", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 66.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelRightIdle", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Right\\SteelIdleSheet.bmp");
		ani->CreateAnimation(L"SteelIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 66.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

		// Boss
		Boss* Boss1 = object::Instantiate<Boss>(enums::eLayerType::Enemy);
		Boss1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(704.f, 598.f));
		Boss1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(280.f, 396.f));
		texture = Resources::Load<Texture>(L"BossIdle", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\Idle\\SkellBossIdleSheet.bmp");
		Boss1->AddComponent<Animator>();
		Boss1->GetComponent<Animator>()->CreateAnimation(L"BossIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(70.f, 99.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		Boss1->GetComponent<Animator>()->PlayAnimation(L"BossIdle", true);
		Boss1->GetComponent<Animator>()->SetAffectedCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(256.f, 700.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		Boss1->SetTarget(player);
		SetPlayer(player);

		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Floor, true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Bullet, true);
	}

	void JailBossScene::Update()
	{
		Scene::Update();
		mCheckTime += Time::GetDeltaTime();
		if (mIntro == 0 && 1.f < mCheckTime)
		{
			Camera::SetTarget(nullptr);
			Camera::SetLookAt(Math::Vector2<float>(704.f, 598.f));
			mBelialLaugh->Play(false);
			mIntro++;
		}
		else if (9.f < mCheckTime)
		{
			Camera::SetTarget(GetPlayer());
		}
		else if (5.f < mCheckTime)
		{
			Math::Vector2<float> camerapos = Camera::GetLookAt();
			Math::Vector2<float> playerpos = GetPlayer()->GetComponent<Transform>()->Getpos();

			if (mCheck1 == 0)
			{
				mCheck2 = playerpos - camerapos;
				mCheck1++;
			}
			
			camerapos += mCheck2.normalized<float>() * 300.f * Time::GetDeltaTime();
			Camera::SetLookAt(camerapos);
		}
	}

	void JailBossScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailBossScene", 13);
	}
}