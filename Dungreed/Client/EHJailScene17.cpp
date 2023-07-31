#include "EHJailScene17.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"

namespace EH
{
	void JailScene17::Initialize()
	{
		SetSize(Math::Vector2<float>(1280.f,896.f));
		BackGround* JailBG17 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG17->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f,448.f));
		JailBG17->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 896.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG17", L"..\\Resources\\Dungeon\\JailBackGround\\17\\JailField17.bmp");
		JailBG17->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG17->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailScene17::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt((640.f, 360.f));
			SceneManager::LoadScene(L"JailScene18");
		}
		Scene::Update();
	}

	void JailScene17::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene17", 11);
	}
}