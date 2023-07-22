#pragma once
#include "Commoninclude.h"
#include "EHComponent.h"
#include "EHGameObject.h"
#include "EHTransform.h"
#include "EHPath.h"
#include "EHTexture.h"

namespace EH
{
	class SpriteRenderer : public Component
	{
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		void SetImg(Texture* texture) { mTexture = texture; }
		Texture* GetImg() { return mTexture; }

		void SetAffectCamera(bool affectcamera) { mAffectCamera = affectcamera; }

		float GetAlpha() { return mAlpha; }
		void SetAlpha(float alpha) { mAlpha = alpha; }

	private:
		Texture* mTexture;
		bool mAffectCamera;
		float mAlpha;
	};
}

