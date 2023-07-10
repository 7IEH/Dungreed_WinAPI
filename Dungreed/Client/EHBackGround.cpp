#include "EHBackGround.h"

namespace EH
{
	BackGround::BackGround()
	{
		AddComponent<SpriteRenderer>();
	}

	BackGround::~BackGround()
	{
	}

	void BackGround::Initialize()
	{
	}

	void BackGround::Update()
	{
		GameObject::Update();
	}

	void BackGround::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

}