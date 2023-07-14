#include "EHAnimator.h"
#include "EHResources.h"

namespace EH
{
	Animator::Animator()
		:
		Component(enums::eComponentType::Animator),
		mAnimations{},
		mActiveAnimation(nullptr),
		mbLoop(false),
		mAffectedCamera(true),
		mAlpha(1.f)
	{
	}


	Animator::~Animator()
	{
	}

	void Animator::Initialize()
	{
	}

	void Animator::Update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Update();
			if (mActiveAnimation->IsComplete() && mbLoop)
			{
				mActiveAnimation->Reset();
			}
		}
	}

	void Animator::Render(HDC hdc)
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Render(hdc);
		}
	}

	void Animator::CreateAnimation(const std::wstring& name, Texture* texutre, Math::Vector2<float> leftTop, Math::Vector2<float> Size, Math::Vector2<float> offset, UINT spriteLength, float duration)
	{
		Animation* anim = Resources::Find<Animation>(name);
		if (anim != nullptr)
			return;

		anim = new Animation();
		anim->Create(name, texutre, 
			leftTop, Size, 
			offset, spriteLength, duration);
		anim->SetAnimator(this);

		mAnimations.insert(std::make_pair(name, anim));
		Resources::Insert<Animation>(name, anim);
	}

	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter = mAnimations.find(name);
		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}

	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		Animation* anim = FindAnimation(name);
		if (anim == nullptr)
			return;

		mActiveAnimation = anim;
		mActiveAnimation->Reset();
		mbLoop = loop;
	}
}