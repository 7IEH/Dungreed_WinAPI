#pragma once
#include "Commoninclude.h"
#include "EHComponent.h"
#include "EHGameObject.h"
#include "EHTransform.h"
#include "EHPath.h"

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

		void SetSrcPos(Math::Vector2<float> srcpos) { mSrcPos = srcpos; }
		void SetSrcScale(Math::Vector2<float> srcscale) { mSrcScale = srcscale; }

		void AddImg(const std::wstring& path, const std::wstring& name);

		void SetImg(const std::wstring& name);

	private:
		Math::Vector2<float> mSrcPos;
		Math::Vector2<float> mSrcScale;

		// test
		Gdiplus::Image* mCurImg;
		std::map<std::wstring, Gdiplus::Image*> mImg;
	};
}
