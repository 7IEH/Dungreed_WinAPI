#include "EHLayer.h"

namespace EH
{
	Layer::Layer()
		:
		mGameObjects{}
	{
	}

	Layer::~Layer()
	{
		for (GameObject* obj : mGameObjects)
		{
			delete obj;
			obj = nullptr;
		}
	}

	void Layer::Initialize()
	{
	}

	void Layer::Update()
	{
		for (GameObject* obj : mGameObjects)
		{
			obj->Update();
		}
	}

	void Layer::Render(HDC hdc)
	{
		for (GameObject* obj : mGameObjects)
		{
			obj->Render(hdc);
		}

		std::vector<GameObject*>::iterator iter = mGameObjects.begin();

		for (;iter != mGameObjects.end();)
		{
			if ((*iter)->GetState() == GameObject::eState::Dead)
			{
				GameObject* deadObj = *iter;
				delete deadObj;
				deadObj = nullptr;
				iter = mGameObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}
}