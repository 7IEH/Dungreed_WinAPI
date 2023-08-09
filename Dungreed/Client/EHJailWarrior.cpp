#include "EHJailWarrior.h"
#include "EHDetection.h"
#include "EHObject.h"
#include "EHPlayer.h"
#include "EHWeapon.h"
#include "EHCollisionManager.h"
#include "EHResources.h"
#include "EHBullet.h"

namespace EH
{
    JailWarrior::JailWarrior()
        :
          mAttack(nullptr)
        , mIsRight(true)
    {
        Rigidbody* rigid = AddComponent<Rigidbody>();
        SetHP(40.f);
        SetDelayTime(4.f);
        mDect = object::Instantiate<Detection>(enums::eLayerType::Detect);
        Collider* dectcol = mDect->AddComponent<Collider>();
        dectcol->SetScale(Math::Vector2<float>(500.f, 16.f));
        Animator* ani = AddComponent<Animator>();
        Texture* texture = Resources::Load<Texture>(L"GreySkelRightIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Right\\GraySkelIdle.bmp");
        ani->CreateAnimation(L"GreySkelRightIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);

        texture = Resources::Load<Texture>(L"GreySkelLeftIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Idle\\Left\\GraySkelIdle.bmp");
        ani->CreateAnimation(L"GreySkelLeftIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);

        texture = Resources::Load<Texture>(L"GreySkelRightWalk", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Walk\\Right\\GreySkelWalk.bmp");
        ani->CreateAnimation(L"GreySkelRightWalk", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
        texture = Resources::Load<Texture>(L"GreySkelLeftWalk", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Walk\\Left\\GreySkelWalk.bmp");
        ani->CreateAnimation(L"GreySkelLeftWalk", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);

        // Weapon
        mSword = object::Instantiate<Weapon>(enums::eLayerType::Sword);
        mSword->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
        Animator* swordani = mSword->AddComponent<Animator>();
        texture = Resources::Load<Texture>(L"RustySwordLeftIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Warrior\\Idle\\Left\\RustyShortSword00.bmp");
        swordani->CreateAnimation(L"RustySwordLeftIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);
        texture = Resources::Load<Texture>(L"RustySwordRightIdle", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Warrior\\Idle\\Right\\RustyShortSword00.bmp");
        swordani->CreateAnimation(L"RustySwordRightIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 1, 0.1f);

        texture = Resources::Load<Texture>(L"RustySwordLeftAttack", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Warrior\\Attack\\Left\\RustySwordAttack.bmp");
        swordani->CreateAnimation(L"RustySwordLeftAttack", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 12, 0.1f);

        texture = Resources::Load<Texture>(L"RustySwordRightAttack", L"..\\Resources\\Enemy\\JailField\\Skell\\GreySkel\\Warrior\\Attack\\Right\\RustySwordAttack.bmp");
        swordani->CreateAnimation(L"RustySwordRightAttack", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 12, 0.1f);

        // Weapon Col
        mBullet = object::Instantiate<Bullet>(enums::eLayerType::Bullet);
        Collider* bulletcol = mBullet->AddComponent<Collider>();
        bulletcol->SetScale(Math::Vector2<float>(100.f, 100.f));
        bulletcol->SetType(Collider::eColliderType::Circle);
        mBullet->SetDelete(false);
    }

    JailWarrior::~JailWarrior()
    {
        Destroy(mDect);
        Destroy(mSword);
        Destroy(mBullet);
    }

    void JailWarrior::Initialize()
    {
    }

    void JailWarrior::Update()
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

        Transform* tr = GetComponent<Transform>();
        mDect->GetComponent<Transform>()->SetPos(tr->Getpos());
    }

    void JailWarrior::Render(HDC hdc)
    {
        GameObject::Render(hdc);
    }

    void JailWarrior::OnCollisionEnter(Collider* other)
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

    void JailWarrior::OnCollisionStay(Collider* other)
    {
    }

    void JailWarrior::OnCollisionExit(Collider* other)
    {
    }

    void JailWarrior::Idle()
    {
        if (GetHP() <= 0.f)
        {
            SetState(eState::Dead);
        }

        // Sword
        Transform* swordtr = mSword->GetComponent<Transform>();
        Transform* tr = GetComponent<Transform>();
        Transform* bullettr = mBullet->GetComponent<Transform>();

        Animator* swordani = mSword->GetComponent<Animator>();

        if (mIsRight)
        {
            bullettr->SetPos(Math::Vector2<float>(tr->Getpos().x + 50.f, tr->Getpos().y + 30.f));
            swordtr->SetPos(Math::Vector2<float>(tr->Getpos().x + 50.f, tr->Getpos().y + 30.f));
            swordani->PlayAnimation(L"RustySwordRightIdle", true);
        }
        else
        {
            bullettr->SetPos(Math::Vector2<float>(tr->Getpos().x - 50.f, tr->Getpos().y + 30.f));
            swordtr->SetPos(Math::Vector2<float>(tr->Getpos().x - 50.f, tr->Getpos().y + 30.f));
            swordani->PlayAnimation(L"RustySwordLeftIdle", true);
        }


        if (GetTarget() != nullptr)
        {
            // 공격 부분 off
            Collider* bulletcol = mBullet->GetComponent<Collider>();
            bulletcol->enabled(false);

            mDect->GetComponent<Collider>()->enabled(false);
            Transform* tr = GetComponent<Transform>();
            Transform* playertr = GetTarget()->GetComponent<Transform>();

            Math::Vector2<float> pos = tr->Getpos();
            Math::Vector2<float> playerpos = playertr->Getpos();
            Animator* ani = GetComponent<Animator>();

            //
            if (fabs(pos.x-playerpos.x)<35.f)
            {
                if (mIsRight)
                {
                    swordani->PlayAnimation(L"RustySwordRightAttack", false);
                    ani->PlayAnimation(L"GreySkelRightIdle", false);
                }
                else
                {
                    swordani->PlayAnimation(L"RustySwordLeftAttack", false);
                    ani->PlayAnimation(L"GreySkelLeftIdle", false);
                }
                SetState(eState::Attack);
            }
            else
            {
                Rigidbody* rigid = GetComponent<Rigidbody>();
                if (playerpos.x < pos.x)
                {
                    // Left run
                    rigid->AddForce(Math::Vector2<float>(-200.f, 0.f));
                    ani->PlayAnimation(L"GreySkelLeftWalk", true);
                    
                    tr->SetPos(pos);
                    mIsRight = false;
                }
                else
                {
                    // Right run
                    ani->PlayAnimation(L"GreySkelRightWalk", true);
                    rigid->AddForce(Math::Vector2<float>(200.f, 0.f));
                    tr->SetPos(pos);
                    mIsRight = true;
                }
            }
        }
        else
        {
            SetTarget(mDect->passthetarget());
        }
    }

    void JailWarrior::Attack()
    {

        Rigidbody* rigid = GetComponent<Rigidbody>();
        rigid->SetVeclocity(Math::Vector2<float>(0.f, 0.f));
        if (GetHP() <= 0.f)
        {
            SetState(eState::Dead);
        }
        float chargetime = GetCheckTime();
        SetCheckTime(chargetime += Time::GetDeltaTime());
        // 공격 부분 on
        Collider* bulletcol = mBullet->GetComponent<Collider>();
        bulletcol->enabled(true);

       

        if (GetDelayTime()<chargetime)
        {
            SetState(eState::Idle);
            SetCheckTime(0.f);
        }
    }

    void JailWarrior::Dead()
    {
        CollisionManager::ForceExit(GetComponent<Collider>(), mAttack->GetComponent<Collider>());
        Destroy(this);
    }
}