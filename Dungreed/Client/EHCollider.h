#pragma once
#include "EHComponent.h"

namespace EH
{
	class Collider : public Component
	{
	public:
		Collider();
		virtual ~Collider();
		
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void SetScale(Math::Vector2<float> scale) { mScale = scale; }
		void SetOffset(Math::Vector2<float> scale) { mOffset = scale; }

		Math::Vector2<float> GetScale() { return mScale; }
		Math::Vector2<float> GetOffset() { return mOffset; }

	private:
		Math::Vector2<float> mScale;
		Math::Vector2<float> mOffset;
	};
}
