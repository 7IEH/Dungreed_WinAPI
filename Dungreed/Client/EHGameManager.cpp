#include "EHGameManager.h"
#include "EHCanvas.h"
#include "EHObject.h"

namespace EH
{
	Canvas* GameManager::mPlayerUI = nullptr;

	void GameManager::Initialize()
	{
		Canvas* canvas = object::Instantiate<Canvas>(enums::eLayerType::UI);
		mPlayerUI = canvas;
	}

	void GameManager::Update()
	{
		mPlayerUI->Update();
	}

	void GameManager::Render(HDC hdc)
	{
		mPlayerUI->Render(hdc);
	}
}