#include "EHSpriteRenderer.h"

namespace EH
{
	SpriteRenderer::SpriteRenderer()
		:
		Component(enums::eComponentType::SpriteRenderer)
		, mSrcPos(0.f,0.f)
		, mSrcScale(0.f,0.f)
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
		std::wstring path = GetOwner()->GetImagePath();
		if (path == L"")
		{
			Rectangle(hdc, pos.x,pos.y,pos.x+ scale.x,pos.y+scale.y);
		}
		else
		{
			wchar_t temp[100] = L"";
			for (int i = 0;i < 100;i++)
			{
				temp[i] = Path::GetPath()[i];
			}
			std::wstring absPath = temp + path;
			Image* img = Image::FromFile(absPath.c_str());
			::Graphics g(hdc);
			g.DrawImage(img,Rect(pos.x, pos.y, scale.x, scale.y), mSrcPos.x, mSrcPos.y, mSrcScale.x, mSrcScale.y,UnitPixel);
		}
	}
}