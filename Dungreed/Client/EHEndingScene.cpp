#include "EHEndingScene.h"
#include "EHBackGround.h"
#include "EHResources.h"
#include "EHObject.h"

namespace EH
{
	void EndingScene::Initialize()
	{
		// Sound
		Sound* BGM = Resources::Load<Sound>(L"BGM", L"..\\Resources\\Sound\\BGM\\title.wav");
		SetBGM(BGM);
		BGM->Play(true);

		SetSize(Math::Vector2<float>(1280.f, 720.f));

		Texture* temp = nullptr;
		// BackCloud
		BackGround* BackCloud = object::Instantiate<BackGround>(enums::eLayerType::UI);
		BackCloud->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		BackCloud->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		temp = Resources::Load<Texture>(L"skyday", L"..\\Resources\\Ending\\Sky_Day.bmp");
		BackCloud->GetComponent<SpriteRenderer>()->SetImg(temp);
		BackCloud->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* mount1 = object::Instantiate<BackGround>(enums::eLayerType::UI);
		mount1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 436.f));
		mount1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 568.f));
		temp = Resources::Load<Texture>(L"mount", L"..\\Resources\\Ending\\TownBG_Day.bmp");
		mount1->GetComponent<SpriteRenderer>()->SetImg(temp);
		mount1->GetComponent<SpriteRenderer>()->SetAffectCamera(false);
		mMount1 = mount1;

		BackGround* mount2 = object::Instantiate<BackGround>(enums::eLayerType::UI);
		mount2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(-640.f, 436.f));
		mount2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 568.f));
		temp = Resources::Load<Texture>(L"mount", L"..\\Resources\\Ending\\TownBG_Day.bmp");
		mount2->GetComponent<SpriteRenderer>()->SetImg(temp);
		mount2->GetComponent<SpriteRenderer>()->SetAffectCamera(false);
		mMount2 = mount2;

		BackGround* player = object::Instantiate<BackGround>(enums::eLayerType::UI);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(480.f, 400.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		temp = Resources::Load<Texture>(L"playerending", L"..\\Resources\\Ending\\CharLeftIdleSheet.bmp");
		Animator* ani = player->AddComponent<Animator>();
		ani->CreateAnimation(L"playerending", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 5, 0.1f);
		ani->PlayAnimation(L"playerending", true);

		BackGround* horse = object::Instantiate<BackGround>(enums::eLayerType::UI);
		horse->GetComponent<Transform>()->SetPos(Math::Vector2<float>(300.f, 460.f));
		horse->GetComponent<Transform>()->SetScale(Math::Vector2<float>(495.f, 152.f));
		temp = Resources::Load<Texture>(L"horse", L"..\\Resources\\Ending\\horse.bmp");
		ani = horse->AddComponent<Animator>();
		ani->CreateAnimation(L"horse", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(120.f, 38.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);
		ani->PlayAnimation(L"horse", true);

		// FrontCloud
		BackGround* bg1 = object::Instantiate<BackGround>(enums::eLayerType::UI);
		bg1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		bg1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		temp = Resources::Load<Texture>(L"ground", L"..\\Resources\\Ending\\EndingBG.bmp");
		bg1->GetComponent<SpriteRenderer>()->SetImg(temp);
		bg1->GetComponent<SpriteRenderer>()->SetAffectCamera(false);
		mBG1 = bg1;

		BackGround* bg2 = object::Instantiate<BackGround>(enums::eLayerType::UI);
		bg2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(-640.f, 360.f));
		bg2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		temp = Resources::Load<Texture>(L"ground", L"..\\Resources\\Ending\\EndingBG.bmp");
		bg2->GetComponent<SpriteRenderer>()->SetImg(temp);
		bg2->GetComponent<SpriteRenderer>()->SetAffectCamera(false);
		mBG2 = bg2;

		BackGround* bg3 = object::Instantiate<BackGround>(enums::eLayerType::UI);
		bg3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(920.f, 360.f));
		bg3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(720.f, 720.f));
		temp = Resources::Load<Texture>(L"endinghalf", L"..\\Resources\\Ending\\Endinghalf.bmp");
		bg3->GetComponent<SpriteRenderer>()->SetImg(temp);
		bg3->GetComponent<SpriteRenderer>()->SetAffectCamera(false);
		bg3->GetComponent<SpriteRenderer>()->SetAlpha(0.7f);

		// Main Logo
		BackGround* MainLogo = object::Instantiate<BackGround>(enums::eLayerType::UI);
		MainLogo->GetComponent<Transform>()->SetPos(Math::Vector2<float>(940.f, 800.f));
		MainLogo->GetComponent<Transform>()->SetScale(Math::Vector2<float>(312.f, 150.f));
		temp = Resources::Load<Texture>(L"MainLogo", L"..\\Resources\\EnterScene\\MainLogo.png");
		MainLogo->GetComponent<SpriteRenderer>()->SetImg(temp);
		MainLogo->GetComponent<SpriteRenderer>()->SetAffectCamera(false);
		mLogo = MainLogo;

		BackGround* practice = object::Instantiate<BackGround>(enums::eLayerType::UI);
		practice->GetComponent<Transform>()->SetPos(Math::Vector2<float>(940.f, 950.f));
		practice->GetComponent<Transform>()->SetScale(Math::Vector2<float>(396.f, 33.f));
		temp = Resources::Load<Texture>(L"Practice2", L"..\\Resources\\Ending\\copypratice.bmp");
		practice->GetComponent<SpriteRenderer>()->SetImg(temp);
		practice->GetComponent<SpriteRenderer>()->SetAffectCamera(false);
		mPratice = practice;

		BackGround* qa = object::Instantiate<BackGround>(enums::eLayerType::UI);
		qa->GetComponent<Transform>()->SetPos(Math::Vector2<float>(940.f, 1030.f));
		qa->GetComponent<Transform>()->SetScale(Math::Vector2<float>(357.f, 36.f));
		temp = Resources::Load<Texture>(L"Qa", L"..\\Resources\\Ending\\Qa.bmp");
		qa->GetComponent<SpriteRenderer>()->SetImg(temp);
		qa->GetComponent<SpriteRenderer>()->SetAffectCamera(false);
		mQa = qa;

		BackGround* practicechar = object::Instantiate<BackGround>(enums::eLayerType::UI);
		practicechar->GetComponent<Transform>()->SetPos(Math::Vector2<float>(700.f, 950.f));
		practicechar->GetComponent<Transform>()->SetScale(Math::Vector2<float>(96.f, 96.f));
		temp = Resources::Load<Texture>(L"practicechar", L"..\\Resources\\Ending\\CharIdle\\CharIdle.bmp");
		ani = practicechar->AddComponent<Animator>();
		ani->CreateAnimation(L"practicechar", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 5, 0.1f);
		ani->PlayAnimation(L"practicechar", true);
		mPracticeChar = practicechar;

		BackGround* qachar = object::Instantiate<BackGround>(enums::eLayerType::UI);
		qachar->GetComponent<Transform>()->SetPos(Math::Vector2<float>(700.f, 1030.f));
		qachar->GetComponent<Transform>()->SetScale(Math::Vector2<float>(75.f, 96.f));
		temp = Resources::Load<Texture>(L"qachar", L"..\\Resources\\Ending\\DearFarmer\\DeerFarmIdle.bmp");
		ani = qachar->AddComponent<Animator>();
		ani->CreateAnimation(L"qachar", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(25.f, 32.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		ani->PlayAnimation(L"qachar", true);
		mQaChar = qachar;

		BackGround* black = object::Instantiate<BackGround>(enums::eLayerType::UI);
		black->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		black->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		temp = Resources::Load<Texture>(L"black", L"..\\Resources\\Ending\\black.bmp");
		black->GetComponent<SpriteRenderer>()->SetImg(temp);
		black->GetComponent<SpriteRenderer>()->SetAffectCamera(false);
		mBG3 = black;
		black->GetComponent<SpriteRenderer>()->SetAlpha(0.f);

		BackGround* thankyou = object::Instantiate<BackGround>(enums::eLayerType::UI);
		thankyou->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		thankyou->GetComponent<Transform>()->SetScale(Math::Vector2<float>(396.f, 76.f));
		temp = Resources::Load<Texture>(L"thankyou", L"..\\Resources\\Ending\\ThankYou.korean.bmp");
		thankyou->GetComponent<SpriteRenderer>()->SetImg(temp);
		thankyou->GetComponent<SpriteRenderer>()->SetAffectCamera(false);
		mThankyou = thankyou;
		thankyou->GetComponent<SpriteRenderer>()->SetAlpha(0.f);
	}

	void EndingScene::Update()
	{
		Scene::Update();

		mCheck1 += Time::GetDeltaTime();

		Transform* fronttr1 = mMount1->GetComponent<Transform>();
		Transform* fronttr2 = mMount2->GetComponent<Transform>();
		Transform* backtr1 = mBG1->GetComponent<Transform>();
		Transform* backtr2 = mBG2->GetComponent<Transform>();

		Math::Vector2<float> frontpos1 = fronttr1->Getpos();
		Math::Vector2<float> frontpos2 = fronttr2->Getpos();
		Math::Vector2<float> backpos1 = backtr1->Getpos();
		Math::Vector2<float> backpos2 = backtr2->Getpos();

		if (frontpos1.x >= 1920.f)
		{
			fronttr1->SetPos(Math::Vector2<float>(-640.f, 436.f));
		}

		if (frontpos2.x >= 1920.f)
		{
			fronttr2->SetPos(Math::Vector2<float>(-640.f, 436.f));
		}

		if (backpos1.x >= 1920.f)
		{
			backtr1->SetPos(Math::Vector2<float>(-640.f, 360.f));
		}

		if (backpos2.x >= 1920.f)
		{
			backtr2->SetPos(Math::Vector2<float>(-640.f, 360.f));
		}

		frontpos1 = fronttr1->Getpos();
		frontpos2 = fronttr2->Getpos();
		backpos1 = backtr1->Getpos();
		backpos2 = backtr2->Getpos();

		fronttr1->SetPos(Math::Vector2<float>(frontpos1.x + 50.f * Time::GetDeltaTime(), 436.f));
		fronttr2->SetPos(Math::Vector2<float>(frontpos2.x + 50.f * Time::GetDeltaTime(), 436.f));
		backtr1->SetPos(Math::Vector2<float>(backpos1.x + 50.f * Time::GetDeltaTime(), 360.f));
		backtr2->SetPos(Math::Vector2<float>(backpos2.x + 50.f * Time::GetDeltaTime(), 360.f));
		mLogo->GetComponent<Transform>()->SetPos(Math::Vector2<float>(940.f, mLogo->GetComponent<Transform>()->Getpos().y - 50.f * Time::GetDeltaTime()));
		mPratice->GetComponent<Transform>()->SetPos(Math::Vector2<float>(940.f, mPratice->GetComponent<Transform>()->Getpos().y - 50.f * Time::GetDeltaTime()));
		mQa->GetComponent<Transform>()->SetPos(Math::Vector2<float>(940.f, mQa->GetComponent<Transform>()->Getpos().y - 50.f * Time::GetDeltaTime()));
		mPracticeChar->GetComponent<Transform>()->SetPos(Math::Vector2<float>(700.f, mPracticeChar->GetComponent<Transform>()->Getpos().y - 50.f * Time::GetDeltaTime()));
		mQaChar->GetComponent<Transform>()->SetPos(Math::Vector2<float>(700.f, mQaChar->GetComponent<Transform>()->Getpos().y - 50.f * Time::GetDeltaTime()));

		if (16.f<mCheck1)
		{
			if (mCheck2 < 0.9f)
			{
				mCheck2 += 0.01f;
			}
			else if (0.9f < mCheck2)
			{
				mCheck2 = 1.f;
			}
			mBG3->GetComponent<SpriteRenderer>()->SetAlpha(mCheck2);
		}

		if (18.f <= mCheck1)
		{
			if (mCheck3 < 0.9f)
			{
				mCheck3 += 0.01f;
			}
			else if (0.9f < mCheck3)
			{
				mCheck3 = 1.f;
			}
			mThankyou->GetComponent<SpriteRenderer>()->SetAlpha(mCheck3);
		}
	}

	void EndingScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}