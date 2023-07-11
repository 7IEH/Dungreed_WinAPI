#include "EHSpriteRenderer.h"
#include "EHSceneManager.h"

namespace EH
{
	SpriteRenderer::SpriteRenderer()
		:
		Component(enums::eComponentType::SpriteRenderer)
		, mTexture(nullptr)
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

		if (mTexture == nullptr)
		{
			Rectangle(hdc, pos.x, pos.y, pos.x + scale.x, pos.y + scale.y);
		}
		else if (mTexture->GetType() == eTextureType::Bmp)
		{
			TransparentBlt(hdc, pos.x, pos.y, scale.x, scale.y, mTexture->GetHDC(), 0, 0, mTexture->GetWidth(), mTexture->GetHeight(), RGB(255, 0, 255));
		}
		else if (mTexture->GetType() == eTextureType::Png)
		{
			::Graphics g(hdc);
			g.DrawImage(mTexture->GetImage(), Rect(pos.x, pos.y, scale.x, scale.y), 0, 0, mTexture->GetWidth(), mTexture->GetHeight(), UnitPixel);
		}		
	}
}