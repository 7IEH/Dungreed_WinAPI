#include "EHNiflheim.h"
#include "EHResources.h"

namespace EH
{
	Niflheim::Niflheim()
		:
		mEnter(0)
	{
		// Animator
		Animator* ani = AddComponent<Animator>();
		Texture* texture = Resources::Load<Texture>(L"NiflheimRightEnter", L"..\\Resources\\Enemy\\Boss\\Niflheim\\Enter\\NiflheimEnter.bmp");
		ani->CreateAnimation(L"NiflheimRightEnter", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(42.f, 33.f), Math::Vector2<float>(0.f, 0.f), 16, 0.1f);
		texture = Resources::Load<Texture>(L"NiflheimRightIdle", L"..\\Resources\\Enemy\\Boss\\Niflheim\\Idle\\Right\\NiflheimRightIdle.bmp");
		ani->CreateAnimation(L"NiflheimRightIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(42.f, 33.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		texture = Resources::Load<Texture>(L"NiflheimLeftIdle", L"..\\Resources\\Enemy\\Boss\\Niflheim\\Idle\\Left\\NiflheimLeftIdle.bmp");
		ani->CreateAnimation(L"NiflheimLeftIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(42.f, 33.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		ani->PlayAnimation(L"NiflheimRightEnter", true);
	}

	Niflheim::~Niflheim()
	{
	}

	void Niflheim::Initialize()
	{
	}

	void Niflheim::Update()
	{
		GameObject::Update();
		switch (GetState())
		{
		case EH::Enemy::eState::Idle:
			Idle();
			break;
		case EH::Enemy::eState::Attack:
			break;
		case EH::Enemy::eState::Dead:
			break;
		default:
			break;
		}

	}

	void Niflheim::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Niflheim::OnCollisionEnter(Collider* other)
	{
	}

	void Niflheim::OnCollisionStay(Collider* other)
	{
	}

	void Niflheim::OnCollisionExit(Collider* other)
	{
	}

	void Niflheim::Idle()
	{
		float checkTime = GetCheckTime();
		Animator* ani = GetComponent<Animator>();
		SetCheckTime(checkTime += Time::GetDeltaTime());
		if (mEnter == 0 && 1.7f < checkTime)
		{
			ani->PlayAnimation(L"NiflheimRightIdle", true);
		}
	}

	void Niflheim::Attack()
	{
	}

	void Niflheim::Dead()
	{
	}
}
