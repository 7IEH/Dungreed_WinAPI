#pragma once
#include "Commoninclude.h"
#include "EHGameObject.h"

namespace EH
{
	class Camera
	{
	public:
		static void Initialize();
		static void Update();

		static void SetTarget(GameObject* target) { mTarget = target; }
		static Math::Vector2<float> CaculatePos(Math::Vector2<float> pos) { return pos - mDiffDistance; }
		static void SetLookAt(Math::Vector2<float> lookat) { mLookAt = lookat; }
		static Math::Vector2<float> GetLookAt() { return mLookAt; }

	private:
		static Math::Vector2<float> mResolution;
		static Math::Vector2<float> mLookAt;
		static Math::Vector2<float> mDiffDistance;
		static GameObject* mTarget;

	};
}

