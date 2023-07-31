#include "EHJailScene3.h"
#include "EHSceneManager.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"

namespace EH
{
	void JailScene3::Initialize()
	{
		SetSize(Math::Vector2<float>(1792.f, 768.f));
		BackGround* JailBG3 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(896.f, 384.f));
		JailBG3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1792.f, 768.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG3", L"..\\Resources\\Dungeon\\JailBackGround\\3\\JailField3.bmp");
		JailBG3->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG3->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailScene3::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene4");
		}
		Scene::Update();
	}

	void JailScene3::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene3", 10);
	}
}
