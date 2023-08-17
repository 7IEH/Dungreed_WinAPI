#include "EHDungeonManager.h"
#include "EHSceneManager.h"
#include "EHTime.h"
#include "EHResources.h"

namespace EH
{
	std::map<std::wstring, bool> DungeonManager::mClear = {};
	float DungeonManager::mSubCheckTime = 0.f;
	float DungeonManager::mDelayTime = 1.5f;
	UINT DungeonManager::Check1 = 0;

	void DungeonManager::Initialize()
	{
		mClear.insert(std::make_pair(L"JailScene1", false));
		mClear.insert(std::make_pair(L"JailScene2", false));
		mClear.insert(std::make_pair(L"JailScene3", false));
		mClear.insert(std::make_pair(L"JailScene4", false));
		mClear.insert(std::make_pair(L"JailScene5", false));
		mClear.insert(std::make_pair(L"JailScene6", false));
		mClear.insert(std::make_pair(L"JailScene7", false));
		mClear.insert(std::make_pair(L"JailScene8", false));
		mClear.insert(std::make_pair(L"JailScene9", false));
		mClear.insert(std::make_pair(L"JailScene10", false));
		mClear.insert(std::make_pair(L"JailScene11", false));
		mClear.insert(std::make_pair(L"JailScene12", false));
		mClear.insert(std::make_pair(L"JailScene13", false));
		mClear.insert(std::make_pair(L"JailScene14", false));
		mClear.insert(std::make_pair(L"JailScene15", false));
		mClear.insert(std::make_pair(L"JailScene16", false));
		mClear.insert(std::make_pair(L"JailScene17", false));
		mClear.insert(std::make_pair(L"JailScene18", false));
		mClear.insert(std::make_pair(L"JailBossScene", false));
		mClear.insert(std::make_pair(L"IceScene2", false));
		mClear.insert(std::make_pair(L"IceScene3", false));
		mClear.insert(std::make_pair(L"IceScene4", false));
		mClear.insert(std::make_pair(L"IceScene5", false));
		mClear.insert(std::make_pair(L"IceScene6", false));
		mClear.insert(std::make_pair(L"IceScene7", false));
		mClear.insert(std::make_pair(L"IceScene8", false));
		mClear.insert(std::make_pair(L"IceBossScene", false));
	}

	void DungeonManager::Update()
	{
		Scene* curscene = SceneManager::GetCurScene();
		std::map<std::wstring, bool>::iterator iter = mClear.find(curscene->GetName());

		if (iter != mClear.end())
		{
			// not clear
			if (!(iter->second))
			{
				// 검사했을때 enemy 없을경우
				if (curscene->GetLayer(enums::eLayerType::Enemy).GetObjects().size() == 0)
				{
					iter->second = true;
					mSubCheckTime = 0.f;
					for (GameObject* obj : curscene->GetLayer(enums::eLayerType::Steel).GetObjects())
					{
						Sound* sound = Resources::Load<Sound>(L"SteelDoor", L"..\\Resources\\Sound\\Structure\\stoneDoor.wav");
						sound->Play(false);
						obj->GetComponent<Animator>()->PlayAnimation(L"SteelExit", false);
						obj->GetComponent<Collider>()->enabled(false);
					}
				}
				else
				{
					mSubCheckTime += Time::GetDeltaTime();
					for (GameObject* obj : curscene->GetLayer(enums::eLayerType::Steel).GetObjects())
					{
						if (mDelayTime < mSubCheckTime)
						{
							obj->GetComponent<Animator>()->PlayAnimation(L"SteelIdle", true);
							Check1 = 0;
						}
						else
						{
							obj->GetComponent<Animator>()->PlayAnimation(L"SteelOpen", false);
							if (Check1 == 0)
							{
								Check1++;
								Sound* sound = Resources::Load<Sound>(L"SteelDoor", L"..\\Resources\\Sound\\Structure\\stoneDoor.wav");
								sound->Play(false);
							}
						}
					}
				}
			}
			else
			{
				mSubCheckTime = 0.f;
				for (GameObject* obj : curscene->GetLayer(enums::eLayerType::Steel).GetObjects())
				{
					obj->GetComponent<Collider>()->enabled(false);
				}
			}
		}
	}
}