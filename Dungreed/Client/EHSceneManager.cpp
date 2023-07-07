#include "EHSceneManager.h"
#include "EHTitleScene.h"
#include "EHSelectScene.h"
#include "EHTownScene.h"

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