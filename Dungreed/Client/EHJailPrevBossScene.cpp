#include "EHJailPrevBossScene.h"
#include "EHSceneManager.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHTexture.h"
#include "EHResources.h"
#include "EHPlayer.h"
#include "EHCamera.h"
#include "EHCanvas.h"
#include "EHFloor.h"
#include "EHWall.h"
#include "EHTrigger.h"

namespace EH
{
	JailPrevBossScene::JailPrevBossScene()
		:
		  mCheck1(0)
		, mEnterSound(nullptr)
	{
	}

	JailPrevBossScene::~JailPrevBossScene()
	{
	}

	void JailPrevBossScene::Initialize()
	{
		Sound* BGM = Resources::Load<Sound>(L"JailFieldBGM", L"..\\Resources\\Sound\\BGM\\1.JailField.wav");
		SetBGM(BGM);

		SetSize(Math::Vector2<float>(1400.f, 720.f));
		
		mEnterSound = Resources::Load<Sound>(L"JailDoorSound", L"..\\Resources\\Sound\\Structure\\JailDoorSound.wav");

		Texture* texture = nullptr;

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(300.f, 300.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// SceneChanger Player
		SetPlayer(player);

		BackGround* JailBossPrevBackGround = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBossPrevBackGround->GetComponent<Transform>()->SetPos(Math::Vector2<float>(700.f,360.f));
		JailBossPrevBackGround->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1400.f,720.f));
		texture = Resources::Load<Texture>(L"JailBossPrevBackGround", L"..\\Resources\\Dungeon\\Belial\\BossPrev.bmp");
		JailBossPrevBackGround->GetComponent<SpriteRenderer>()->SetImg(texture);
		//JailBossPrevBackGround->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Torch1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Torch1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(252.f, 380.f));
		Torch1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		texture = Resources::Load<Texture>(L"Torch", L"..\\Resources\\Dungeon\\Belial\\Torch0.png");
		Torch1->GetComponent<SpriteRenderer>()->SetImg(texture);
		//Torch1->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Torch2 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Torch2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(704.f, 380.f));
		Torch2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		texture = Resources::Load<Texture>(L"Torch", L"..\\Resources\\Dungeon\\Belial\\Torch0.png");
		Torch2->GetComponent<SpriteRenderer>()->SetImg(texture);
		//Torch2->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Torch3 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Torch3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1160.f, 380.f));
		Torch3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		texture = Resources::Load<Texture>(L"Torch", L"..\\Resources\\Dungeon\\Belial\\Torch0.png");
		Torch3->GetComponent<SpriteRenderer>()->SetImg(texture);
		//Torch3->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		GameObject* door1 = object::Instantiate<GameObject>(enums::eLayerType::UI);
		door1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(482.f, 398.f));
		door1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(228.f, 260.f));
		Animator* ani = door1->AddComponent<Animator>();
		texture = Resources::Load<Texture>(L"JailDoorClose", L"..\\Resources\\Dungeon\\JailDoorSheet.bmp");
		ani->CreateAnimation(L"JailDoorClose", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(57.f, 65.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		ani->PlayAnimation(L"JailDoorClose", false);

		BackGround* TortureTable1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		TortureTable1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(926.f, 490.f));
		TortureTable1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(180.f, 76.f));
		texture = Resources::Load<Texture>(L"TortureTable2", L"..\\Resources\\Dungeon\\Belial\\TortureTable1.png");
		TortureTable1->GetComponent<SpriteRenderer>()->SetImg(texture);
		//TortureTable1->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Skull1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Skull1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1086.f, 514.f));
		Skull1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(60.f, 28.f));
		texture = Resources::Load<Texture>(L"Skull2", L"..\\Resources\\Dungeon\\Belial\\Skull1.png");
		Skull1->GetComponent<SpriteRenderer>()->SetImg(texture);
		//Skull1->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// Structure
		// Floor
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(732.f, 560.f));
		floor1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1336.f, 64.f));
		floor1->AddComponent<Collider>();
		floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1336.f, 64.f));
		floor1->GetComponent<Collider>()->SetAffectedCamera(true);
		floor1->SetDownFloor(false);

		Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1368.f, 400.f));
		trigger1->AddComponent<Collider>();
		trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger1->SetType(Trigger::eTriggertype::Scenechange);
		trigger1->SetScenename(L"JailBossScene");
	}

	void JailPrevBossScene::Update()
	{
		Scene::Update();
		if (mCheck1 == 0)
		{
			mEnterSound->Play(false);
			mCheck1++;
		}
	}

	void JailPrevBossScene::Render(HDC hdc)
	{
		HBRUSH hNewBrush = (HBRUSH)CreateSolidBrush(RGB(51, 49, 67));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush);

		HPEN hNewPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(51, 49, 67));
		HPEN hOldPen = (HPEN)SelectObject(hdc, hNewPen);

		Rectangle(hdc, -1, -1, 1280, 720);

		SelectObject(hdc, hOldBrush);
		SelectObject(hdc, hOldPen);

		DeleteObject(hNewBrush);
		DeleteObject(hNewPen);
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailPrevScene", 13);
	}
}