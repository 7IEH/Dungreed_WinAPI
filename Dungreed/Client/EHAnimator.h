#pragma once
#include "EHComponent.h"
#include "EHAnimation.h"

namespace EH
{
	class Animator : public Component
	{
	public:
		Animator();
		virtual ~Animator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void CreateAnimation(const std::wstring& name, class Texture* texutre,
			Math::Vector2<float> leftTop, Math::Vector2<float> Size, Math::Vector2<float> offset,
			UINT spriteLength, float duration);

		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop);

		bool GetAffectedCamera() { return mAffectedCamera; }
		void SetAffectedCamera(bool affect) { mAffectedCamera = affect; }
		float GetAlpha() { return mAlpha; }
		void SetAlpha(float alpha) { mAlpha = alpha; }

		/*void SetActiveAnimation(Animation* activeanimation, bool loop) 
		{ 
			mActiveAnimation = activeanimation;
			mbLoop = loop;
		}*/
		Animation* GetActiveAnimation() { return mActiveAnimation; }

	private:
		std::map<std::wstring, Animation*>mAnimations;

		Animation* mActiveAnimation;
		bool mbLoop;
		bool mAffectedCamera;
		float mAlpha;
	};
}

