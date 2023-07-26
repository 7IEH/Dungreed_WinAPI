#include "EHScene.h"
namespace EH
{
	Scene::Scene()
		:
		 mSceneSize(0.f, 0.f)
	{
		mLayers.resize((UINT)enums::eLayerType::End);
	}

	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
	}

	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (Layer& layer : mLayers)
		{
			layer.Render(hdc);
		}
	}
}