#include "EHJailScene2.h"
#include "EHSceneManager.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"

namespace EH
{
	void JailScene2::Initialize()
	{
		BackGround* JailBG2 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 448.f));
		JailBG2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 896.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG2", L"..\\Resources\\Dungeon\\JailBackGround\\2\\JailField2.bmp");
		JailBG2->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG2->GetComponent<SpriteRenderer>()->SetAffectCamera(true);
	}
	void JailScene2::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene3");
		}
		Scene::Update();
	}
	void JailScene2::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene2", 10);
	}
}
