#include "EHSpriteRenderer.h"
#include "EHSceneManager.h"
#include "EHGameObject.h"
#include "EHAnimator.h"
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
		if (mTexture == nullptr)
			return;

		
		mTexture->Render(hdc, GetOwner()
			, mAffectCamera
			, Math::Vector2<float>(mTexture->GetWidth(), mTexture->GetHeight()), Math::Vector2<float>(mTexture->GetPos().x
			, mTexture->GetPos().y), mAlpha);
	}
}