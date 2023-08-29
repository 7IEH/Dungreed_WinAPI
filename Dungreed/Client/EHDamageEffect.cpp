#include "EHDamageEffect.h"
#include "EHResources.h"

namespace EH
{
	DamageEffect::DamageEffect()
		:
		  mDamage(0)
		, mCheck1(0)
	{
		AddComponent<Rigidbody>();
		Animator* ani = AddComponent<Animator>();

		Texture* texture = Resources::Load<Texture>(L"numberfont", L"..\\Resources\\UI\\NumberFont.bmp");

		for (int i = 0;i < 9;i++)
		{
			ani->CreateAnimation(L"NUM" + std::to_wstring(i), texture, Math::Vector2<float>(i * 7.f, 0.f), Math::Vector2<float>(7.f, 11.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
		}
	}

	DamageEffect::~DamageEffect()
	{

	}

	void DamageEffect::Initialize()
	{
	}

	void DamageEffect::Update()
	{
		GameObject::Update();

		mCheckTime += Time::GetDeltaTime();

		Rigidbody* rigid = GetComponent<Rigidbody>();
		Animator* ani = GetComponent<Animator>();

		if (mCheck1 == 0)
		{
			rigid->SetVeclocity(Math::Vector2<float>(+100.f, -400.f));
			mCheck1 = 1;
		}

		ani->PlayAnimation(L"NUM" + std::to_wstring(mDamage), false);

		if (1.f < mCheckTime)
		{
			Destroy(this);
		}
	}

	void DamageEffect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}