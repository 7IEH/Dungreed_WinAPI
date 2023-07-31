#include "EHJailScene13.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"

namespace EH
{
	void JailScene13::Initialize()
	{
		SetSize(Math::Vector2<float>(1920.f, 1152.f));

		BackGround* JailSubBG13 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailSubBG13->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		JailSubBG13->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		Texture* texture = Resources::Load<Texture>(L"JailSubBG", L"..\\Resources\\Dungeon\\JailBackGround\\4\\SubBG.bmp");
		JailSubBG13->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailSubBG13->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailBG13 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG13->GetComponent<Transform>()->SetPos(Math::Vector2<float>(960.f, 576.f));
		JailBG13->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1920.f, 1152.f));
		texture = Resources::Load<Texture>(L"JailBG13", L"..\\Resources\\Dungeon\\JailBackGround\\13\\JailField13.bmp");
		JailBG13->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG13->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailScene13::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene14");
		}
		Scene::Update();
	}

	void JailScene13::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene13", 11);
	}
}