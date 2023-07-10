#include "EHSpriteRenderer.h"
#include "EHSceneManager.h"

namespace EH
{
	SpriteRenderer::SpriteRenderer()
		:
		Component(enums::eComponentType::SpriteRenderer)
		, mImg(nullptr)
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

		if (mImg == nullptr)
		{
			Rectangle(hdc, pos.x, pos.y, pos.x + scale.x, pos.y + scale.y);
		}
		else
		{
			::Graphics g(hdc);
			g.DrawImage(mImg->GetImage(), Rect(pos.x, pos.y, scale.x, scale.y), 0, 0, mImg->GetWidth(), mImg->GetHeight(), UnitPixel);
		}
	}
}