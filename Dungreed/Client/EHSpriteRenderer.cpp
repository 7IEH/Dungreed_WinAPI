#include "EHSpriteRenderer.h"
#include "EHSceneManager.h"
#include "EHCamera.h"

namespace EH
{
	SpriteRenderer::SpriteRenderer()
		:
		Component(enums::eComponentType::SpriteRenderer)
		, mTexture(nullptr)
		, mAffectCamera(true)
		, mAlpha(1.f)
	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::Initialize()
	{
	}

	void SpriteRenderer::Update()
	{
	}

	void SpriteRenderer::Render(HDC hdc)
	{
		Transform* tf = GetOwner()->GetComponent<Transform>();
		Math::Vector2<float> pos = tf->Getpos();
		Math::Vector2<float> scale = tf->GetScale();

		if(mAffectCamera)
			pos = Camera::CaculatePos(pos);

		if (mTexture == nullptr)
		{
			Rectangle(hdc, pos.x - scale.x/2.f, pos.y - scale.x / 2.f, pos.x + scale.x, pos.y + scale.y);
		}
		else if (mTexture->GetType() == eTextureType::Bmp)
		{
			if (mAlpha < 1.0f)
			{
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				func.SourceConstantAlpha = 255;

				AlphaBlend(hdc, 
					pos.x-scale.x/2.f, pos.y-scale.y/2.f,
					scale.x, scale.y,
					mTexture->GetHDC(),
					mTexture->GetPos().x, mTexture->GetPos().y,
					mTexture->GetWidth(), mTexture->GetHeight(),
					func);
			}
			else
			{
				TransparentBlt(hdc,
					pos.x- scale.x/2.f, pos.y - scale.y/2.f,
					scale.x, scale.y,
					mTexture->GetHDC(),
					mTexture->GetPos().x, mTexture->GetPos().y,
					mTexture->GetWidth(), mTexture->GetHeight(),
					RGB(255, 0, 255));
			}
		}
		else if (mTexture->GetType() == eTextureType::Png)
		{
			Gdiplus::ImageAttributes imageAtt = {};

			if(mTexture->GetName()==L"TownBackGround" || mTexture->GetName() == L"TownBG" || mTexture->GetName() == L"TownLayer")
				imageAtt.SetColorKey(Gdiplus::Color(0, 255, 255,255), Gdiplus::Color(0, 255, 255, 255));

			::Graphics g(hdc);
			g.SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
			g.DrawImage(mTexture->GetImage(),
				Rect(pos.x - scale.x/2.f, pos.y - scale.y/2.f, scale.x, scale.y),
				mTexture->GetPos().x, mTexture->GetPos().y,
				mTexture->GetWidth(), mTexture->GetHeight(),
				Gdiplus::UnitPixel,
				&imageAtt);
		}		
	}
}