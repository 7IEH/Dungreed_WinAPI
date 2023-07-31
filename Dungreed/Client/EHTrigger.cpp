#include "EHTrigger.h"
#include "EHPlayer.h"
#include "EHSceneManager.h"
#include "EHCamera.h"

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
		Scene* mCurScene = SceneManager::LoadScene(mScenename);
		Camera::SetTarget(mCurScene->GetPlayer());
	}
}