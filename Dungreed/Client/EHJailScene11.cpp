#include "EHJailScene11.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"
#include "EHPlayer.h"
#include "EHCanvas.h"

namespace EH
{
	void JailScene11::Initialize()
	{
		SetSize(Math::Vector2<float>(1600.f, 768.f));
		BackGround* JailBG11 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG11->GetComponent<Transform>()->SetPos(Math::Vector2<float>(800.f, 384.f));
		JailBG11->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1600.f, 768.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG11", L"..\\Resources\\Dungeon\\JailBackGround\\11\\JailField11.bmp");
		JailBG11->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG11->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailScene11::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene12");
		}
		Scene::Update();
	}

	void JailScene11::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene11", 11);
	}
}