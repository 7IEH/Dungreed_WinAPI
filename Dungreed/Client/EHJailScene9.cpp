#include "EHJailScene9.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"
#include "EHPlayer.h"
#include "EHCanvas.h"

namespace EH
{
	void JailScene9::Initialize()
	{
		SetSize(Math::Vector2<float>(3136.f,896.f));
		BackGround* JailBG9 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG9->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1568.f, 448.f));
		JailBG9->GetComponent<Transform>()->SetScale(Math::Vector2<float>(3136.f, 896.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG9", L"..\\Resources\\Dungeon\\JailBackGround\\9\\JailField9.bmp");
		JailBG9->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG9->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailScene9::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene10");
		}
		Scene::Update();
	}

	void JailScene9::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene9", 10);
	}
}