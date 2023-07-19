#include "EHJailField7.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"

namespace EH
{
	void JailField7::Initialize()
	{
		SetSize(Math::Vector2<float>(1536.f, 896.f));
		BackGround* JailBG7 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG7->GetComponent<Transform>()->SetPos(Math::Vector2<float>(768.f, 448.f));
		JailBG7->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1536.f, 896.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG7", L"..\\Resources\\Dungeon\\JailBackGround\\7\\JailField7.bmp");
		JailBG7->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG7->GetComponent<SpriteRenderer>()->SetAffectCamera(true);
	}
	void JailField7::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene8");
		}
		Scene::Update();
	}
	void JailField7::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene7", 10);
	}
}
