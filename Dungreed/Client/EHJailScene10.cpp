#include "EHJailScene10.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"

namespace EH
{
	void JailScene10::Initialize()
	{
		SetSize(Math::Vector2<float>(2176.f, 720.f));

		BackGround* JailSubBG10 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailSubBG10->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		JailSubBG10->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		Texture* texture = Resources::Load<Texture>(L"JailSubBG", L"..\\Resources\\Dungeon\\JailBackGround\\4\\SubBG.bmp");
		JailSubBG10->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailSubBG10->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailBG10 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG10->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1088.f, 360.f));
		JailBG10->GetComponent<Transform>()->SetScale(Math::Vector2<float>(2176.f, 720.f));
		texture = Resources::Load<Texture>(L"JailBG10", L"..\\Resources\\Dungeon\\JailBackGround\\10\\JailField10.bmp");
		JailBG10->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG10->GetComponent<SpriteRenderer>()->SetAffectCamera(true);
	}

	void JailScene10::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene11");
		}
		Scene::Update();
	}

	void JailScene10::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene10", 11);
	}
}
