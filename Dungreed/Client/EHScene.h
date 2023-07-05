#pragma once
#include "Commoninclude.h"
#include "EHEntity.h"
#include "EHLayer.h"

namespace EH
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void SetLayer(enums::eLayerType type, GameObject* obj)
		{
			mLayers[(UINT)type].SetObject(obj);
		}

	private:
		std::vector<Layer> mLayers;
	};
}
