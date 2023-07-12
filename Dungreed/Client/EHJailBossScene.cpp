#include "EHJailBossScene.h"
#include "EHSceneManager.h"
#include "EHBackGround.h"
#include "EHResources.h"
#include "EHObject.h"


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
		BackGround* JailBossBackGround = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBossBackGround->GetComponent<Transform>()->SetPos(Math::Vector2<float>(720.f, 660.f));
		JailBossBackGround->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1440.f, 1320.f));
		Texture* temp = Resources::Load<Texture>(L"JailBossBackGround", L"..\\Resources\\Dungeon\\Belial\\Boss.png");
		JailBossBackGround->GetComponent<SpriteRenderer>()->SetImg(temp);
		JailBossBackGround->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// Torch
		BackGround* Torch1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Torch1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(524.f, 804.f));
		Torch1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		temp = Resources::Load<Texture>(L"Torch", L"..\\Resources\\Dungeon\\Belial\\Torch0.png");
		Torch1->GetComponent<SpriteRenderer>()->SetImg(temp);
		Torch1->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Torch2 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Torch2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(936.f, 804.f));
		Torch2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		temp = Resources::Load<Texture>(L"Torch", L"..\\Resources\\Dungeon\\Belial\\Torch0.png");
		Torch2->GetComponent<SpriteRenderer>()->SetImg(temp);
		Torch2->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Torch3 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Torch3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(476.f, 320.f));
		Torch3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		temp = Resources::Load<Texture>(L"Torch", L"..\\Resources\\Dungeon\\Belial\\Torch0.png");
		Torch3->GetComponent<SpriteRenderer>()->SetImg(temp);
		Torch3->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Torch4 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Torch4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(948.f, 320.f));
		Torch4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		temp = Resources::Load<Texture>(L"Torch", L"..\\Resources\\Dungeon\\Belial\\Torch0.png");
		Torch4->GetComponent<SpriteRenderer>()->SetImg(temp);
		Torch4->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// Floor
		BackGround* JailFloor1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailFloor1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(718.f, 224.f));
		JailFloor1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		temp = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor1->GetComponent<SpriteRenderer>()->SetImg(temp);
		JailFloor1->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailFloor2 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailFloor2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1166.f, 324.f));
		JailFloor2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		temp = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor2->GetComponent<SpriteRenderer>()->SetImg(temp);
		JailFloor2->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailFloor3 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailFloor3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(294.f, 324.f));
		JailFloor3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		temp = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor3->GetComponent<SpriteRenderer>()->SetImg(temp);
		JailFloor3->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailFloor4 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailFloor4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1166.f, 552.f));
		JailFloor4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		temp = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor4->GetComponent<SpriteRenderer>()->SetImg(temp);
		JailFloor4->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailFloor5 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailFloor5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(294.f, 552.f));
		JailFloor5->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		temp = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor5->GetComponent<SpriteRenderer>()->SetImg(temp);
		JailFloor5->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailFloor6 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailFloor6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1094.f, 784.f));
		JailFloor6->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		temp = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor6->GetComponent<SpriteRenderer>()->SetImg(temp);
		JailFloor6->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailFloor7 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailFloor7->GetComponent<Transform>()->SetPos(Math::Vector2<float>(334.f, 784.f));
		JailFloor7->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		temp = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor7->GetComponent<SpriteRenderer>()->SetImg(temp);
		JailFloor7->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailFloor8 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailFloor8->GetComponent<Transform>()->SetPos(Math::Vector2<float>(734.f, 996.f));
		JailFloor8->GetComponent<Transform>()->SetScale(Math::Vector2<float>(188.f, 48.f));
		temp = Resources::Load<Texture>(L"JailFloor1", L"..\\Resources\\Dungeon\\Belial\\JailFloor.png");
		JailFloor8->GetComponent<SpriteRenderer>()->SetImg(temp);
		JailFloor8->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// Boss
		BackGround* Boss1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Boss1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(704.f, 598.f));
		Boss1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(280.f, 396.f));
		temp = Resources::Load<Texture>(L"Boss1", L"..\\Resources\\Enemy\\Boss\\SkellBoss\\Idle\\SkellBossIdle0.png");
		Boss1->GetComponent<SpriteRenderer>()->SetImg(temp);
		Boss1->GetComponent<SpriteRenderer>()->SetAffectCamera(false);
	}

	void JailBossScene::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
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