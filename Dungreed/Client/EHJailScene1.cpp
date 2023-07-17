#include "EHJailScene1.h"
#include "EHObject.h"
#include "EHBackGround.h"
#include "EHResources.h"

namespace EH
{
	void JailScene1::Initialize()
	{
		BackGround* JailBG1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		JailBG1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG1", L"..\\Resources\\Dungeon\\JailBackGround\\1\\JailField1.bmp");
		JailBG1->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG1->GetComponent<SpriteRenderer>()->SetAffectCamera(true);
	}

	void JailScene1::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
			SceneManager::LoadScene(L"JailScene2");
		Scene::Update();
	}

	void JailScene1::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene1", 10);
	}
}
