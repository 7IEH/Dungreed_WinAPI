#include "EHTitleScene.h"
#include "EHObject.h"
#include "EHTexture.h"
#include "EHInput.h"
#include "EHBackGround.h"
#include "EHResources.h"
#include "EHPath.h"
#include "EHSound.h"

namespace EH
{
	TitleScene::TitleScene()
	{
	}

	TitleScene::~TitleScene()
	{
		// 나중에 신 오브젝트들 삭제
	}

	void TitleScene::Initialize()
	{
		// Sound
		Sound* BGM = Resources::Load<Sound>(L"BGM", L"..\\Resources\\Sound\\title.wav");
		BGM->Play();

		Texture* temp = nullptr;
		// BackCloud
		BackGround* BackCloud = object::Instantiate<BackGround>(enums::eLayerType::UI);
		BackCloud->GetComponent<Transform>()->SetPos(Math::Vector2<float>(0.f, 0.f));
		BackCloud->GetComponent<Transform>()->SetScale(Math::Vector2<float>(2560.f, 720.f));
		temp = Resources::Load<Texture>(L"BackCloud",L"..\\Client\\Resources\\EnterScene\\BackCloud.png");
		BackCloud->GetComponent<SpriteRenderer>()->SetImg(temp);


		// FrontCloud
		BackGround* FrontCloud = object::Instantiate<BackGround>(enums::eLayerType::UI);
		FrontCloud->GetComponent<Transform>()->SetPos(Math::Vector2<float>(0.f, 0.f));
		FrontCloud->GetComponent<Transform>()->SetScale(Math::Vector2<float>(2560.f, 720.f));
		temp = Resources::Load<Texture>(L"FrontCloud", L"..\\Resources\\EnterScene\\FrontCloud.png");
		FrontCloud->GetComponent<SpriteRenderer>()->SetImg(temp);


		// Main Logo
		BackGround* MainLogo = object::Instantiate<BackGround>(enums::eLayerType::UI);
		MainLogo->GetComponent<Transform>()->SetPos(Math::Vector2<float>(320.f,140.f));
		MainLogo->GetComponent<Transform>()->SetScale(Math::Vector2<float>(624.f, 300.f));
		temp = Resources::Load<Texture>(L"MainLogo", L"..\\Resources\\EnterScene\\MainLogo.png");
		MainLogo->GetComponent<SpriteRenderer>()->SetImg(temp);

		// Start
		BackGround* Start = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Start->GetComponent<Transform>()->SetPos(Math::Vector2<float>(565.f, 460.f));
		Start->GetComponent<Transform>()->SetScale(Math::Vector2<float>(144.f, 48.f));
		temp = Resources::Load<Texture>(L"Start_Btn", L"..\\Resources\\EnterScene\\PlayOff_Kor.png");
		Start->GetComponent<SpriteRenderer>()->SetImg(temp);

		// Option
		BackGround* Option = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Option->GetComponent<Transform>()->SetPos(Math::Vector2<float>(595.f, 507.f));
		Option->GetComponent<Transform>()->SetScale(Math::Vector2<float>(84.f, 48.f));
		temp = Resources::Load<Texture>(L"Option_Btn", L"..\\Resources\\EnterScene\\OptionOff_Kor.png");
		Option->GetComponent<SpriteRenderer>()->SetImg(temp);

		// Exit
		BackGround* Exit = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Exit->GetComponent<Transform>()->SetPos(Math::Vector2<float>(595.f, 556.f));
		Exit->GetComponent<Transform>()->SetScale(Math::Vector2<float>(84.f, 48.f));
		temp = Resources::Load<Texture>(L"Exit_Btn", L"..\\Resources\\EnterScene\\ExitOff_Kor.png");
		Exit->GetComponent<SpriteRenderer>()->SetImg(temp);
	}

	void TitleScene::Update()
	{
		if (Input::Getkey(EH::eKeyCode::Z).state == eKeyState::DOWN)
		{
			SceneManager::LoadScene(L"SelectScene");
		}
		Scene::Update();
	}

	void TitleScene::Render(HDC hdc)
	{
		HBRUSH hNewBrush = (HBRUSH)CreateSolidBrush(RGB(121, 185, 255));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc,hNewBrush);

		HPEN hNewPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(121, 185, 255));
		HPEN hOldPen = (HPEN)SelectObject(hdc, hNewPen);

		Rectangle(hdc, -1, -1, 1280, 720);

		SelectObject(hdc, hOldBrush);
		SelectObject(hdc, hOldPen);

		DeleteObject(hNewBrush);
		DeleteObject(hNewPen);

		Scene::Render(hdc);
	}
}