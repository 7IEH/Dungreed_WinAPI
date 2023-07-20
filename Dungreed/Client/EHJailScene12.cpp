#include "EHJailScene12.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"

namespace EH
{
	void JailScene12::Initialize()
	{
		SetSize(Math::Vector2<float>(1280.f, 1088.f));

		BackGround* JailSubBG12 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailSubBG12->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		JailSubBG12->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		Texture* texture = Resources::Load<Texture>(L"JailSubBG", L"..\\Resources\\Dungeon\\JailBackGround\\4\\SubBG.bmp");
		JailSubBG12->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailSubBG12->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailBG12 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG12->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 544.f));
		JailBG12->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 1088.f));
		texture = Resources::Load<Texture>(L"JailBG12", L"..\\Resources\\Dungeon\\JailBackGround\\12\\JailField12.bmp");
		JailBG12->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG12->GetComponent<SpriteRenderer>()->SetAffectCamera(true);
	}

	void JailScene12::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene13");
		}
		Scene::Update();
	}

	void JailScene12::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene12", 11);
	}
}