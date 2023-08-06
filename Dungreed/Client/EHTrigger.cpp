#include "EHTrigger.h"
#include "EHPlayer.h"
#include "EHSceneManager.h"
#include "EHCamera.h"
#include "EHDungeonManager.h"

namespace EH
{
	Trigger::Trigger()
		:
		mType(eTriggertype::None)
		, mScenename(L"")
	{
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
	}

	void Trigger::OnCollisionExit(Collider* other)
	{
	}

	void Trigger::SceneChange()
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