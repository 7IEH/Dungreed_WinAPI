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

		mTexture->Render(hdc, mAnimator->GetOwner()
			, mAnimator->GetAffectedCamera()
			, mSpriteSheet[mIndex].Size, mSpriteSheet[mIndex].leftTop, mSpriteSheet[mIndex].Offset
			, mAnimator->GetAlpha());
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
