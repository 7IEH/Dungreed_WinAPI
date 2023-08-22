#include "EHNiflheim.h"
#include "EHResources.h"
#include "EHObject.h"
#include "EHPlayer.h"
#include <time.h>

namespace EH
{
	Niflheim::Niflheim()
		:
		  mEnter(0)
		, mType(eBossAttack::None)
		, mCheck1(0)
		, mCheck2(0)
		, mStop(false)
		, mMove(0.f)
	{
		// Time
		SetDelayTime(3.f);

		// Animator
		Animator* ani = AddComponent<Animator>();
		Texture* texture = Resources::Load<Texture>(L"NiflheimRightEnter", L"..\\Resources\\Enemy\\Boss\\Niflheim\\Enter\\NiflheimEnter.bmp");
		ani->CreateAnimation(L"NiflheimRightEnter", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(42.f, 33.f), Math::Vector2<float>(0.f, 0.f), 16, 0.1f);
		texture = Resources::Load<Texture>(L"NiflheimRightIdle", L"..\\Resources\\Enemy\\Boss\\Niflheim\\Idle\\Right\\NiflheimRightIdle.bmp");
		ani->CreateAnimation(L"NiflheimRightIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(42.f, 33.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		texture = Resources::Load<Texture>(L"NiflheimLeftIdle", L"..\\Resources\\Enemy\\Boss\\Niflheim\\Idle\\Left\\NiflheimLeftIdle.bmp");
		ani->CreateAnimation(L"NiflheimLeftIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(42.f, 33.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		ani->PlayAnimation(L"NiflheimRightEnter", true);

		// Collider
		Collider* col = AddComponent<Collider>();
		col->SetScale(Math::Vector2<float>(168.f, 132.f));
		col->enabled(false);

		// Rigidbody
		Rigidbody* rigid = AddComponent<Rigidbody>();
		rigid->SetGround(true);

		// IcePillar
		Transform* tr = GetComponent<Transform>();

		SetTarget(SceneManager::GetCurScene()->GetPlayer());

		for (int i = 0;i < 4;i++)
		{
			mIcePillar[i] = object::Instantiate<IcePillar>(enums::eLayerType::Enemy);
			mIcePillar[i]->SetOwner(this);
		}	
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
		case EH::Enemy::eState::Dealtime:
			Dealtime();
			break;
		case EH::Enemy::eState::Attack:
			Attack();
			break;
		case EH::Enemy::eState::Dead:
			Dead();
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
		Transform* tr = GetComponent<Transform>();

		tr->SetPos(Math::Vector2<float>(992.f, 520.f));

		/*for (size_t i = 0; i < 4; i++)
		{
			if(mIcePillar[i]->GetHP()<=0)
			{
				mCheck1++;
			}
		}*/

		if (mCheck1 == 4)
		{
			SetState(eState::Dealtime);
			Rigidbody* rigid = GetComponent<Rigidbody>();
			rigid->SetGround(false);
			return;
		}
		else
		{
			mCheck1 = 0;
		}

		if (mEnter != 1)
		{
			SetCheckTime(checkTime += Time::GetDeltaTime());
		}
		if (mEnter == 0 && 1.7f < checkTime)
		{
			Animator* ani = GetComponent<Animator>();
			ani->PlayAnimation(L"NiflheimRightIdle", true);
			mEnter = 1;
			SetCheckTime(0.f);
		}

		float thinktime = GetCheckTime();
		SetCheckTime(thinktime += Time::GetDeltaTime());

		if (GetDelayTime() < thinktime)
		{
			SetState(eState::Attack);
			SetCheckTime(0.f);
		}

		// È¸Àü
		mMove += 0.1f;
		for (int i = 0;i < 4;i++)
		{
			Transform* pillartr = mIcePillar[i]->GetComponent<Transform>();
			mIcePillar[i]->SetDegree((70.f * mMove + 90.f* i)+90.f);
			pillartr->SetPos(Math::Vector2<float>(tr->Getpos().x + 200.f * cosf((70.f * mMove + 90.f * i) * (3.14f / 180.f)), tr->Getpos().y + 200.f * sinf((70.f * mMove + 90.f * i) * (3.14f / 180.f))));
		}
	}

	void Niflheim::Attack()
	{
		srand((UINT)time(NULL));
		if (mType == eBossAttack::None)
			mType = eBossAttack::Bullet;

		switch (mType)
		{
		case EH::eBossAttack::Bullet:
			Bullet();
			break;
		case EH::eBossAttack::Barrage:
			Barrage();
			break;
		case EH::eBossAttack::FourBarrage:
			FourBarrage();
			break;
		case EH::eBossAttack::SquareFourBarrage:
			SquareFourBarrage();
			break;
		case EH::eBossAttack::Bullet2:
			Bullet2();
			break;
		case EH::eBossAttack::None:
			break;
		default:
			break;
		}
	}

	void Niflheim::Dealtime()
	{
		float dealtime = GetCheckTime();
		SetCheckTime(dealtime += Time::GetDeltaTime());
		Collider* col = GetComponent<Collider>();
		col->enabled(true);

		if (4.f < dealtime)
		{
			Rigidbody* rigid = GetComponent<Rigidbody>();
			rigid->SetGround(true);
			col->enabled(false);
			SetState(eState::Idle);
			mCheck1 = 0;
		}
	}

	void Niflheim::Dead()
	{

	}

	void Niflheim::Bullet()
	{
		float movetime = GetCheckTime();
		SetCheckTime(movetime += Time::GetDeltaTime());


		if (mCheck2 == 4)
		{
			SetState(eState::Idle);
			SetCheckTime(0.f);
			mType = eBossAttack::None;
			mCheck2 = 0;
			return;
		}

		if (2.f < movetime)
		{
			float bullettime = GetSubCheckTime();
			SetSubCheckTime(bullettime += Time::GetDeltaTime());

			if (!mStop)
			{
				mIcePillar[mCheck2]->SetTargetPos(GetTarget()->GetComponent<Transform>()->Getpos());
				mStop = true;
				mIcePillar[mCheck2]->SetType(ePillarAttack::Bullet);
			}
				

			mMove += 0.1f;
			for (int i = 0;i < 4;i++)
			{
				mIcePillar[i]->SetDegree((70.f * mMove + 90.f * i) + 90.f);
			}
		}
		else
		{
			for (int i = 0;i < 4;i++)
			{
				Transform* tr = mIcePillar[i]->GetComponent<Transform>();
				Math::Vector2<float> dir;
				if (i == 0)
				{
					dir = Math::Vector2<float>(1584.f, 800.f) - tr->Getpos();
				}
				else if (i == 1)
				{
					dir = Math::Vector2<float>(1584.f, 200.f) - tr->Getpos();
					
				}
				else if (i == 2)
				{
					dir = Math::Vector2<float>(400.f, 200.f) - tr->Getpos();
					
				}
				else
				{
					dir = Math::Vector2<float>(400.f, 800.f) - tr->Getpos();
					
				}

				dir.normalized<float>();

				
				tr->SetPos(Math::Vector2<float>(tr->Getpos().x + 400.f * dir.x * Time::GetDeltaTime(), tr->Getpos().y + 400.f * dir.y * Time::GetDeltaTime()));
			}
		}
		
	}

	void Niflheim::Barrage()
	{
		SetState(eState::Idle);
		mType = eBossAttack::None;
	}

	void Niflheim::FourBarrage()
	{
		SetState(eState::Idle);
		mType = eBossAttack::None;
	}

	void Niflheim::SquareFourBarrage()
	{
		SetState(eState::Idle);
		mType = eBossAttack::None;
	}

	void Niflheim::Bullet2()
	{
		SetState(eState::Idle);
		mType = eBossAttack::None;
	}
}
