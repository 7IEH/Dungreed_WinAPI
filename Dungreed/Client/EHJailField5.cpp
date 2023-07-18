#include "EHJailField5.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"


namespace EH
{
	void JailField5::Initialize()
	{
		SetSize(Math::Vector2<float>(1280.f,720.f));
		BackGround* JailBG5 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG5->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		JailBG5->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG5", L"..\\Resources\\Dungeon\\JailBackGround\\5\\JailField5.bmp");
		JailBG5->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG5->GetComponent<SpriteRenderer>()->SetAffectCamera(true);
	}

	void JailField5::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene6");
		}
		Scene::Update();
	}

	void JailField5::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}