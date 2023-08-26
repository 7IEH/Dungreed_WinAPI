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
#include "EHBullet.h"
#include <time.h>

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
		srand((UINT)time(NULL));
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
		mBackcloud1 = BackCloud;


		BackGround* BackCloud2 = object::Instantiate<BackGround>(enums::eLayerType::UI);
		BackCloud2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(3840.f, 360.f));
		BackCloud2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(2560.f, 720.f));
		temp = Resources::Load<Texture>(L"BackCloud", L"..\\Client\\Resources\\EnterScene\\BackCloud.png");
		BackCloud2->GetComponent<SpriteRenderer>()->SetImg(temp);
		BackCloud2->GetComponent<SpriteRenderer>()->SetAffectCamera(false);
		mBackcloud2 = BackCloud2;

		// FrontCloud
		BackGround* FrontCloud = object::Instantiate<BackGround>(enums::eLayerType::UI);
		FrontCloud->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1280.f, 360.f));
		FrontCloud->GetComponent<Transform>()->SetScale(Math::Vector2<float>(2560.f, 720.f));
		temp = Resources::Load<Texture>(L"FrontCloud", L"..\\Resources\\EnterScene\\FrontCloud.png");
		FrontCloud->GetComponent<SpriteRenderer>()->SetImg(temp);
		FrontCloud->GetComponent<SpriteRenderer>()->SetAffectCamera(false);
		mFrontcloud1 = FrontCloud;

		BackGround* FrontCloud2 = object::Instantiate<BackGround>(enums::eLayerType::UI);
		FrontCloud2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(3840.f, 360.f));
		FrontCloud2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(2560.f, 720.f));
		temp = Resources::Load<Texture>(L"FrontCloud", L"..\\Resources\\EnterScene\\FrontCloud.png");
		FrontCloud2->GetComponent<SpriteRenderer>()->SetImg(temp);
		FrontCloud2->GetComponent<SpriteRenderer>()->SetAffectCamera(false);
		mFrontcloud2 = FrontCloud2;

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

		// Exit
		Button* bug = object::Instantiate<Button>(enums::eLayerType::UI);
		bug->GetComponent<Transform>()->SetPos(Math::Vector2<float>(100.f, 700.f));
		bug->GetComponent<Transform>()->SetScale(Math::Vector2<float>(118.f, 18.f));
		temp = Resources::Load<Texture>(L"bugreport", L"..\\Resources\\EnterScene\\BugReport.bmp");
		bug->SetTransition(eButtonState::Selected, temp);
		bug->SetTransition(eButtonState::Pressed, temp);
		bug->SetTransition(eButtonState::Idle, temp);
		bug->SetClickEvent(eClickEvent::BugReport);
		bug->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* copypratice = object::Instantiate<BackGround>(enums::eLayerType::UI);
		copypratice->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 690.f));
		copypratice->GetComponent<Transform>()->SetScale(Math::Vector2<float>(396.f, 33.f));
		temp = Resources::Load<Texture>(L"copypratice", L"..\\Resources\\EnterScene\\copypratice.bmp");
		copypratice->GetComponent<SpriteRenderer>()->SetImg(temp);
		copypratice->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* version = object::Instantiate<BackGround>(enums::eLayerType::UI);
		version->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1240.f, 700.f));
		version->GetComponent<Transform>()->SetScale(Math::Vector2<float>(50.f, 18.f));
		temp = Resources::Load<Texture>(L"version", L"..\\Resources\\EnterScene\\Ver.bmp");
		version->GetComponent<SpriteRenderer>()->SetImg(temp);
		version->GetComponent<SpriteRenderer>()->SetAffectCamera(false);
	}

	void TitleScene::Update()
	{
		Scene::Update();

		Transform* fronttr1 = mFrontcloud1->GetComponent<Transform>();
		Transform* fronttr2 = mFrontcloud2->GetComponent<Transform>();
		Transform* backtr1 = mBackcloud1->GetComponent<Transform>();
		Transform* backtr2 = mBackcloud2->GetComponent<Transform>();

		Math::Vector2<float> frontpos1 = fronttr1->Getpos();
		Math::Vector2<float> frontpos2 = fronttr2->Getpos();
		Math::Vector2<float> backpos1 = backtr1->Getpos();
		Math::Vector2<float> backpos2 = backtr2->Getpos();

		if (frontpos1.x <= -1280.f)
		{
			fronttr1->SetPos(Math::Vector2<float>(3840.f, 360.f));
		}
		
		if (frontpos2.x <= -1280.f)
		{
			fronttr2->SetPos(Math::Vector2<float>(3840.f, 360.f));
		}

		if (backpos1.x <= -1280.f)
		{
			backtr1->SetPos(Math::Vector2<float>(3840.f, 360.f));
		}

		if (backpos2.x <= -1280.f)
		{
			backtr2->SetPos(Math::Vector2<float>(3840.f, 360.f));
		}

		fronttr1->SetPos(Math::Vector2<float>(frontpos1.x - 100.f*Time::GetDeltaTime(),360.f));
		fronttr2->SetPos(Math::Vector2<float>(frontpos2.x - 100.f * Time::GetDeltaTime(), 360.f));
		backtr1->SetPos(Math::Vector2<float>(backpos1.x - 50.f * Time::GetDeltaTime(), 360.f));
		backtr2->SetPos(Math::Vector2<float>(backpos2.x - 50.f * Time::GetDeltaTime(), 360.f));

		int ran = rand() % 7;
		mCheck1 += Time::GetDeltaTime();

		if (2.f < mCheck1)
		{
			Bullet* bird = object::Instantiate<Bullet>(enums::eLayerType::BackGround);
			bird->GetComponent<Transform>()->SetPos(Math::Vector2<float>(0.f, 100.f*ran));
			bird->GetComponent<Transform>()->SetScale(Math::Vector2<float>(48.f, 32.f));
			Texture* texture = Resources::Load<Texture>(L"Bird", L"..\\Resources\\EnterScene\\Bird.bmp");
			Animator* ani = bird->AddComponent<Animator>();
			ani->CreateAnimation(L"Bird", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(12.f, 8.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);
			ani->PlayAnimation(L"Bird", true);
			bird->SetStop(false);
			bird->SetRadian(0.f);
			bird->SetDeleteTime(10.f);
			mCheck1 = 0;
		}
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