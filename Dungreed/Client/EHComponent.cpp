#include "EHComponent.h"

namespace EH
{
	Component::Component(enums::eComponentType type)
		:
		mType(type)
		,mOwner(nullptr)
	{
	}
	Component::~Component()
	{
	}
	void Component::Initialize()
	{
	}
	void Component::Update()
	{
	}
	void Component::Render(HDC hdc)
	{
	}
}