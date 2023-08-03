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

		Enemy* testenemy = object::Instantiate<Enemy>(enums::eLayerType::Enemy);
		testenemy->GetComponent<Transform>()->SetPos(Math::Vector2<float>(400.f, 400.f));
		testenemy->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		texture = Resources::Load<Texture>(L"Bat", L"..\\Resources\\Enemy\\JailField\\Bat\\Bat\\Idle\\BatSheet.bmp");
		testenemy->AddComponent<Animator>();
		testenemy->GetComponent<Animator>()->CreateAnimation(L"Bat", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		testenemy->GetComponent<Animator>()->PlayAnimation(L"Bat", true);
		testenemy->GetComponent<Animator>()->SetAffectedCamera(true);
		testenemy->AddComponent<Collider>();
		testenemy->GetComponent<Collider>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		testenemy->GetComponent<Collider>()->SetAffectedCamera(true);

		Enemy* testenemy2 = object::Instantiate<Enemy>(enums::eLayerType::Enemy);
		testenemy2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(800.f, 400.f));
		testenemy2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		texture = Resources::Load<Texture>(L"Bat", L"..\\Resources\\Enemy\\JailField\\Bat\\Bat\\Idle\\BatSheet.bmp");
		testenemy2->AddComponent<Animator>();
		testenemy2->GetComponent<Animator>()->CreateAnimation(L"Bat", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		testenemy2->GetComponent<Animator>()->PlayAnimation(L"Bat", true);
		testenemy2->GetComponent<Animator>()->SetAffectedCamera(true);
		testenemy2->AddComponent<Collider>();
		testenemy2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		testenemy2->GetComponent<Collider>()->SetAffectedCamera(true);

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

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailScene18::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailPrevBossScene");
		}
		Scene::Update();
	}

	void JailScene18::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene18", 11);
	}

}