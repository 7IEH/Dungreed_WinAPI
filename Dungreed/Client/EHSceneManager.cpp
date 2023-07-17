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

namespace EH
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mCurScene = nullptr;

	void SceneManager::Initialize()
	{
		// scene ����� ó�� �Ұ� load
		CreateScene<TitleScene>(L"TitleScene");
		CreateScene<SelectScene>(L"SelectScene");
		CreateScene<TownScene>(L"TownScene");
		CreateScene<JailScene18>(L"JailScene18");
		CreateScene<JailPrevBossScene>(L"JailPrevBossScene");
		CreateScene<JailBossScene>(L"JailBossScene");
		CreateScene<JailScene1>(L"JailScene1");
		CreateScene<JailScene2>(L"JailScene2");
		CreateScene<JailScene3>(L"JailScene3");
		CreateScene<JailScene4>(L"JailScene4");

		LoadScene(L"TitleScene");
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