#include "EHIcePillar.h"
#include "EHResources.h"
#include "EHNiflheim.h"
#include "EHObject.h"
#include "EHBullet.h"

namespace EH
{
	UINT IcePillar::mCheck1 = 0;
	IcePillar::IcePillar()
		:
		  mDegree(0.f)
		, mType(ePillarAttack::None)
	{
		Transform* tr = GetComponent<Transform>();
		SpriteRenderer* sr = AddComponent<SpriteRenderer>();
		Texture* texture = Resources::Load<Texture>(L"IcePillar" + std::to_wstring(mCheck1), L"..\\Resources\\Enemy\\Boss\\Niflheim\\UI\\IcePillar19.png");
		tr->SetScale(Math::Vector2<float>(248.f, 132.f));
		sr->SetImg(texture);
		Collider* col = AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(40.f, 40.f));
		mCheck1++;
	}

	IcePillar::~IcePillar()
	{
	}

	void IcePillar::Initialize()
	{
	}

	void IcePillar::Update()
	{
		GameObject::Update();

		SpriteRenderer* sr = GetComponent<SpriteRenderer>();
		Texture* texture = sr->GetImg();
		texture->SetDegree(mDegree);

		switch (mType)
		{
		case EH::ePillarAttack::Bullet:
			BulletP();
			break;
		case EH::ePillarAttack::Barrage:
			break;
		case EH::ePillarAttack::FourBarrage:
			break;
		case EH::ePillarAttack::SquareFourBarrage:
			break;
		case EH::ePillarAttack::Bullet2:
			break;
		case EH::ePillarAttack::None:
			break;
		default:
			break;
		}
	}

	void IcePillar::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void IcePillar::BulletP()
	{
		float checktime = GetCheckTime();
		SetCheckTime(checktime += Time::GetDeltaTime());

		float createtime = GetSubCheckTime();
		SetSubCheckTime(createtime += Time::GetDeltaTime());
		if (2.f < checktime)
		{
			mOwner->SetStop(false);
			mOwner->SetCheck(mOwner->GetCheck() + 1);
			SetCheckTime(0.f);
			mType = ePillarAttack::None;
		}
		Transform* tr = GetComponent<Transform>();
		float radian = Math::Radian(mTarget, tr->Getpos());
		

		if (0.2f < createtime)
		{
			SetSubCheckTime(0.f);
			Bullet* bullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
			Collider* col = bullet->AddComponent<Collider>();

			Transform* bullettr = bullet->GetComponent<Transform>();
			bullettr->SetPos(tr->Getpos());

			col->SetScale(Math::Vector2<float>(40.f, 40.f));
			bullettr->SetScale(Math::Vector2<float>(36.f, 72.f));

			bullet->SetRadian(radian);
			bullet->SetStop(false);
			bullet->SetDeleteTime(10.f);
		}
	}

	void IcePillar::Barrage()
	{

	}

	void IcePillar::Barrage2()
	{

	}
}