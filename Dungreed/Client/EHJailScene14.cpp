#include "EHJailScene14.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"

namespace EH
{
	void JailScene14::Initialize()
	{
		SetSize(Math::Vector2<float>(1280.f, 1024.f));
		BackGround* JailBG14 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG14->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 512.f));
		JailBG14->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 1024.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG14", L"..\\Resources\\Dungeon\\JailBackGround\\14\\JailField14.bmp");
		JailBG14->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG14->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailScene14::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene15");
		}
		Scene::Update();
	}

	void JailScene14::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene14", 11);
	}
}
