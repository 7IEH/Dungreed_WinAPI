#include "EHJailScene4.h"
#include "EHSceneManager.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"

namespace EH
{
	void JailScene4::Initialize()
	{
		BackGround* JailSubBG4 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailSubBG4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		JailSubBG4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		Texture* texture = Resources::Load<Texture>(L"JailSubBG", L"..\\Resources\\Dungeon\\JailBackGround\\4\\SubBG.bmp");
		JailSubBG4->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailSubBG4->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailBG4 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG4->GetComponent<Transform>()->SetPos(Math::Vector2<float>(736.f, 544.f));
		JailBG4->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1472.f, 1088.f));
		texture = Resources::Load<Texture>(L"JailBG4", L"..\\Resources\\Dungeon\\JailBackGround\\4\\JailField4.bmp");
		JailBG4->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG4->GetComponent<SpriteRenderer>()->SetAffectCamera(true);
	}

	void JailScene4::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
			SceneManager::LoadScene(L"TitleScene");
		Scene::Update();
	}

	void JailScene4::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene4", 10);
	}
}