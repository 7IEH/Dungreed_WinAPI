#include "EHJailField6.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"

namespace EH
{
	void JailField6::Initialize()
	{
		SetSize(Math::Vector2<float>(1472.f, 832.f));
		BackGround* JailBG6 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG6->GetComponent<Transform>()->SetPos(Math::Vector2<float>(736.f, 416.f));
		JailBG6->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1472.f, 832.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG6", L"..\\Resources\\Dungeon\\JailBackGround\\6\\JailField6.bmp");
		JailBG6->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG6->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailField6::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene7");
		}
		Scene::Update();
	}

	void JailField6::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene6", 10);
	}
}
