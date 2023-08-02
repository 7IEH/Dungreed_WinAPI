#include "EHTitleScene.h"
#include "EHObject.h"
#include "EHTexture.h"
#include "EHInput.h"
#include "EHBackGround.h"
#include "EHResources.h"
#include "EHPath.h"
#include "EHSound.h"
#include "EHCamera.h"
#include "EHButton.h"

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
		Sound* BGM = Resources::Load<Sound>(L"BGM", L"..\\Resources\\Sound\\BGM\\title.wav");
		SetBGM(BGM);
		BGM->Play(true);

		SetSize(Math::Vector2<float>(1280.f, 720.f));

		Texture* temp = nullptr;
		// BackCloud
		BackGround* BackCloud = object::Instantiate<BackGround>(enums::eLayerType::UI);
		BackCloud->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1280.f, 360.f));
		BackCloud->GetComponent<Transform>()->SetScale(Math::Vector2<float>(2560.f, 720.f));
		temp = Resources::Load<Texture>(L"BackCloud",L"..\\Client\\Resources\\EnterScene\\BackCloud.png");
		BackCloud->GetComponent<SpriteRenderer>()->SetImg(temp);
		BackCloud->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// FrontCloud
		BackGround* FrontCloud = object::Instantiate<BackGround>(enums::eLayerType::UI);
		FrontCloud->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1280.f, 360.f));
		FrontCloud->GetComponent<Transform>()->SetScale(Math::Vector2<float>(2560.f, 720.f));
		temp = Resources::Load<Texture>(L"FrontCloud", L"..\\Resources\\EnterScene\\FrontCloud.png");
		FrontCloud->GetComponent<SpriteRenderer>()->SetImg(temp);
		FrontCloud->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// Main Logo
		BackGround* MainLogo = object::Instantiate<BackGround>(enums::eLayerType::UI);
		MainLogo->GetComponent<Transform>()->SetPos(Math::Vector2<float>(632.f,279.f));
		MainLogo->GetComponent<Transform>()->SetScale(Math::Vector2<float>(624.f, 300.f));
		temp = Resources::Load<Texture>(L"MainLogo", L"..\\Resources\\EnterScene\\MainLogo.png");
		MainLogo->GetComponent<SpriteRenderer>()->SetImg(temp);
		MainLogo->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		Button* Start = object::Instantiate<Button>(enums::eLayerType::UI);
		Start->GetComponent<Transform>()->SetPos(Math::Vector2<float>(637.f, 484.f));
		Start->GetComponent<Transform>()->SetScale(Math::Vector2<float>(144.f, 48.f));
		temp = Resources::Load<Texture>(L"Start_Btn_Off", L"..\\Resources\\EnterScene\\PlayOff_Kor.png");
		Start->SetTransition(eButtonState::Idle, temp);
		temp = Resources::Load<Texture>(L"Start_Btn_On", L"..\\Resources\\EnterScene\\PlayOn_Kor.png");
		Start->SetTransition(eButtonState::Selected, temp);
		Start->SetTransition(eButtonState::Pressed, temp);
		Start->GetComponent<SpriteRenderer>()->SetAffectCamera(false);
		Start->SetClickEvent(eClickEvent::SceneChange);
		Start->SetScene(L"TownScene");

		// Option
		Button* Option = object::Instantiate<Button>(enums::eLayerType::UI);
		Option->GetComponent<Transform>()->SetPos(Math::Vector2<float>(637.f, 531.f));
		Option->GetComponent<Transform>()->SetScale(Math::Vector2<float>(84.f, 48.f));
		temp = Resources::Load<Texture>(L"Option_Btn_Off", L"..\\Resources\\EnterScene\\OptionOff_Kor.png");
		Option->SetTransition(eButtonState::Idle, temp);
		temp = Resources::Load<Texture>(L"Option_Btn_On", L"..\\Resources\\EnterScene\\OptionOn_Kor.png");
		Option->SetTransition(eButtonState::Selected, temp);
		Option->SetTransition(eButtonState::Pressed, temp);
		Option->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// Exit
		Button* Exit = object::Instantiate<Button>(enums::eLayerType::UI);
		Exit->GetComponent<Transform>()->SetPos(Math::Vector2<float>(637.f, 580.f));
		Exit->GetComponent<Transform>()->SetScale(Math::Vector2<float>(84.f, 48.f));
		temp = Resources::Load<Texture>(L"Exit_Btn_Off", L"..\\Resources\\EnterScene\\ExitOff_Kor.png");
		Exit->SetTransition(eButtonState::Idle, temp);
		temp = Resources::Load<Texture>(L"Exit_Btn_On", L"..\\Resources\\EnterScene\\ExitOn_Kor.png");
		Exit->SetTransition(eButtonState::Selected, temp);
		Exit->SetTransition(eButtonState::Pressed, temp);
		Exit->GetComponent<SpriteRenderer>()->SetAffectCamera(false);
	}

	void TitleScene::Update()
	{
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