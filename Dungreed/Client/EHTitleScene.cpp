#include "EHTitleScene.h"
#include "EHObject.h"
#include "EHImage.h"
#include "EHInput.h"

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
		// BackCloud
		Image* BackCloud = object::Instantiate<Image>(enums::eLayerType::UI);
		BackCloud->GetComponent<Transform>()->SetPos(Math::Vector2<float>(0.f, 0.f));
		BackCloud->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		BackCloud->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(160.f, 0.f));
		BackCloud->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(300.f, 180.f));
		BackCloud->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\EnterScene\\BackCloud.png", L"BackCloud");
		BackCloud->GetComponent<SpriteRenderer>()->SetImg(L"BackCloud");

		// FrontCloud
		Image* FrontCloud = object::Instantiate<Image>(enums::eLayerType::UI);
		FrontCloud->GetComponent<Transform>()->SetPos(Math::Vector2<float>(0.f, 0.f));
		FrontCloud->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		FrontCloud->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(130.f, 0.f));
		FrontCloud->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(390.f, 180.f));
		FrontCloud->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\EnterScene\\FrontCloud.png", L"FrontCloud");
		FrontCloud->GetComponent<SpriteRenderer>()->SetImg(L"FrontCloud");

		// Main Logo
		Image* MainLogo = object::Instantiate<Image>(enums::eLayerType::UI);
		MainLogo->GetComponent<Transform>()->SetPos(Math::Vector2<float>(320.f,140.f));
		MainLogo->GetComponent<Transform>()->SetScale(Math::Vector2<float>(624.f, 270.f));
		MainLogo->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
		MainLogo->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(156.f, 75.f));
		MainLogo->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\EnterScene\\MainLogo.png", L"MainLogo");
		MainLogo->GetComponent<SpriteRenderer>()->SetImg(L"MainLogo");

		// Start
		Image* Start = object::Instantiate<Image>(enums::eLayerType::UI);
		Start->GetComponent<Transform>()->SetPos(Math::Vector2<float>(565.f, 460.f));
		Start->GetComponent<Transform>()->SetScale(Math::Vector2<float>(144.f, 48.f));
		Start->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
		Start->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(36.f, 12.f));
		Start->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\EnterScene\\PlayOff_Kor.png", L"Start");
		Start->GetComponent<SpriteRenderer>()->SetImg(L"Start");

		// Option
		Image* Option = object::Instantiate<Image>(enums::eLayerType::UI);
		Option->GetComponent<Transform>()->SetPos(Math::Vector2<float>(595.f, 507.f));
		Option->GetComponent<Transform>()->SetScale(Math::Vector2<float>(84.f, 48.f));
		Option->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
		Option->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(20.f, 12.f));
		Option->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\EnterScene\\OptionOff_Kor.png", L"Option");
		Option->GetComponent<SpriteRenderer>()->SetImg(L"Option");

		// Exit
		Image* Exit = object::Instantiate<Image>(enums::eLayerType::UI);
		Exit->GetComponent<Transform>()->SetPos(Math::Vector2<float>(595.f, 556.f));
		Exit->GetComponent<Transform>()->SetScale(Math::Vector2<float>(84.f, 48.f));
		Exit->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
		Exit->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(21.f, 12.f));
		Exit->GetComponent<SpriteRenderer>()->AddImg(L"\\Resources\\EnterScene\\ExitOff_Kor.png", L"Exit");
		Exit->GetComponent<SpriteRenderer>()->SetImg(L"Exit");
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