#include "EHIntro.h"

namespace EH
{
	Intro::Intro()
		:
		 mCheck1(0)
	{
		SpriteRenderer* sr = AddComponent<SpriteRenderer>();
		sr->SetAlpha(0.f);
	}

	Intro::~Intro()
	{
	}

	void Intro::Initialize()
	{
	}

	void Intro::Update()
	{
		GameObject::Update();
		SpriteRenderer* sr = GetComponent<SpriteRenderer>();

		mCheckTime+=Time::GetDeltaTime();
		float fratio = mCheckTime / 3.f;

		if (fratio > 1.f)
			fratio = 1.f;
		

		if (fratio < 1.f && mCheck1 == 0)
		{
			sr->SetAlpha(fratio);
		}
		else if (fratio >= 1.f && mCheck1 == 0)
		{
			fratio = 1.f;
			mCheck1++;
			mCheckTime = 0.f;
		}
		else if (fratio > 0.f && mCheck1 == 1)
		{
			sr->SetAlpha(1.f-fratio);
		}
		else if (fratio <= 0.f && mCheck1 == 1)
		{
			fratio = 0.f;
			mCheck1++;
		}
	}

	void Intro::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}