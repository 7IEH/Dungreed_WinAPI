#include "EHSceneManager.h"
#include "EHTitleScene.h"
#include "EHSelectScene.h"
#include "EHTownScene.h"
#include "EHJailScene18.h"
#include "EHJailPrevBossScene.h"
#include "EHJailBossScene.h"
#include "EHJailScene1.h"
#include "EHJailScene2.h"
#include "EHJailScene3.h"
#include "EHJailScene4.h"
#include "EHJailField5.h"
#include "EHJailField6.h"
#include "EHJailField7.h"
#include "EHJailField8.h"
#include "EHJailScene9.h"
#include "EHJailScene10.h"
#include "EHJailScene11.h"
#include "EHJailScene12.h"
#include "EHJailScene13.h"
#include "EHJailScene14.h"
#include "EHJailScene15.h"
#include "EHJailScene16.h"
#include "EHJailScene17.h"

namespace EH
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mCurScene = nullptr;

	void SceneManager::Initialize()
	{
		// scene 만들고 처음 할거 load
		CreateScene<TitleScene>(L"TitleScene");
		// CreateScene<SelectScene>(L"SelectScene");
		CreateScene<TownScene>(L"TownScene");
		CreateScene<JailPrevBossScene>(L"JailPrevBossScene");
		CreateScene<JailBossScene>(L"JailBossScene");
		CreateScene<JailScene1>(L"JailScene1");
		CreateScene<JailScene2>(L"JailScene2");
		CreateScene<JailScene3>(L"JailScene3");
		CreateScene<JailScene4>(L"JailScene4");
		CreateScene<JailField5>(L"JailScene5");
		CreateScene<JailField6>(L"JailScene6");
		CreateScene<JailField7>(L"JailScene7");
		CreateScene<JailField8>(L"JailScene8");
		CreateScene<JailScene9>(L"JailScene9");
		CreateScene<JailScene10>(L"JailScene10");
		CreateScene<JailScene11>(L"JailScene11");
		CreateScene<JailScene12>(L"JailScene12");
		CreateScene<JailScene13>(L"JailScene13");
		CreateScene<JailScene14>(L"JailScene14");
		CreateScene<JailScene15>(L"JailScene15");
		CreateScene<JailScene16>(L"JailScene16");
		CreateScene<JailScene17>(L"JailScene17");
		CreateScene<JailScene18>(L"JailScene18");

		LoadScene(L"JailScene1");
	}

	void SceneManager::Release()
	{
		for (auto iter : mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	void SceneManager::Update()
	{
		mCurScene->Update();
	}

	void SceneManager::Render(HDC hdc)
	{
		mCurScene->Render(hdc);
	}

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		std::map<std::wstring, Scene*>::iterator iter = mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;

		mCurScene = iter->second;
		return iter->second;
	}
}