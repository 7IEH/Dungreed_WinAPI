#include "EHJailScene.h"
#include "EHSceneManager.h"
#include "EHBackGround.h"
#include "EHResources.h"
#include "EHObject.h"

namespace EH
{
	JailScene::JailScene()
	{
	}

	JailScene::~JailScene()
	{
	}

	void JailScene::Initialize()
	{
		BackGround* JailBossPrevBackGround = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBossPrevBackGround->GetComponent<Transform>()->SetPos(Math::Vector2<float>(760.f, 416.f));
		JailBossPrevBackGround->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1520.f, 832.f));
		Texture* temp = Resources::Load<Texture>(L"Jailprevprev", L"..\\Resources\\Dungeon\\Belial\\Bossprevprev.png");
		JailBossPrevBackGround->GetComponent<SpriteRenderer>()->SetImg(temp);

		BackGround* Candle1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Candle1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(376.f, 670.f));
		Candle1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(48.f, 68.f));
		temp = Resources::Load<Texture>(L"Candle1", L"..\\Resources\\Dungeon\\Belial\\CandleOn20.png");
		Candle1->GetComponent<SpriteRenderer>()->SetImg(temp);

		BackGround* Door1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Door1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(810.f, 574.f));
		Door1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(228.f, 260.f));
		temp = Resources::Load<Texture>(L"Door1", L"..\\Resources\\Dungeon\\Belial\\Door0.png");
		Door1->GetComponent<SpriteRenderer>()->SetImg(temp);

		BackGround* SavePoint1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		SavePoint1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1142.f, 670.f));
		SavePoint1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(92.f, 68.f));
		temp = Resources::Load<Texture>(L"SavePoint1", L"..\\Resources\\Dungeon\\Belial\\SavePoint_Off.png");
		SavePoint1->GetComponent<SpriteRenderer>()->SetImg(temp);
	}

	void JailScene::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			SceneManager::LoadScene(L"JailPrevBossScene");
		}
		Scene::Update();
	}

	void JailScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene", 10);
	}

}