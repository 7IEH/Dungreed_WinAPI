#pragma once
#include "Commoninclude.h"
#include "EHEntity.h"
#include "EHLayer.h"
#include "EHSound.h"

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

		Math::Vector2<float> GetSize() { return mSceneSize; }
		void SetSize(Math::Vector2<float> scenesize) { mSceneSize = scenesize; }

		void SetLayer(enums::eLayerType type, GameObject* obj)
		{
			mLayers[(UINT)type].SetObject(obj);
		}

		Layer& GetLayer(enums::eLayerType type) { return mLayers[(UINT)type]; }

		void SetBGM(Sound* bgm) { mBGM = bgm; }
		Sound* GetBGM() { return mBGM; }

	private:
		std::vector<Layer> mLayers;
		Math::Vector2<float> mSceneSize;
		Sound* mBGM;
	};
}
