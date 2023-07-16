#include "EHAnimation.h"
#include "EHAnimator.h"
#include "EHTime.h"
#include "EHTransform.h"
#include "EHGameObject.h"
#include "EHCamera.h"

namespace EH
{
	Animation::Animation()
		:
		  mAnimator(nullptr)
		, mbComplete(false)
		, mSpriteSheet{}
		, mIndex(-1)
		, mTime(0.f)
		, mTexture(nullptr)
	{

	}

	Animation::~Animation()
	{
	}

	void Animation::Update()
	{
		if (mbComplete)
			return;

		mTime += Time::GetDeltaTime();

		if (mSpriteSheet[mIndex].duration < mTime)
		{
			mTime = 0.f;
			if (mIndex < mSpriteSheet.size() - 1)
			{
				mIndex++;
			}
			else
			{
				mbComplete = true;
			}
		}
	}

	void Animation::Render(HDC hdc)
	{
		if (mTexture == nullptr)
			return;

		Transform* tf = mAnimator->GetOwner()->GetComponent<Transform>();

		Math::Vector2<float> pos = tf->Getpos();
		Math::Vector2<float> scale = tf->GetScale();

		if (mAnimator->GetAffectedCamera())
			pos = Camera::CaculatePos(pos);

		if (mTexture == nullptr)
		{
			//Rectangle(hdc, pos.x - scale.x / 2.f, pos.y - scale.x / 2.f, pos.x + scale.x, pos.y + scale.y);
		}
		else if (mTexture->GetType() == eTextureType::Bmp)
		{
			if (mAnimator->GetAlpha() <= 1.0f)
			{
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				func.SourceConstantAlpha = 255;

				AlphaBlend(hdc,
					pos.x - scale.x / 2.f, pos.y - scale.y / 2.f,
					scale.x, scale.y,
					mTexture->GetHDC(),
					mSpriteSheet[mIndex].leftTop.x, mSpriteSheet[mIndex].leftTop.y,
					mSpriteSheet[mIndex].Size.x, mSpriteSheet[mIndex].Size.y,
					func);
			}
			else
			{
				TransparentBlt(hdc,
					pos.x - scale.x / 2.f, pos.y - scale.y / 2.f,
					scale.x, scale.y,
					mTexture->GetHDC(),
					mSpriteSheet[mIndex].leftTop.x, mSpriteSheet[mIndex].leftTop.y,
					mSpriteSheet[mIndex].Size.x, mSpriteSheet[mIndex].Size.y,
					RGB(255, 0, 255));
			}
		}
		else if (mTexture->GetType() == eTextureType::Png)
		{
			Gdiplus::ImageAttributes imageAtt = {};

			::Graphics g(hdc);
			g.SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
			g.DrawImage(mTexture->GetImage(),
				Rect(pos.x - scale.x / 2.f, pos.y - scale.y / 2.f, scale.x, scale.y),
				mSpriteSheet[mIndex].leftTop.x, mSpriteSheet[mIndex].leftTop.y,
				mSpriteSheet[mIndex].Size.x, mSpriteSheet[mIndex].Size.y,
				Gdiplus::UnitPixel,
				&imageAtt);
		}
	}

	void Animation::Create(const std::wstring& name, Texture* texture, Math::Vector2<float> leftTop, Math::Vector2<float> size, Math::Vector2<float> offset, UINT spriteLength, float duration)
	{
		mTexture = texture;

		for (size_t i = 0; i < spriteLength; i++)
		{
			Sprite sprite = {};
			sprite.duration = duration;
			sprite.leftTop.x = leftTop.x + (size.x * i);
			sprite.leftTop.y = leftTop.y;
			sprite.Size = size;
			sprite.Offset = offset;

			mSpriteSheet.push_back(sprite);
		}
	}

	void Animation::Reset()
	{
		mTime = 0.f;
		mIndex = 0;
		mbComplete = false;
	}
}
