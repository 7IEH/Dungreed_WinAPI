#pragma once
#include "Commoninclude.h"
#include "EHEntity.h"
#include "EHGameObject.h"

namespace EH
{
	class Layer : Entity
	{
	public:
		Layer();
		virtual ~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void SetObject(GameObject* obj)
		{
			mGameObjects.push_back(obj);
		}

	private:
		std::vector<GameObject*> mGameObjects;
	};
}
