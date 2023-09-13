#include "EHNiflheim.h"
#include "EHResources.h"
#include "EHObject.h"
#include "EHPlayer.h"
#include "EHWeapon.h"
#include "EHCollisionManager.h"
#include "EHDeadObj.h"
#include "EHCanvas.h"
#include "EHImageObject.h"
#include "EHBullet.h"
#include "EHDamageEffect.h"
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
		, mCheck3(0)
		, mAttack(nullptr)
		, mIsRight(true)
		, mPhase(0)
		, mCheck4(-1)
		, mStart(false)
	{
		SetHP(100.f);

		// Time
		SetDelayTime(3.f);

		srand((UINT)time(NULL));

		// Animator
		Animator* ani = AddComponent<Animator>();
		Texture* texture = Resources::Load<Texture>(L"NiflheimRightEnter", L"..\\Resources\\Enemy\\Boss\\Niflheim\\Enter\\NiflheimEnter.bmp");
		ani->CreateAnimation(L"NiflheimRightEnter", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(42.f, 33.f), Math::Vector2<float>(0.f, 0.f), 16, 0.1f);
		texture = Resources::Load<Texture>(L"NiflheimRightIdle", L"..\\Resources\\Enemy\\Boss\\Niflheim\\Idle\\Right\\NiflheimRightIdle.bmp");
		ani->CreateAnimation(L"NiflheimRightIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(42.f, 33.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		texture = Resources::Load<Texture>(L"NiflheimLeftIdle", L"..\\Resources\\Enemy\\Boss\\Niflheim\\Idle\\Left\\NiflheimLeftIdle.bmp");
		ani->CreateAnimation(L"NiflheimLeftIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(42.f, 33.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		texture = Resources::Load<Texture>(L"NiflheimRightAttack", L"..\\Resources\\Enemy\\Boss\\Niflheim\\Attack\\Right\\NiflheimAttack.bmp");
		ani->CreateAnimation(L"NiflheimRightAttack", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(42.f, 33.f), Math::Vector2<float>(0.f, 0.f), 11, 0.1f);
		texture = Resources::Load<Texture>(L"NiflheimLeftAttack", L"..\\Resources\\Enemy\\Boss\\Niflheim\\Attack\\Left\\NiflheimAttack.bmp");
		ani->CreateAnimation(L"NiflheimLeftAttack", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(42.f, 33.f), Math::Vector2<float>(0.f, 0.f), 11, 0.1f);
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
			mIcePillar[i]->SetHP(40.f);
		}

		Canvas* BossUICanvas = object::Instantiate<Canvas>(enums::eLayerType::UI);
		texture = Resources::Load<Texture>(L"BossLifeBack", L"..\\Resources\\Enemy\\Boss\\UI\\BossLifeBack.png");
		BossUICanvas->AddImageObject(L"BossLifeBack", texture, false, Math::Vector2<float>(640.f, 670.f), Math::Vector2<float>(500.f, 64.f));

		texture = Resources::Load<Texture>(L"BossHP", L"..\\Resources\\Enemy\\Boss\\UI\\BossLife.png");
		BossUICanvas->AddImageObject(L"BossHP", texture, false, Math::Vector2<float>(676.f, 670.f), Math::Vector2<float>(402.f, 56.f));

		texture = Resources::Load<Texture>(L"BossHPBase", L"..\\Resources\\Enemy\\Boss\\UI\\BossLifeBase.png");
		BossUICanvas->AddImageObject(L"BossHPBase", texture, false, Math::Vector2<float>(640.f, 670.f), Math::Vector2<float>(500.f, 64.f));

		texture = Resources::Load<Texture>(L"BossPortrait", L"..\\Resources\\Enemy\\Boss\\UI\\BossSkellPortrait.png");
		BossUICanvas->AddImageObject(L"BossPortrait", texture, false, Math::Vector2<float>(435.f, 670.f), Math::Vector2<float>(68.f, 40.f));

		mCanvas = BossUICanvas;

		mDefeatSound = Resources::Load<Sound>(L"bossDefeat", L"..\\Resources\\Sound\\Enemy\\JailField\\Belial\\bossDefeat.wav");
		mIcicleSound = Resources::Load<Sound>(L"icicle", L"..\\Resources\\Sound\\Enemy\\IceField\\ice_spell_forming_shards_03.wav");
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

		mCheck1 = 0;
		for (size_t i = 0; i < 4; i++)
		{
			if (mIcePillar[i] == nullptr)
			{
				mCheck1++;
			}
			else if (mIcePillar[i]->GetHP() <= 0)
			{
				if (mIcePillar[i]->GetType() == ePillarAttack::Barrage)
				{
					mCheck2++;
				}
				mIcePillar[i]->SetType(ePillarAttack::Dead);
				mIcePillar[i]->GetComponent<Animator>()->PlayAnimation(L"IcePillarDestroy", false);
				mIcePillar[i] = nullptr;
				mCheck1++;
			}
		}

		if (GetState() != eState::Dead)
		{
			if (GetState() != eState::Dealtime)
			{
				if (mCheck1 == 4)
				{
					mCheck1 = 0;
					SetState(eState::Dealtime);
					Rigidbody* rigid = GetComponent<Rigidbody>();
					Collider* col = GetComponent<Collider>();
					col->enabled(true);
					rigid->SetGround(false);
					SetCheckTime(0.f);
					return;
				}
			}
		}

		if (GetHP() <= 50)
		{
			mPhase = 1;
		}

		if (GetHP() <= 0)
		{
			SetState(eState::Dead);
			mCheck3 = 0;
		}

		// UI Update
		ImageObject* hp = mCanvas->Find(L"BossHP");
		Transform* tr = hp->GetComponent<Transform>();
		tr->SetPos(Math::Vector2<float>(676.f - ((402.f - 402.f * ((float)GetHP() / (float)100.f)) / 2.f), tr->Getpos().y));
		tr->SetScale(Math::Vector2<float>(402.f * ((float)GetHP() / (float)100.f), tr->GetScale().y));

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
		// 플레이어 오브젝트 충돌
		Weapon* weapon = dynamic_cast<Weapon*>(other->GetOwner());
		if (weapon != nullptr)
		{
			UINT hp = GetHP();
			SetHP(hp -= 20);
			mAttack = weapon;
			GetHitSound()->Play(false);

			Transform* tr = GetComponent<Transform>();

			DamageEffect* damageef = object::Instantiate<DamageEffect>(enums::eLayerType::UI);
			Transform* eftr = damageef->GetComponent<Transform>();
			eftr->SetPos(tr->Getpos());
			eftr->SetScale(Math::Vector2<float>(14.f, 22.f));
			damageef->SetDamage(2);

			DamageEffect* damageef2 = object::Instantiate<DamageEffect>(enums::eLayerType::UI);
			eftr = damageef2->GetComponent<Transform>();
			eftr->SetPos(Math::Vector2<float>(tr->Getpos().x + 14.f, tr->Getpos().y));
			eftr->SetScale(Math::Vector2<float>(14.f, 22.f));
			damageef2->SetDamage(0);
		}
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
		Transform* targettr = GetTarget()->GetComponent<Transform>();
		Animator* ani = GetComponent<Animator>();

		tr->SetPos(Math::Vector2<float>(992.f, 520.f));

		if (mEnter != 1)
		{
			SetCheckTime(checkTime += Time::GetDeltaTime());
		}
		if (mEnter == 0 && 1.7f < checkTime)
		{
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

		if (tr->Getpos().x < targettr->Getpos().x)
		{
			ani->PlayAnimation(L"NiflheimRightIdle", true);
			mIsRight = true;
		}
		else
		{
			ani->PlayAnimation(L"NiflheimLeftIdle", true);
			mIsRight = false;
		}

		// 회전
		mMove += 5.f * Time::GetDeltaTime();
		for (int i = 0;i < 4;i++)
		{
			if (mIcePillar[i] == nullptr)
				continue;
			Transform* pillartr = mIcePillar[i]->GetComponent<Transform>();
			mIcePillar[i]->SetDegree((70.f * mMove + 90.f * i) + 90.f);
			pillartr->SetPos(Math::Vector2<float>(tr->Getpos().x + 200.f * cosf((70.f * mMove + 90.f * i) * (3.14f / 180.f)), tr->Getpos().y + 200.f * sinf((70.f * mMove + 90.f * i) * (3.14f / 180.f))));
		}
	}

	void Niflheim::Attack()
	{
		if (mPhase == 0)
		{
			if (mType == eBossAttack::None)
			{
				if (mCheck4 == 5)
				{
					mCheck4 = -1;
				}
				mType = eBossAttack(mCheck4 += 1);
			}
				//mType = eBossAttack(rand() % (6));
		}
		else if (mPhase == 1)
		{
			if (mStart == false)
			{
				mType = eBossAttack::Spear;
				mStart = true;
			}
			else
			{
				if (mType == eBossAttack::None)
					mType = eBossAttack(rand() % ((UINT)eBossAttack::None));
			}
		}

		switch (mType)
		{
		case EH::eBossAttack::Bullet:
			Bulletp();
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
		case EH::eBossAttack::Icicle:
			Icicle();
			break;
		case EH::eBossAttack::Spear:
			Spear();
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
			SetCheckTime(0.f);
			SetState(eState::Idle);
			for (int i = 0;i < 4;i++)
			{
				mIcePillar[i] = object::Instantiate<IcePillar>(enums::eLayerType::Enemy);
				mIcePillar[i]->SetOwner(this);
				mIcePillar[i]->SetHP(40.f);
			}
			mCheck1 = 0;
			mCheck2 = 0;
			mCheck3 = 0;
		}
	}

	void Niflheim::Dead()
	{
		float timecheck = GetCheckTime();
		float subtimecheck = GetSubCheckTime();
		SetCheckTime(timecheck += Time::GetDeltaTime());
		SetSubCheckTime(subtimecheck += Time::GetDeltaTime());
		Transform* tr = GetComponent<Transform>();
		Math::Vector2<float> pos = tr->Getpos();

		if (mCheck3 == 0)
		{
			if (mAttack != nullptr)
			{
				CollisionManager::ForceExit(GetComponent<Collider>(), mAttack->GetComponent<Collider>());
			}
			Destroy(this);
			mDefeatSound->Play(false);
			SceneManager::GetCurScene()->GetBGM()->Stop(true);
			mCheck3++;
			DeadObj* deadobj = object::Instantiate<DeadObj>(enums::eLayerType::UI);
			Transform* deadtr = deadobj->GetComponent<Transform>();
			deadtr->SetPos(pos);
			deadtr->SetScale(Math::Vector2<float>(168.f,132.f));
			Animator* deadani = deadobj->AddComponent<Animator>();
			Texture* texture = Resources::Load<Texture>(L"Niflheimdead", L"..\\Resources\\Enemy\\Boss\\Niflheim\\Dead\\NiflheimDie.bmp");
			deadani->CreateAnimation(L"Niflheimdead", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(42.f, 33.f), Math::Vector2<float>(0.f, 0.f), 30, 0.1f);
			deadani->PlayAnimation(L"Niflheimdead", false);
		}
	}

	void Niflheim::Bulletp()
	{
		float movetime = GetCheckTime();
		SetCheckTime(movetime += Time::GetDeltaTime());

		if (mCheck2 == 4)
		{
			SetState(eState::Idle);
			SetCheckTime(0.f);
			mType = eBossAttack::None;
			mMove = 0.f;
			mCheck2 = 0;
			return;
		}

		if (2.f < movetime)
		{
			float bullettime = GetSubCheckTime();
			SetSubCheckTime(bullettime += Time::GetDeltaTime());

			if (mIcePillar[mCheck2] == nullptr)
			{
				mCheck2++;
				mStop = false;
			}
			 
			if (!mStop)
			{
				if (mCheck2 == 4)
					return;
				if (mIcePillar[mCheck2] != nullptr)
				{
					mIcePillar[mCheck2]->SetTargetPos(GetTarget()->GetComponent<Transform>()->Getpos());
					mStop = true;
					mIcePillar[mCheck2]->SetType(ePillarAttack::Bullet);
				}
			}


			mMove += 5.f * Time::GetDeltaTime();
			for (int i = 0;i < 4;i++)
			{
				if (mIcePillar[i] == nullptr)
					continue;
				mIcePillar[i]->SetDegree((70.f * mMove + 90.f * i) + 90.f);
			}
		}
		else
		{
			for (int i = 0;i < 4;i++)
			{
				if (mIcePillar[i] == nullptr)
					continue;
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


				tr->SetPos(Math::Vector2<float>(tr->Getpos().x + 500.f * dir.x * Time::GetDeltaTime(), tr->Getpos().y + 500.f * dir.y * Time::GetDeltaTime()));

				mMove += 0.1f;
				for (int i = 0;i < 4;i++)
				{
					if (mIcePillar[i] == nullptr)
						continue;
					Transform* pillartr = mIcePillar[i]->GetComponent<Transform>();
					mIcePillar[i]->SetDegree((70.f * mMove + 90.f * i) + 90.f);
				}
			}
		}

	}

	void Niflheim::Barrage()
	{
		float movetime = GetCheckTime();
		SetCheckTime(movetime += Time::GetDeltaTime());
		Transform* tr = GetComponent<Transform>();
		if (mCheck2 == 4)
		{
			SetState(eState::Idle);
			SetCheckTime(0.f);
			mType = eBossAttack::None;
			mCheck2 = 0;
			mCheck3 = 0;
			mMove = 0.f;
			return;
		}

		if (2.f < movetime)
		{
			float bullettime = GetSubCheckTime();
			SetSubCheckTime(bullettime += Time::GetDeltaTime());

			if (mCheck3 == 0)
			{
				for (int i = 0;i < 4;i++)
				{
					if (mIcePillar[i] == nullptr)
					{
						mCheck2++;
					}
					else
					{
						mIcePillar[i]->SetType(ePillarAttack::Barrage);
					}
				}
				mCheck3++;
			}
		}

		mMove += 0.1f;
		for (int i = 0;i < 4;i++)
		{
			if (mIcePillar[i] == nullptr)
				continue;
			Transform* pillartr = mIcePillar[i]->GetComponent<Transform>();
			mIcePillar[i]->SetDegree((70.f * mMove + 90.f * i) + 90.f);
			pillartr->SetPos(Math::Vector2<float>(tr->Getpos().x + 200.f * cosf((70.f * mMove + 90.f * i) * (3.14f / 180.f)), tr->Getpos().y + 200.f * sinf((70.f * mMove + 90.f * i) * (3.14f / 180.f))));
		}
	}

	void Niflheim::FourBarrage()
	{
		float movetime = GetCheckTime();
		SetCheckTime(movetime += Time::GetDeltaTime());

		if (mCheck2 == 4)
		{
			SetState(eState::Idle);
			SetCheckTime(0.f);
			mType = eBossAttack::None;
			mCheck2 = 0;
			mCheck3 = 0;
			mMove = 0.f;
			return;
		}

		if (1.f < movetime)
		{
			float bullettime = GetSubCheckTime();
			SetSubCheckTime(bullettime += Time::GetDeltaTime());

			if (mCheck3 == 0)
			{
				for (int i = 0;i < 4;i++)
				{
					if (mIcePillar[i] == nullptr)
					{
						mCheck2++;
					}
					else
					{
						mIcePillar[i]->SetType(ePillarAttack::Barrage);
					}
				}
				mCheck3++;
			}


			mMove += 0.1f;
			for (int i = 0;i < 4;i++)
			{
				if (mIcePillar[i] == nullptr)
					continue;
				mIcePillar[i]->SetDegree((70.f * mMove + 90.f * i) + 90.f);
			}
		}
		else
		{
			for (int i = 0;i < 4;i++)
			{
				if (mIcePillar[i] == nullptr)
					continue;
				Transform* tr = mIcePillar[i]->GetComponent<Transform>();
				Math::Vector2<float> dir;
				if (i == 0)
				{
					dir = Math::Vector2<float>(600.f, 500.f) - tr->Getpos();
				}
				else if (i == 1)
				{
					dir = Math::Vector2<float>(850.f, 500.f) - tr->Getpos();

				}
				else if (i == 2)
				{
					dir = Math::Vector2<float>(1100.f, 500.f) - tr->Getpos();

				}
				else
				{
					dir = Math::Vector2<float>(1350.f, 500.f) - tr->Getpos();

				}

				dir.normalized<float>();
				tr->SetPos(Math::Vector2<float>(tr->Getpos().x + 500.f * dir.x * Time::GetDeltaTime(), tr->Getpos().y + 500.f * dir.y * Time::GetDeltaTime()));
			}


			mMove += 0.1f;
			for (int i = 0;i < 4;i++)
			{
				if (mIcePillar[i] == nullptr)
					continue;
				Transform* pillartr = mIcePillar[i]->GetComponent<Transform>();
				mIcePillar[i]->SetDegree((70.f * mMove + 90.f * i) + 90.f);
			}
		}
	}

	void Niflheim::SquareFourBarrage()
	{
		float movetime = GetCheckTime();
		SetCheckTime(movetime += Time::GetDeltaTime());

		if (mCheck2 == 4)
		{
			SetState(eState::Idle);
			SetCheckTime(0.f);
			mType = eBossAttack::None;
			mCheck2 = 0;
			mCheck3 = 0;
			mMove = 0.f;
			return;
		}

		if (2.f < movetime)
		{
			float bullettime = GetSubCheckTime();
			SetSubCheckTime(bullettime += Time::GetDeltaTime());

			if (mCheck3 == 0)
			{
				for (int i = 0;i < 4;i++)
				{
					if (mIcePillar[i] == nullptr)
					{
						mCheck2++;
					}
					else
					{
						mIcePillar[i]->SetType(ePillarAttack::Barrage);
					}
				}
				mCheck3++;
			}


			mMove += 0.1f;
			for (int i = 0;i < 4;i++)
			{
				if (mIcePillar[i] == nullptr)
					continue;
				mIcePillar[i]->SetDegree((70.f * mMove + 90.f * i) + 90.f);
			}
		}
		else
		{
			for (int i = 0;i < 4;i++)
			{
				if (mIcePillar[i] == nullptr)
					continue;
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
				tr->SetPos(Math::Vector2<float>(tr->Getpos().x + 500.f * dir.x * Time::GetDeltaTime(), tr->Getpos().y + 500.f * dir.y * Time::GetDeltaTime()));
			}


			mMove += 0.1f;
			for (int i = 0;i < 4;i++)
			{
				if (mIcePillar[i] == nullptr)
					continue;
				Transform* pillartr = mIcePillar[i]->GetComponent<Transform>();
				mIcePillar[i]->SetDegree((70.f * mMove + 90.f * i) + 90.f);
			}
		}
	}

	void Niflheim::Bullet2()
	{
		SetState(eState::Idle);
		mType = eBossAttack::None;
	}

	void Niflheim::Icicle()
	{
		float checktime = GetCheckTime();
		Animator* ani = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		Transform* playertr = GetTarget()->GetComponent<Transform>();
		if (mCheck2 == 1)
		{
			SetCheckTime(checktime += Time::GetDeltaTime());
		}

		if (mCheck3 == 2)
		{
			SetState(eState::Idle);
			mType = eBossAttack::None;
			mCheck3 = 0;
			mCheck2 = 0;
			mMove = 0.f;
			return;
		}

		if (1.f < checktime && mCheck2 == 1)
		{
			mIcicleSound->Play(false);
			for (int i = 0;i < 8;i++)
			{
				Destroy(mRedZone[i]);
				mIcicle[i]->SetStop(false);
			}

			SetCheckTime(0.f);
			mCheck2 = 0;
			mCheck3++;
		}

		if (mCheck2 == 0 && mCheck3 < 2)
		{
			for (int i = 0;i < 8;i++)
			{
				Bullet* bullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
				Transform* bullettr = bullet->GetComponent<Transform>();
				Animator* bulletani = bullet->AddComponent<Animator>();
				Collider* bulletcol = bullet->AddComponent<Collider>();
				bullettr->SetPos(Math::Vector2<float>((118.f + 108.f * mCheck3) + 216.f * i, 128.f));
				bullettr->SetScale(Math::Vector2<float>(108.f, 160.f));
				bulletcol->SetScale(Math::Vector2<float>(80.f, 160.f));
				Texture* texture = Resources::Load<Texture>(L"Icicle", L"..\\Resources\\Enemy\\Boss\\Niflheim\\Attack\\Icicle\\Icicle.bmp");
				bulletani->CreateAnimation(L"Icicle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(27.f, 40.f), Math::Vector2<float>(0.f, 0.f), 10, 0.1f);
				bulletani->PlayAnimation(L"Icicle", false);
				bullet->SetDeleteTime(0.8f);
				bullet->SetSpeed(3.f);
				bullet->SetRadian(1.57f);
				mIcicle[i] = bullet;
				bullet->SetStar(true);

				GameObject* redzone = object::Instantiate<GameObject>(enums::eLayerType::UI);
				Transform* redtr = redzone->GetComponent<Transform>();
				SpriteRenderer* redsr = redzone->AddComponent<SpriteRenderer>();
				texture = Resources::Load<Texture>(L"RedZone", L"..\\Resources\\Enemy\\Boss\\Niflheim\\Attack\\DangerousArea.bmp");
				redsr->SetImg(texture);
				redtr->SetPos(Math::Vector2<float>((118.f + 108.f * mCheck3) + 216.f * i, 512.f));
				redtr->SetScale(Math::Vector2<float>(30.f,768.f));
				mRedZone[i] = redzone;
			}

			if (tr->Getpos().x < playertr->Getpos().x)
			{
				ani->PlayAnimation(L"NiflheimRightAttack", true);
			}
			else
			{
				ani->PlayAnimation(L"NiflheimLeftAttack", true);
			}

			mCheck2 = 1;
		}

		mMove += 0.1f;
		for (int i = 0;i < 4;i++)
		{
			if (mIcePillar[i] == nullptr)
				continue;
			Transform* pillartr = mIcePillar[i]->GetComponent<Transform>();
			mIcePillar[i]->SetDegree((70.f * mMove + 90.f * i) + 90.f);
			pillartr->SetPos(Math::Vector2<float>(tr->Getpos().x + 200.f * cosf((70.f * mMove + 90.f * i) * (3.14f / 180.f)), tr->Getpos().y + 200.f * sinf((70.f * mMove + 90.f * i) * (3.14f / 180.f))));
		}
	}

	void Niflheim::Spear()
	{
		Animator* ani = GetComponent<Animator>();
		Transform* tr = GetComponent<Transform>();
		Transform* playertr = GetTarget()->GetComponent<Transform>();
		bool right = rand() % 2;
		float checktime = GetCheckTime();

		if (mCheck2)
		{
			SetCheckTime(checktime += Time::GetDeltaTime());
		}

		if (1.f<checktime && mCheck2)
		{
			Destroy(mRedSpearZone);
			mSpear->SetStop(false);
			SetState(eState::Idle);
			mType = eBossAttack::None;
			SetCheckTime(3.f);
			mCheck2 = 0;
			mCheck3 = 0;
			mMove = 0.f;
			return;
		}

		if (mCheck3 == 0)
		{
			Bullet* bullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
			Transform* bullettr = bullet->GetComponent<Transform>();
			Animator* bulletani = bullet->AddComponent<Animator>();
			Collider* bulletcol = bullet->AddComponent<Collider>();
			Texture* texture = nullptr;
			bullettr->SetScale(Math::Vector2<float>(100.f, 444.f));
			bulletcol->SetScale(Math::Vector2<float>(444.f, 100.f));
			Math::Vector2<float> playerpos = playertr->Getpos();
			if (right)
			{
				texture = Resources::Load<Texture>(L"IceRightSpear", L"..\\Resources\\Enemy\\Boss\\Niflheim\\Attack\\Spear\\IceSpear.png");
				bullettr->SetPos(Math::Vector2<float>(1984.f, playertr->Getpos().y));
				texture->SetDegree(-90.f);
				bullet->SetRadian(3.14f);
				bulletani->CreateAnimation(L"IceRightSpear", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(25.f, 111.f), Math::Vector2<float>(0.f, 0.f), 13, 0.1f);
				bulletani->PlayAnimation(L"IceRightSpear", false);
			}
			else
			{
				texture = Resources::Load<Texture>(L"IceLeftSpear", L"..\\Resources\\Enemy\\Boss\\Niflheim\\Attack\\Spear\\IceSpear.png");
				bullettr->SetPos(Math::Vector2<float>(0.f, playerpos.y));
				texture->SetDegree(90.f);
				bullet->SetRadian(0.f);
				bulletani->CreateAnimation(L"IceLeftSpear", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(25.f, 111.f), Math::Vector2<float>(0.f, 0.f), 13, 0.1f);
				bulletani->PlayAnimation(L"IceLeftSpear", false);
			}
			bullet->SetDeleteTime(4.f);
			bullet->SetSpeed(10.f);
			mSpear = bullet;

			GameObject* redzone = object::Instantiate<GameObject>(enums::eLayerType::UI);
			Transform* redzonetr = redzone->GetComponent<Transform>();
			SpriteRenderer* redzonesr = redzone->AddComponent<SpriteRenderer>();
			texture = Resources::Load<Texture>(L"RedZone", L"..\\Resources\\Enemy\\Boss\\Niflheim\\Attack\\DangerousArea.bmp");
			redzonetr->SetScale(Math::Vector2<float>(1984.f, 40.f));
			redzonetr->SetPos(Math::Vector2<float>(992.f, playerpos.y));
			redzonesr->SetImg(texture);
			mRedSpearZone = redzone;

			mCheck2 = 1;
			mCheck3 = 1;
			if (tr->Getpos().x < playertr->Getpos().x)
			{
				ani->PlayAnimation(L"NiflheimRightAttack", true);
			}
			else
			{
				ani->PlayAnimation(L"NiflheimLeftAttack", true);
			}
		}

		mMove += 0.1f;
		for (int i = 0;i < 4;i++)
		{
			if (mIcePillar[i] == nullptr)
				continue;
			Transform* pillartr = mIcePillar[i]->GetComponent<Transform>();
			mIcePillar[i]->SetDegree((70.f * mMove + 90.f * i) + 90.f);
			pillartr->SetPos(Math::Vector2<float>(tr->Getpos().x + 200.f * cosf((70.f * mMove + 90.f * i) * (3.14f / 180.f)), tr->Getpos().y + 200.f * sinf((70.f * mMove + 90.f * i) * (3.14f / 180.f))));
		}
	}
}
