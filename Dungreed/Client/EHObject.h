#pragma once
#include "Commoninclude.h"
#include "EHSceneManager.h"

namespace EH::object
{
	template <typename T>
	T* Instantiate(enums::eLayerType type)
	{
		T* obj = new T();
		Scene* curscene = SceneManager::GetCurScene();
		curscene->SetLayer(type, obj);

		return obj;
	}
}