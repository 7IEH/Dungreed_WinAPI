#include "EHIcePrevBossScene.h"
#include "EHResources.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHFloor.h"
#include "EHCeil.h"
#include "EHWall.h"
#include "EHTrigger.h"
#include "EHPlayer.h"
#include "EHCamera.h"

namespace EH
{
	void IcePrevBossScene::Initialize()
	{
		// Sound
		Sound* BGM = Resources::Load<Sound>(L"IceFieldBGM", L"..\\Resources\\Sound\\BGM\\2.IceField.wav");
		SetBGM(BGM);
		mEnterSound = Resources::Load<Sound>(L"JailDoorSound", L"..\\Resources\\Sound\\Structure\\JailDoorSound.wav");

		SetSize(Math::Vector2<float>(1280.f, 720.f));

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
		IceBG1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		IceBG1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		texture = Resources::Load<Texture>(L"PrevBossIceBG", L"..\\Resources\\Dungeon\\IceBackGround\\PrevBossScene\\PrevBossIceScene.bmp");
		IceBG1->GetComponent<SpriteRenderer>()->SetImg(texture);
		IceBG1->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		GameObject* obj = object::Instantiate<GameObject>(enums::eLayerType::BackGround);
		Transform* tr = obj->GetComponent<Transform>();
		Animator* ani = obj->AddComponent<Animator>();
		tr->SetPos(Math::Vector2<float>(320.f, 462.f));
		tr->SetScale(Math::Vector2<float>(228.f,260.f));
		texture = Resources::Load<Texture>(L"IceDoor", L"..\\Resources\\Dungeon\\IceBackGround\\IceLayer\\IceDoor.bmp");
		ani->CreateAnimation(L"IceDoor", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(57.f, 65.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
		ani->PlayAnimation(L"IceDoor", false);

		// Floor
		Floor* floor1 = object::Instantiate<Floor>(enums::eLayerType::Floor);
		floor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(704.f, 624.f));
		floor1->AddComponent<Collider>();
		floor1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(1152.f, 64.f));
		floor1->GetComponent<Collider>()->SetAffectedCamera(true);
		floor1->SetDownFloor(false);

		// Trigger
		Trigger* trigger1 = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
		trigger1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1248.f, 464.f));
		trigger1->AddComponent<Collider>();
		trigger1->GetComponent<Collider>()->SetScale(Math::Vector2<float>(64.f, 256.f));
		trigger1->SetType(Trigger::eTriggertype::Scenechange);
		trigger1->SetScenename(L"IceBossScene");
	}

	void IcePrevBossScene::Update()
	{
		Scene::Update();
		if (mCheck1 == 0)
		{
			mEnterSound->Play(false);
			mCheck1++;
		}
	}

	void IcePrevBossScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}