#include "EHJailScene15.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"

namespace EH
{
	void JailScene15::Initialize()
	{
		SetSize(Math::Vector2<float>(1280.f, 896.f));
		BackGround* JailBG15 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG15->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 448.f));
		JailBG15->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 896.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG15", L"..\\Resources\\Dungeon\\JailBackGround\\15\\JailField15.bmp");
		JailBG15->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG15->GetComponent<SpriteRenderer>()->SetAffectCamera(true);
	}

	void JailScene15::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene16");
		}
		Scene::Update();
	}

	void JailScene15::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene15", 11);
	}
}
