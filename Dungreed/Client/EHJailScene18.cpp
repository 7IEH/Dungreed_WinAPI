#include "EHJailScene18.h"
#include "EHSceneManager.h"
#include "EHBackGround.h"
#include "EHResources.h"
#include "EHObject.h"
#include "EHPlayer.h"
#include "EHCamera.h"
#include "EHEnemy.h"
#include "EHCollisionManager.h"
#include "EHCanvas.h"
#include "EHObjdata.h"
#include "EHTrigger.h"
#include "EHFloor.h"
#include "EHSlope.h"
#include "EHWall.h"
#include "EHCeil.h"
#include "EHGiantBat.h"
#include "EHJailArchor.h"


namespace EH
{
	JailScene18::JailScene18()
	{
	}

	JailScene18::~JailScene18()
	{
	}

	void JailScene18::Initialize()
	{
		Sound* BGM = Resources::Load<Sound>(L"JailFieldBGM", L"..\\Resources\\Sound\\BGM\\1.JailField.wav");
		SetBGM(BGM);

		SetSize(Math::Vector2<float>(1536.f, 896.f));
	
		Texture* texture = nullptr;
		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		BackGround* JailSubBG18 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailSubBG18->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		JailSubBG18->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
	    texture = Resources::Load<Texture>(L"JailSubBG", L"..\\Resources\\Dungeon\\JailBackGround\\4\\SubBG.bmp");
		JailSubBG18->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailSubBG18->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailBG18 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG18->GetComponent<Transform>()->SetPos(Math::Vector2<float>(768.f, 448.f));
		JailBG18->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1536.f, 896.f));
		texture = Resources::Load<Texture>(L"JailBG18", L"..\\Resources\\Dungeon\\JailBackGround\\18\\JailField18.bmp");
		JailBG18->GetComponent<SpriteRenderer>()->SetImg(texture);

		// Ceil
		Ceil* ceil1 = object::Instantiate<Ceil>(enums::eLayerType::Floor);
		ceil1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(638.f, 96.f));
		ceil1->AddComponent<Collider>();
		ceil1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1148.f, 64.f));
		ceil1->GetComponent<Collider>()->SetAffectedCamera(true);

		// Wall
		Wall* wall1 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(32.f, 416.f));
		wall1->AddComponent<Collider>();
		wall1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 704.f));
		wall1->GetComponent<Collider>()->SetAffectedCamera(true);
		wall1->SetRight(false);

		Wall* wall2 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1184.f, 74.f));
		wall2->AddComponent<Collider>();
		wall2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 100.f));
		wall2->GetComponent<Collider>()->SetAffectedCamera(true);
		wall2->SetRight(false);

		Wall* wall3 = object::Instantiate<Wall>(enums::eLayerType::Floor);
		wall3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1504.f, 256.f));
		wall3->AddComponent<Collider>();
		wall3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 512.f));
		wall3->GetComponent<Collider>()->SetAffectedCamera(true);

		// Floor
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(224.f, 800.f));
		floor1->AddComponent<Collider>();
		floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(320.f, 64.f));
		floor1->GetComponent<Collider>()->SetAffectedCamera(true);
		floor1->SetDownFloor(false);

		Floor* floor2 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(544.f, 736.f));
		floor2->AddComponent<Collider>();
		floor2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(192.f, 64.f));
		floor2->GetComponent<Collider>()->SetAffectedCamera(true);
		floor2->SetDownFloor(false);

		Floor* floor3 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(800.f, 672.f));
		floor3->AddComponent<Collider>();
		floor3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(192.f, 64.f));
		floor3->GetComponent<Collider>()->SetAffectedCamera(true);
		floor3->SetDownFloor(false);

		Floor* floor4 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1060.f, 608.f));
		floor4->AddComponent<Collider>();
		floor4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(192.f, 64.f));
		floor4->GetComponent<Collider>()->SetAffectedCamera(true);
		floor4->SetDownFloor(false);

		Floor* floor5 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1344.f, 544.f));
		floor5->AddComponent<Collider>();
		floor5->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256., 64.f));
		floor5->GetComponent<Collider>()->SetAffectedCamera(true);
		floor5->SetDownFloor(false);

		// Slope
		Slope* slope1 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(416.f, 736.f));
		slope1->AddComponent<Collider>();
		slope1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope1->GetComponent<Collider>()->SetAffectedCamera(true);
		slope1->SetIntercept(1152.f);
		slope1->SetCorrection(90.f);
		slope1->SetRight(true);

		Slope* slope2 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(672.f, 672.f));
		slope2->AddComponent<Collider>();
		slope2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope2->GetComponent<Collider>()->SetAffectedCamera(true);
		slope2->SetIntercept(1344.f);
		slope2->SetCorrection(90.f);
		slope2->SetRight(true);

		Slope* slope3 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(928.f, 608.f));
		slope3->AddComponent<Collider>();
		slope3->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope3->GetComponent<Collider>()->SetAffectedCamera(true);
		slope3->SetIntercept(1536.f);
		slope3->SetCorrection(90.f);
		slope3->SetRight(true);

		Slope* slope4 = object::Instantiate<Slope>(enums::eLayerType::Floor);
		slope4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1184.f, 544.f));
		slope4->AddComponent<Collider>();
		slope4->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 64.f));
		slope4->GetComponent<Collider>()->SetAffectedCamera(true);
		slope4->SetIntercept(1728.f);
		slope4->SetCorrection(90.f);
		slope4->SetRight(true);

		// Trigger
		Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1344.f, 32.f));
		trigger1->AddComponent<Collider>();
		trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 64.f));
		trigger1->SetType(Trigger::eTriggertype::Scenechange);
		trigger1->SetScenename(L"JailScene16");

		// Steel
		Ceil* steel1 = object::Instantiate<Ceil>(enums::eLayerType::Steel);
		steel1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1344.f, 32.f));
		steel1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(264.f, 80.f));
		steel1->AddComponent<Collider>();
		steel1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(256.f, 64.f));
		Animator* ani = steel1->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"SteelOpen", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Ceil\\SteelOpenSheet2.bmp");
		ani->CreateAnimation(L"SteelOpen", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(66.f, 20.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelExit", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Ceil\\SteelExitSheet.bmp");
		ani->CreateAnimation(L"SteelExit", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(66.f, 20.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		texture = Resources::Load<Texture>(L"SteelIdle", L"..\\Resources\\Dungeon\\DungeonStructure\\DungeonSteel\\Ceil\\SteelIdleSheet.bmp");
		ani->CreateAnimation(L"SteelIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(66.f, 20.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);

		// Enemy
		GiantBat* giantbat1 = object::Instantiate<GiantBat>(enums::eLayerType::Enemy);
		giantbat1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(604.f, 348.f));
		giantbat1->GetComponent<Animator>()->PlayAnimation(L"GiantRightIdle", true);

		JailArchor* archor1 = object::Instantiate<JailArchor>(enums::eLayerType::Enemy);
		archor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(232.f, 700.f));
		archor1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		Collider* col = archor1->AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(128.f, 128.f));
		archor1->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"GreySkelRightIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Right\\GraySkelIdle.bmp");
		archor1->GetComponent<Animator>()->CreateAnimation(L"GreySkelRightIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		texture = Resources::Load<Texture>(L"GreySkelLeftIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Left\\GraySkelIdle.bmp");
		archor1->GetComponent<Animator>()->CreateAnimation(L"GreySkelLeftIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		archor1->GetComponent<Animator>()->PlayAnimation(L"GreySkelRightIdle", true);

		JailArchor* archor2 = object::Instantiate<JailArchor>(enums::eLayerType::Enemy);
		archor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(552.f, 636.f));
		archor2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		col = archor2->AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(128.f, 128.f));
		archor2->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"GreySkelRightIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Right\\GraySkelIdle.bmp");
		archor2->GetComponent<Animator>()->CreateAnimation(L"GreySkelRightIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		texture = Resources::Load<Texture>(L"GreySkelLeftIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Left\\GraySkelIdle.bmp");
		archor2->GetComponent<Animator>()->CreateAnimation(L"GreySkelLeftIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		archor2->GetComponent<Animator>()->PlayAnimation(L"GreySkelRightIdle", true);

		JailArchor* archor3 = object::Instantiate<JailArchor>(enums::eLayerType::Enemy);
		archor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(804.f, 572.f));
		archor3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		col = archor3->AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(128.f, 128.f));
		archor3->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"GreySkelRightIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Right\\GraySkelIdle.bmp");
		archor3->GetComponent<Animator>()->CreateAnimation(L"GreySkelRightIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		texture = Resources::Load<Texture>(L"GreySkelLeftIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Left\\GraySkelIdle.bmp");
		archor3->GetComponent<Animator>()->CreateAnimation(L"GreySkelLeftIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		archor3->GetComponent<Animator>()->PlayAnimation(L"GreySkelRightIdle", true);

		JailArchor* archor4 = object::Instantiate<JailArchor>(enums::eLayerType::Enemy);
		archor4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1056.f, 508.f));
		archor4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		col = archor4->AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(128.f, 128.f));
		archor4->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"GreySkelRightIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Right\\GraySkelIdle.bmp");
		archor4->GetComponent<Animator>()->CreateAnimation(L"GreySkelRightIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		texture = Resources::Load<Texture>(L"GreySkelLeftIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Left\\GraySkelIdle.bmp");
		archor4->GetComponent<Animator>()->CreateAnimation(L"GreySkelLeftIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		archor4->GetComponent<Animator>()->PlayAnimation(L"GreySkelRightIdle", true);

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailScene18::Update()
	{
		Scene::Update();
	}

	void JailScene18::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene18", 11);
	}

}