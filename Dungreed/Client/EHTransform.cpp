#include "EHTransform.h"

namespace EH
{
	Transform::Transform()
		:
		Component(enums::eComponentType::Transform)
		,mPos(0.f,0.f)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
	}

	void Transform::Render(HDC hdc)
	{
	}
}