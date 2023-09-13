#include "EHBullet.h"
#include "EHPlayer.h"
#include "EHCamera.h"
#include "EHObjdata.h"
#include "EHCeil.h"
#include "EHFloor.h"
#include "EHWall.h"
#include "EHResources.h"
#include "EHSound.h"
#include "EHEnemy.h"
#include "EHSceneManager.h"
#include "EHCollisionManager.h"
#include "EHEffect.h"
#include "EHObject.h"
#include "EHWeapon.h"
#include "EHDamageEffect.h"

namespace EH
{
	Bullet::Bullet()
		:
		mRadian(0.f)
		, mDamage(0)
		, mDeleteTime(0.f)
		, mCheckTime(0.f)
		, mIsStop(true)
		, mIsPass(true)
		, mIsDelete(true)
		, mSpeed(1.f)
		, mIsPlayer(false)
		, mHoming(false)
		, mTarget(nullptr)
		, mHomingTime(0.5f)
		, mIsLaser(false)
		, mIsStar(false)
		, mIsHit(false)
	{
		mHitSound = Resources::Load<Sound>(L"playerhitsound", L"..\\Resources\\Sound\\Enemy\\public\\Hit_Player.wav");
		CollisionManager::CollisionLayerCheck(enums::eLayerType::Bullet, enums::eLayerType::Enemy, true);
	}

	Bullet::~Bullet()
	{
	}

	void Bullet::Initialize()
	{
	}

	void Bullet::Update()
	{
		GameObject::Update();
		if (!mIsStop)
		{
			if (!mHoming)
			{
				Transform* tr = GetComponent<Transform>();
				mCheckTime += Time::GetDeltaTime();
				Math::Vector2<float> pos = tr->Getpos();
				pos.y += sinf(mRadian) * 300.f * Time::GetDeltaTime() * mSpeed;
				pos.x += cosf(mRadian) * 300.f * Time::GetDeltaTime() * mSpeed;
				tr->SetPos(pos);
				if (mDeleteTime < mCheckTime && mIsDelete)
				{
					if (mIsStar)
					{
						Effect* bulletFX = object::Instantiate<Effect>(enums::eLayerType::UI);
						Texture* texture = Resources::Load<Texture>(L"Icicledestroy", L"..\\Resources\\Enemy\\Boss\\Niflheim\\Attack\\Icicle\\IcicleDestroy.bmp");
						Transform* tr = bulletFX->GetComponent<Transform>();
						Animator* ani = bulletFX->AddComponent<Animator>();

						tr->SetPos(GetComponent<Transform>()->Getpos());
						tr->SetScale(Math::Vector2<float>(140.f, 192.f));

						ani->CreateAnimation(L"Icicledestroy", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(35.f, 48.f), Math::Vector2<float>(0.f, 0.f), 3, 0.1f);
						ani->PlayAnimation(L"Icicledestroy", false);
					}
				}
			}
			else
			{
				mHomingCheckTime += Time::GetDeltaTime();

				if (SceneManager::GetCurScene()->GetLayer(enums::eLayerType::Enemy).GetObjects().size() == 0)
				{
					Effect* bulletFX = object::Instantiate<Effect>(enums::eLayerType::UI);
					Texture* texture = Resources::Load<Texture>(L"StarBulletFX", L"..\\Resources\\Player\\Basic\\Attack\\LalaWand\\StarBulletFX\\StarBulletFX.bmp");
					Transform* tr = bulletFX->GetComponent<Transform>();
					Animator* ani = bulletFX->AddComponent<Animator>();

					tr->SetPos(GetComponent<Transform>()->Getpos());
					tr->SetScale(Math::Vector2<float>(144.f, 140.f));

					ani->CreateAnimation(L"StarBulletFX", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(36.f, 35.f), Math::Vector2<float>(0.f, 0.f), 7, 0.1f);
					ani->PlayAnimation(L"StarBulletFX", false);
					Destroy(this);
				}

				if (mTarget == nullptr)
				{
					if (!SceneManager::GetCurScene()->GetLayer(enums::eLayerType::Enemy).GetObjects().empty())
					{
						mTarget = dynamic_cast<Enemy*>(SceneManager::GetCurScene()->GetLayer(enums::eLayerType::Enemy).GetObjects().front());
					}
				}

				if (mTarget != nullptr)
				{
					bool isExist = false;
					std::vector<GameObject*>::iterator iter = SceneManager::GetCurScene()->GetLayer(enums::eLayerType::Enemy).GetObjects().begin();
					
					for (;iter != SceneManager::GetCurScene()->GetLayer(enums::eLayerType::Enemy).GetObjects().end();iter++)
					{
						if ((*iter) == mTarget)
						{
							isExist = true;
						}
					}

					if (!isExist)
					{
						mTarget = nullptr;
						return;
					}

					if (mHomingTime > mHomingCheckTime)
					{
						Transform* tr = GetComponent<Transform>();
						Math::Vector2<float> pos = tr->Getpos();
						pos.y += sinf(mRadian) * 300.f * Time::GetDeltaTime() * mSpeed;
						pos.x += cosf(mRadian) * 300.f * Time::GetDeltaTime() * mSpeed;
						tr->SetPos(pos);
					}
					else
					{
						Transform* tr = GetComponent<Transform>();
						if (mTarget == nullptr)
							return;
						Transform* targettr = mTarget->GetComponent<Transform>();
						if (targettr == nullptr)
							return;
						Math::Vector2<float> targettrpos = targettr->Getpos();
						float radian = Math::Radian(targettrpos, tr->Getpos()) * (mCheckTime / 1.f);
						Math::Vector2<float> pos = tr->Getpos();
						pos.y += sinf(radian) * 300.f * Time::GetDeltaTime() * mSpeed;
						pos.x += cosf(radian) * 300.f * Time::GetDeltaTime() * mSpeed;
						tr->SetPos(pos);
					}
				}
				mCheckTime += Time::GetDeltaTime();
				if (mDeleteTime < mCheckTime && mIsDelete)
				{
					Effect* bulletFX = object::Instantiate<Effect>(enums::eLayerType::UI);
					Texture* texture = Resources::Load<Texture>(L"StarBulletFX", L"..\\Resources\\Player\\Basic\\Attack\\LalaWand\\StarBulletFX\\StarBulletFX.bmp");
					Transform* tr = bulletFX->GetComponent<Transform>();
					Animator* ani = bulletFX->AddComponent<Animator>();

					tr->SetPos(GetComponent<Transform>()->Getpos());
					tr->SetScale(Math::Vector2<float>(144.f, 140.f));

					ani->CreateAnimation(L"StarBulletFX", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(36.f, 35.f), Math::Vector2<float>(0.f, 0.f), 7, 0.1f);
					ani->PlayAnimation(L"StarBulletFX", false);
					Destroy(this);
				}
			}
		}
		else
		{
			if (mIsLaser)
			{
				mCheckTime += Time::GetDeltaTime();
				if (mDeleteTime < mCheckTime && mIsDelete)
				{
					Destroy(this);
				}
			}
		}
	}

	void Bullet::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Bullet::OnCollisionEnter(Collider* other)
	{
		if (mIsHit)
		{
			Weapon* weapon = dynamic_cast<Weapon*>(other->GetOwner());
			if (weapon != nullptr)
			{
				Destroy(this);
			}
		}

		if (!mIsPlayer)
		{
			Player* player = dynamic_cast<Player*>(other->GetOwner());

			if (player != nullptr)
			{
				Objdata::SetHP(Objdata::GetHP() - mDamage);
				mHitSound->Play(false);
				if (mIsDelete)
					Destroy(this);
			}

			if (!mIsPass)
			{
				Ceil* ceil = dynamic_cast<Ceil*>(other->GetOwner());
				Floor* floor = dynamic_cast<Floor*>(other->GetOwner());
				Wall* wall = dynamic_cast<Wall*>(other->GetOwner());
				if (ceil != nullptr)
				{
					Destroy(this);
				}
				else if (floor != nullptr)
				{
					Destroy(this);
				}
				else if (wall != nullptr)
				{
					Destroy(this);
				}
			}
		}
		else
		{
			Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());

			if (enemy != nullptr)
			{
				UINT hp = enemy->GetHP();
				enemy->SetHP(hp -= mDamage);
				mHitSound->Play(false);
				if (mIsDelete && mIsStar)
				{
					Destroy(this);
					Effect* bulletFX = object::Instantiate<Effect>(enums::eLayerType::UI);
					Texture* texture = Resources::Load<Texture>(L"StarBulletFX", L"..\\Resources\\Player\\Basic\\Attack\\LalaWand\\StarBulletFX\\StarBulletFX.bmp");
					Transform* tr = bulletFX->GetComponent<Transform>();
					Animator* ani = bulletFX->AddComponent<Animator>();

					tr->SetPos(GetComponent<Transform>()->Getpos());
					tr->SetScale(Math::Vector2<float>(144.f, 140.f));

					ani->CreateAnimation(L"StarBulletFX", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(36.f, 35.f), Math::Vector2<float>(0.f, 0.f), 7, 0.1f);
					ani->PlayAnimation(L"StarBulletFX", false);
				}
				else if(mIsDelete && !mIsLaser)
				{
					Destroy(this);
				}

				Transform* tr = GetComponent<Transform>();

				DamageEffect* damageef = object::Instantiate<DamageEffect>(enums::eLayerType::UI);
				Transform* eftr = damageef->GetComponent<Transform>();
				eftr->SetPos(enemy->GetComponent<Transform>()->Getpos());
				eftr->SetScale(Math::Vector2<float>(14.f, 22.f));
				damageef->SetDamage(1);

				DamageEffect* damageef2 = object::Instantiate<DamageEffect>(enums::eLayerType::UI);
				eftr = damageef2->GetComponent<Transform>();
				eftr->SetPos(Math::Vector2<float>(enemy->GetComponent<Transform>()->Getpos().x + 14.f, enemy->GetComponent<Transform>()->Getpos().y));
				eftr->SetScale(Math::Vector2<float>(14.f, 22.f));
				damageef2->SetDamage(0);
			}

			if (!mIsPass)
			{
				Ceil* ceil = dynamic_cast<Ceil*>(other->GetOwner());
				Floor* floor = dynamic_cast<Floor*>(other->GetOwner());
				Wall* wall = dynamic_cast<Wall*>(other->GetOwner());
				if (ceil != nullptr)
				{
					Destroy(this);
					// 부서지는거
				}
				else if (floor != nullptr)
				{
					// 부서지는거
					Destroy(this);
				}
				else if (wall != nullptr)
				{
					// 부서지는거
					Destroy(this);
				}
			}
		}
	}

	void Bullet::OnCollisionStay(Collider* other)
	{
	}

	void Bullet::OnCollisionExit(Collider* other)
	{
	}
}
