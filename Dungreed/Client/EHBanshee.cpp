#include "EHBanshee.h"
#include "EHBullet.h"
#include "EHObject.h"
#include "EHResources.h"

namespace EH
{
	Banshee::Banshee()
	{
	}

	Banshee::~Banshee()
	{
	}

	void Banshee::Initialize()
	{
	}

	void Banshee::Update()
	{
		GameObject::Update();
		float checktime = GetCheckTime();
		SetCheckTime(checktime += Time::GetDeltaTime());
		if (GetDelayTime() < checktime)
		{
			for (size_t i = 0; i < 12; i++)
			{
				Bullet* bullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
				Transform* bullettr = GetComponent<Transform>();
				Transform* bansheetr = GetComponent<Transform>();
				Math::Vector2<float> bansheepos = bansheetr->Getpos();
				bullettr->SetPos(Math::Vector2<float>(bansheepos.x, bansheepos.y));
				bullettr->SetScale(Math::Vector2<float>(52.f, 64.f));
				Texture* texture = Resources::Load<Texture>(L"BansheeBullet", L"..\\Resources\\Enemy\\JailField\\Banshee\\Attack\\BansheeBullet\\BansheeBullet0.png");
				bullet->AddComponent<Animator>();
				bullet->AddComponent<Collider>();
				bullet->GetComponent<Collider>()->SetScale(Math::Vector2(52.f, 64.f));
;				bullet->GetComponent<Animator>()->CreateAnimation(L"BansheeBullet", texture, 
					Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(13.f, 16.f), 
					Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
				bullet->GetComponent<Animator>()->PlayAnimation(L"BansheeBullet",true);
				bullet->SetDeleteTime(2.f);
				bullet->SetRadian(0.39*i);
			}
		}
	}

	void Banshee::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Banshee::OnCollisionEnter(Collider* other)
	{
	}

	void Banshee::OnCollisionStay(Collider* other)
	{
	}

	void Banshee::OnCollisionExit(Collider* other)
	{
	}
}