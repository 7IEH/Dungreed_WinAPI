#include "EHSceneManager.h"
#include "SceneHeader.h"


namespace EH
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mCurScene = nullptr;

	void SceneManager::Initialize()
	{
		CreateScene<TitleScene>(L"TitleScene");
		// CreateScene<SelectScene>(L"SelectScene");

		CreateScene<TownScene>(L"TownScene");
		CreateScene<JailPrevBossScene>(L"JailPrevBossScene");
		CreateScene<JailAfterBossScene>(L"JailAfterBossScene");
		// JailScene
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

		// ICE
		CreateScene<IceScene1>(L"IceScene1");
		CreateScene<IceScene2>(L"IceScene2");
		CreateScene<IceScene3>(L"IceScene3");
		CreateScene<IceScene4>(L"IceScene4");
		CreateScene<IceScene5>(L"IceScene5");
		CreateScene<IceScene6>(L"IceScene6");
		CreateScene<IceScene7>(L"IceScene7");
		CreateScene<IceScene8>(L"IceScene8");
		CreateScene<IceScene9>(L"IceScene9");
		CreateScene<IceScene10>(L"IceScene10");
		CreateScene<IceScene11>(L"IceScene11");
		CreateScene<IceScene12>(L"IceScene12");
		CreateScene<IceScene13>(L"IceScene13");
		CreateScene<IceScene14>(L"IceScene14");
		CreateScene<IceScene15>(L"IceScene15");
		CreateScene<IceScene16>(L"IceScene16");
		CreateScene<IceScene17>(L"IceScene17");
		CreateScene<IceScene18>(L"IceScene18");
		CreateScene<IceScene19>(L"IceScene19");
		CreateScene<IcePrevBossScene>(L"IcePrevBossScene");
		CreateScene<IceBossScene>(L"IceBossScene");

		CreateScene<EndingScene>(L"EndingScene");

		LoadScene(L"IceScene5");
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