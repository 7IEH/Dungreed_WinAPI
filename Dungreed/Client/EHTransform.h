#pragma once
#include "Commoninclude.h"
#include "EHComponent.h"
#include "EHTime.h"
#include "EHInput.h"

namespace EH
{
	class Transform : public Component
	{
	public:
		Transform();
		virtual ~Transform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetPos(Math::Vector2<float> pos) { mPos = pos; }
		Math::Vector2<float> Getpos() { return mPos; }

		void SetScale(Math::Vector2<float> scale) { mScale = scale; }
		Math::Vector2<float> GetScale() { return mScale; }

	private:
		EH::Math::Vector2<float> mPos;
		EH::Math::Vector2<float> mScale;
	};
}
