#include "EHEnemy.h"
#include "EHResources.h"
#include "EHSound.h"
#include "EHImageObject.h"
#include "EHObject.h"

namespace EH
{
	UINT Enemy::mCheck1 = 0;
	Enemy::Enemy()
		:
		   mDelayTime(0.f)
		 , mCheckTime(0.f)
		 , mSubDelayTime(0.f)
		 , mSubCheckTime(0.f)
		 , mCurState(eState::Idle)
		 , mTarget(nullptr)
		 , mMaxHp(40)
	{
		mHitMonster = Resources::Load<Sound>(L"monsterhitsound", L"..\\Resources\\Sound\\Enemy\\public\\Hit_Monster.wav");
		ImageObject* hpbase = object::Instantiate<ImageObject>(enums::eLayerType::UI);
		Transform* hpbasetr = hpbase->GetComponent<Transform>();
		SpriteRenderer* hpbasesr = hpbase->GetComponent<SpriteRenderer>();
		Texture* texture = Resources::Load<Texture>(L"enemyhpbase" + std::to_wstring(mCheck1), L"..\\Resources\\UI\\EnemyHpbase.bmp");
		hpbasetr->SetScale(Math::Vector2<float>(70.f, 20.f));
		hpbasesr->SetImg(texture);
		mHpbaseimage = hpbase;
		texture->Enabled(false);

		ImageObject* hp = object::Instantiate<ImageObject>(enums::eLayerType::UI);
		hpbasetr = hp->GetComponent<Transform>();
		hpbasesr = hp->GetComponent<SpriteRenderer>();
		texture = Resources::Load<Texture>(L"enemyhp" + std::to_wstring(mCheck1), L"..\\Resources\\UI\\EnemyHp.bmp");
		hpbasetr->SetScale(Math::Vector2<float>(64.f, 14.f));
		hpbasesr->SetImg(texture);
		mHpimage = hp;
		texture->Enabled(false);

		mCheck1++;
	}

	Enemy::~Enemy()
	{
		Destroy(mHpbaseimage);
		Destroy(mHpimage);
	}

	void Enemy::Initialize()
	{
	}

	void Enemy::Update()
	{
		GameObject::Update();
		
		Transform* tr = GetComponent<Transform>();
		Math::Vector2<float> pos = tr->Getpos();
		Math::Vector2<float> scale = tr->GetScale();

		mHpbaseimage->GetComponent<Transform>()->SetPos(Math::Vector2<float>(tr->Getpos().x, tr->Getpos().y + scale.y / 2.f));

		Transform* hptr = mHpimage->GetComponent<Transform>();
		hptr->SetPos(Math::Vector2<float>(tr->Getpos().x - ((64.f - 64.f * ((float)mHP / (float)mMaxHp)) / 2.f), tr->Getpos().y + scale.y / 2.f));
		hptr->SetScale(Math::Vector2<float>(64.f * ((float)mHP / (float)mMaxHp), hptr->GetScale().y));
	}

	void Enemy::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Enemy::OnCollisionEnter(Collider* other)
	{
	}

	void Enemy::OnCollisionStay(Collider* other)
	{
	}

	void Enemy::OnCollisionExit(Collider* other)
	{
	}
}
