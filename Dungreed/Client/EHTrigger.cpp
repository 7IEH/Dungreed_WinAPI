#include "EHTrigger.h"
#include "EHPlayer.h"
#include "EHSceneManager.h"
#include "EHCamera.h"
#include "EHDungeonManager.h"
#include "EHResources.h"

namespace EH
{
	Trigger::Trigger()
		:
		  mType(eTriggertype::None)
		, mScenename(L"")
		, mCheckTime(0.f)
		, mDelayTime(0.f)
		, mCheck1(0)
	{
		mDungeoneat = Resources::Load<Sound>(L"Dungeonout", L"..\\Resources\\Sound\\Structure\\DungeonOut.wav");
	}

	Trigger::~Trigger()
	{
	}

	void Trigger::Initialize()
	{
	}

	void Trigger::Update()
	{
		GameObject::Update();
		if (mScenename == L"JailScene1")
		{
			mDelayTime = 4.f;
		}
		else
		{
			mDelayTime = 0.f;
		}
	}

	void Trigger::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Trigger::OnCollisionEnter(Collider* other)
	{
		switch (mType)
		{
		case EH::Trigger::eTriggertype::Scenechange:
			SceneChange();
			break;
		case EH::Trigger::eTriggertype::None:
			break;
		default:
			break;
		}
	}

	void Trigger::OnCollisionStay(Collider* other)
	{
		if (mScenename == L"JailScene1" && SceneManager::GetCurScene()->GetName() == L"TownScene")
		{
			mCheckTime += Time::GetDeltaTime();

			if (mDelayTime / 2.f < mCheckTime && mCheck1 == 0)
			{
				SceneManager::GetCurScene()->GetPlayer()->GetComponent<Animator>()->SetActiveAnimation(nullptr, false);
				mCheck1++;
			}

			if (mDelayTime < mCheckTime)
			{
				Scene* mCurScene = SceneManager::LoadScene(mScenename);
				if (mCurScene != nullptr)
				{
					if (mCurScene->GetBGM() != nullptr)
						mCurScene->GetBGM()->Play(true);

					if (mCurScene->GetPlayer() != nullptr)
						Camera::SetTarget(mCurScene->GetPlayer());
				}
				mCheckTime = 0.f;
				mCheck1 = 0;
			}
			else
			{
				Player* player = dynamic_cast<Player*>(other->GetOwner());
				Transform* playertr = player->GetComponent<Transform>();
				Transform* duntr = mDungeoneater->GetComponent<Transform>();
				Animator* ani = mDungeoneater->GetComponent<Animator>();
				duntr->SetPos(Math::Vector2<float>(playertr->Getpos().x, 1127.f));
				ani->PlayAnimation(L"Dungeoneat", false);
			}
		}
	}

	void Trigger::OnCollisionExit(Collider* other)
	{
	}

	void Trigger::SceneChange()
	{
		if (SceneManager::GetCurScene()->GetBGM() != nullptr)
			SceneManager::GetCurScene()->GetBGM()->Stop(true);

		if (mScenename == L"JailScene1" && SceneManager::GetCurScene()->GetName() == L"TownScene")
		{
			mDungeoneat->Play(false);
			return;
		}
		else
		{
			Scene* mCurScene = SceneManager::LoadScene(mScenename);
			if (mCurScene != nullptr)
			{
				if (mCurScene->GetBGM() != nullptr)
					mCurScene->GetBGM()->Play(true);

				if (mCurScene->GetPlayer() != nullptr)
					Camera::SetTarget(mCurScene->GetPlayer());
			}
		}
	}
}