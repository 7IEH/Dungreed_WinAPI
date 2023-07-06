#include "EHImage.h"

namespace EH
{
	Image::Image()
	{
		AddComponent<SpriteRenderer>();
	}

	Image::~Image()
	{
	}

	void Image::Initialize()
	{
	}

	void Image::Update()
	{
		GameObject::Update();
	}

	void Image::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}