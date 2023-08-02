#include "EHCoin.h"
#include "EHPlayer.h"
#include "EHObjdata.h"
#include "EHResources.h"

namespace EH
{
	Coin::Coin()
	{
		Collider* col = AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(40.f, 40.f));
		Rigidbody* rb = AddComponent<Rigidbody>();
		rb->SetGround(false);
		Texture* texture = Resources::Load<Texture>(L"GoldCoin", L"..\\Resources\\Item\\Coin\\GoldCoinSheet.bmp");
		Animator* animator = AddComponent<Animator>();
		animator->CreateAnimation(L"GoldCoin", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(7.f, 7.f), Math::Vector2<float>(0.f, 0.f), 8, 0.1f);
		animator->PlayAnimation(L"GoldCoin", true);
	}

	Coin::~Coin()
	{
	}

	void Coin::Initialize()
	{
	}

	void Coin::Update()
	{
		GameObject::Update();
	}

	void Coin::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Coin::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			Objdata::SetGold(Objdata::GetGold() + 100);
			Destroy(this);
		}
	}

	void Coin::OnCollisionStay(Collider* other)
	{
	}

	void Coin::OnCollisionExit(Collider* other)
	{
	}
}