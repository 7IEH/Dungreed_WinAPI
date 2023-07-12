#include "EHJailScene.h"
#include "EHSceneManager.h"

namespace EH
{
	JailScene::JailScene()
	{
	}

	JailScene::~JailScene()
	{
	}

	void JailScene::Initialize()
	{
	}

	void JailScene::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			SceneManager::LoadScene(L"JailPrevBossScene");
		}
		Scene::Update();
	}

	void JailScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene", 10);
	}

}