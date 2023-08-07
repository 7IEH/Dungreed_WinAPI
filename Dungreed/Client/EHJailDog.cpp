#include "EHJailDog.h"
#include "EHObject.h"
#include "EHDetection.h"
#include "EHCollisionManager.h"
#include "EHWeapon.h"
#include "EHPlayer.h"
#include "EHBullet.h"
#include "EHResources.h"

namespace EH
{
    JailDog::JailDog()
        :
         mAttack(nullptr)
        ,mIsRight(true)
        ,mCheck1(0)
    {
        SetHP(40.f);
        SetDelayTime(4.f);
        SetSubDelayTime(1.3f);
        AddComponent<Rigidbody>();
        mDect = object::Instantiate<Detection>(enums::eLayerType::Detect);
        Collider* dectcol = mDect->AddComponent<Collider>();
        dectcol->SetScale(Math::Vector2<float>(500.f, 72.f));
        mBullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
        Collider* bulletcol = mBullet->AddComponent<Collider>();
        bulletcol->SetScale(Math::Vector2<float>(30, 30.f));
        mBullet->SetDelete(false);

        Collider* col = AddComponent<Collider>();
        col->SetScale(Math::Vector2<float>(80.f, 72.f));
        Animator* ani = AddComponent<Animator>();
        Texture* texture = Resources::Load<Texture>(L"SkelDogRightIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\SkelDog\\Idle\\Right\\SkelDogIdleSheet.bmp");
        ani->CreateAnimation(L"SkelDogRightIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 18.f), Math::Vector2<float>(0.f, 0.f), 5, 0.1f);
        texture = Resources::Load<Texture>(L"SkelDogLeftRun", L"..\\Resources\\Enemy\\JailField\\Skell\\SkelDog\\Run\\Left\\SkelDogRunSheet.bmp");
        ani->CreateAnimation(L"SkelDogLeftRun", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 18.f), Math::Vector2<float>(0.f, 0.f), 7, 0.1f);
        texture = Resources::Load<Texture>(L"SkelDogRightRun", L"..\\Resources\\Enemy\\JailField\\Skell\\SkelDog\\Run\\Right\\SkelDogRunSheet.bmp");
        ani->CreateAnimation(L"SkelDogRightRun", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 18.f), Math::Vector2<float>(0.f, 0.f), 7, 0.1f);
        texture = Resources::Load<Texture>(L"SkelDogRightAttack", L"..\\Resources\\Enemy\\JailField\\Skell\\SkelDog\\Attack\\Right\\SkelDogAttack.bmp");
        ani->CreateAnimation(L"SkelDogRightAttack", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 18.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
        texture = Resources::Load<Texture>(L"SkelDogLeftAttack", L"..\\Resources\\Enemy\\JailField\\Skell\\SkelDog\\Attack\\Left\\SkelDogAttack.bmp");
        ani->CreateAnimation(L"SkelDogLeftAttack", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 18.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
    }

    JailDog::~JailDog()
    {
        Destroy(mBullet);
        Destroy(mDect);
    }

    void JailDog::Initialize()
    {
    }

    void JailDog::Update()
    {
        GameObject::Update();
        switch (GetState())
        {
        case EH::Enemy::eState::Idle:
            Idle();
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
        Transform* decttr = mDect->GetComponent<Transform>();
        Transform* bullettr = mBullet->GetComponent<Transform>();
        Transform* tr = GetComponent<Transform>();

        decttr->SetPos(tr->Getpos());
        if (mIsRight)
        {
            bullettr->SetPos(Math::Vector2<float>(tr->Getpos().x + 25.f,tr->Getpos().y));
        }
        else
        {
            bullettr->SetPos(Math::Vector2<float>(tr->Getpos().x - 25.f, tr->Getpos().y));
        }
    }

    void JailDog::Render(HDC hdc)
    {
        GameObject::Render(hdc);
    }

    void JailDog::OnCollisionEnter(Collider* other)
    {
        // 플레이어 오브젝트 충돌
        Weapon* weapon = dynamic_cast<Weapon*>(other->GetOwner());
        if (weapon != nullptr)
        {
            UINT hp = GetHP();
            SetHP(hp -= 20);
            mAttack = weapon;
        }
    }

    void JailDog::OnCollisionStay(Collider* other)
    {
    }

    void JailDog::OnCollisionExit(Collider* other)
    {
    }

    void JailDog::Idle()
    {
        if (GetHP() <= 0.f)
        {
            SetState(eState::Dead);
        }

        if (GetTarget() != nullptr)
        {
            // 공격부분off
            mDect->GetComponent<Collider>()->enabled(false);
            mBullet->GetComponent<Collider>()->enabled(false);
            Transform* tr = GetComponent<Transform>();
            Transform* playertr = GetTarget()->GetComponent<Transform>();

            Math::Vector2<float> pos = tr->Getpos();
            Math::Vector2<float> playerpos = playertr->Getpos();

            Animator* ani = GetComponent<Animator>();

            float thinktime = GetCheckTime();
            SetCheckTime(thinktime += Time::GetDeltaTime());
            if (GetDelayTime()<thinktime)
            {
                if (mIsRight)
                {
                    ani->PlayAnimation(L"SkelDogRightAttack", true);
                }
                else
                {
                    ani->PlayAnimation(L"SkelDogLeftAttack", true);
                }
                SetState(eState::Attack);
                SetCheckTime(0.f);
            }
            else
            {
                Rigidbody* rigid = GetComponent<Rigidbody>();
                float diff = playerpos.x - pos.x + 10.f;
                // patrol
                if (tr->Getpos().x < playertr->Getpos().x)
                {
                    ani->PlayAnimation(L"SkelDogRightRun",true);
                    rigid->AddForce(Math::Vector2<float>(350.f, 0.f));
                    mIsRight = true;
                }
                else
                {
                    ani->PlayAnimation(L"SkelDogLeftRun", true);
                    rigid->AddForce(Math::Vector2<float>(-350.f, 0.f));
                    mIsRight = false;
                }
            }
        }
        else
        {
            SetTarget(mDect->passthetarget());
        }
    }

    void JailDog::Attack()
    {
        if (GetHP() <= 0.f)
        {
            SetState(eState::Dead);
        }

        float chargetime = GetSubCheckTime();
        SetSubCheckTime(chargetime += Time::GetDeltaTime());
        mBullet->GetComponent<Collider>()->enabled(true);
        Rigidbody* rigid = GetComponent<Rigidbody>();

        if (mCheck1 == 0)
        {
            if (mIsRight)
            {
                rigid->SetGround(false);
                rigid->SetVeclocity(Math::Vector2<float>(300.f, -500.f));
            }
            else
            {
                rigid->SetGround(false);
                rigid->SetVeclocity(Math::Vector2<float>(-300.f, -500.f));
            }
            mCheck1++;
        }

        if (GetSubDelayTime() < chargetime)
        {
            SetState(eState::Idle);
            SetSubCheckTime(0.f);
            mCheck1 = 0;
        }
    }

    void JailDog::Dead()
    {
        CollisionManager::ForceExit(GetComponent<Collider>(), mAttack->GetComponent<Collider>());
        Destroy(this);
    }
}