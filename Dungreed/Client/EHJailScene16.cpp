#include "EHJailScene16.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"
#include "EHPlayer.h"
#include "EHCanvas.h"

namespace EH
{
	void JailScene16::Initialize()
	{
		SetSize(Math::Vector2<float>(1280.f, 1024.f));
		BackGround* JailBG16 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG16->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 512.f));
		JailBG16->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 1024.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG16", L"..\\Resources\\Dungeon\\JailBackGround\\16\\JailField16.bmp");
		JailBG16->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG16->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailScene16::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene17");
		}
		Scene::Update();
	}

	void JailScene16::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene16", 11);
	}
}
