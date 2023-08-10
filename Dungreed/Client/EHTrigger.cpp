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
		, mSetKey(eKeyCode::END)
	{
		mDungeoneat = Resources::Load<Sound>(L"Dungeonout", L"..\\Resources\\Sound\\Structure\\DungeonOut.wav");
		mOpend = Resources::Load<Sound>(L"opend", L"..\\Resources\\Sound\\Item\\Chest2.wav");
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
		case EH::Trigger::eTriggertype::Tresure:
			break;
		case EH::Trigger::eTriggertype::None:
			break;
		default:
			break;
		}
	}

	void Trigger::OnCollisionStay(Collider* other)
	{
		
		if (mType == eTriggertype::Tresure)
		{
			if (Input::Getkey(eKeyCode::G).state == eKeyState::DOWN)
			{
				mOpend->Play(false);
				GetComponent<Animator>()->PlayAnimation(L"OpenTresure", false);
			}
		}

		if (mType == eTriggertype::Scenechange)
		{
			if (SceneManager::GetCurScene()->GetLayer(enums::eLayerType::Enemy).GetObjects().size() == 0)
			{

				if (mSetKey != eKeyCode::END)
				{
					if (Input::Getkey(mSetKey).state == eKeyState::DOWN)
					{
						if (SceneManager::GetCurScene()->GetBGM() != nullptr)
							SceneManager::GetCurScene()->GetBGM()->Stop(true);

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

			if (mScenename == L"JailScene1" && SceneManager::GetCurScene()->GetName() == L"TownScene")
			{
				mCheckTime += Time::GetDeltaTime();

				if (mDelayTime / 4.f < mCheckTime && mCheck1 == 0)
				{
					SceneManager::GetCurScene()->GetPlayer()->GetComponent<Animator>()->PlayAnimation(L"Trans", false);
					SceneManager::GetCurScene()->GetPlayer()->SetTrans(true);

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
		else if (mSetKey != eKeyCode::END)
		{
			return;
		}
		else
		{
			SceneManager::GetCurScene()->GetPlayer()->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
			SceneManager::GetCurScene()->GetPlayer()->SetState(eAnimationState::Idle);

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

	void Trigger::Tresure()
	{
		return;
	}
}