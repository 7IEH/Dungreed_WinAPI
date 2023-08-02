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

namespace EH
{
	JailBossScene::JailBossScene()
	{
	}

	JailBossScene::~JailBossScene()
	{
	}

	void JailBossScene::Initialize()
	{
		SetSize(Math::Vector2<float>(1440.f, 1320.f));

		Sound* BGM = Resources::Load<Sound>(L"BOSSBGM1",L"..\\Resources\\Sound\\BGM\\1.JailBoss.wav");
		SetBGM(BGM);

		Texture* texture = nullptr;

		BackGround* JailBossBackGround = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBossBackGround->GetComponent<Transform>()->SetPos(Math::Vector2<float>(720.f, 660.f));
		JailBossBackGround->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1440.f, 1320.f));
		texture = Resources::Load<Texture>(L"JailBossBackGround", L"..\\Resources\\Dungeon\\Belial\\Boss.bmp");
		JailBossBackGround->GetComponent<SpriteRenderer>()->SetImg(texture);
		//JailBossBackGround->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

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
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(256.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		Boss1->SetTarget(player);
		SetPlayer(player);
		/*JailArchor* archor1 = object::Instantiate<JailArchor>(enums::eLayerType::Enemy);
		archor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(400.f, 600.f));
		archor1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		archor1->AddComponent<Animator>();
		temp = Resources::Load<Texture>(L"GreySkelIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\GraySkelIdle.png");
		archor1->GetComponent<Animator>()->CreateAnimation(L"GreySkelIdle", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		archor1->GetComponent<Animator>()->PlayAnimation(L"GreySkelIdle", true);
		archor1->SetTarget(player);*/

		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Floor,true);
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Player, enums::eLayerType::Bullet, true);
	}

	void JailBossScene::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"TitleScene");
		}
		Scene::Update();
	}

	void JailBossScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailBossScene", 13);
	}
}