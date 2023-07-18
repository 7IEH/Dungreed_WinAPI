#include "EHJailField8.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"

namespace EH
{
	void JailField8::Initialize()
	{
		SetSize(Math::Vector2<float>(2752.f, 1088.f));
		BackGround* JailBG8 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG8->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1376.f, 544.f));
		JailBG8->GetComponent<Transform>()->SetScale(Math::Vector2<float>(2752.f, 1088.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG8", L"..\\Resources\\Dungeon\\JailBackGround\\8\\JailField8.bmp");
		JailBG8->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG8->GetComponent<SpriteRenderer>()->SetAffectCamera(true);
	}
	void JailField8::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"TitleScene");
		} 
		Scene::Update();
	}
	void JailField8::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}