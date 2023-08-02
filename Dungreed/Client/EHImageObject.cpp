#include "EHImageObject.h"

namespace EH
{
	ImageObject::ImageObject()
	{
		AddComponent<SpriteRenderer>();
	}

	ImageObject::~ImageObject()
	{

	}

	void ImageObject::Initialize()
	{

	}

	void ImageObject::Update()
	{
		GameObject::Update();
	}

	void ImageObject::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}