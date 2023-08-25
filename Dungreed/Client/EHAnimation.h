#pragma once
#include "EHResource.h"

namespace EH
{
	class Texture;
	class Animator;
	class Animation : public Resource
	{
	public:
		struct Sprite
		{
			Math::Vector2<float> leftTop;
			Math::Vector2<float> Size;
			Math::Vector2<float> Offset;
			float duration;

			Sprite()
				:leftTop(Math::Vector2<float>(0.f,0.f))
				, Size(Math::Vector2<float>(0.f, 0.f))
				, Offset(Math::Vector2<float>(0.f, 0.f))
				, duration(0.f)
			{

			}
		};
		Animation();
		virtual ~Animation();

		void Update();
		void Render(HDC hdc);

		virtual HRESULT Load() override { return S_FALSE; }
		
		void Create(const std::wstring& name
			, class Texture* texture
			, Math::Vector2<float> leftTop, Math::Vector2<float> size, Math::Vector2<float> offset
			, UINT spriteLength, float duration);

		void Reset();

		bool IsComplete() { return mbComplete; }
		void SetAnimator(Animator* animator) { mAnimator = animator; }

		Texture* GetTexture() { return mTexture; }

	private:
		Animator* mAnimator;
		Texture* mTexture;

		std::vector<Sprite> mSpriteSheet;
		int mIndex;
		float mTime;
		bool mbComplete;
	};
}
