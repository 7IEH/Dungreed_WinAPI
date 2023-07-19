#include "EHCollider.h"
#include "EHTransform.h"
#include "EHGameObject.h"

namespace EH
{
	Collider::Collider()
		:
		Component(enums::eComponentType::Collider)
		, mScale(Math::Vector2<float>(0.f, 0.f))
		, mOffset(Math::Vector2<float>(0.f, 0.f))
	{
	}

	Collider::~Collider()
	{
	}

	void Collider::Initialize()
	{
	}

	void Collider::Update()
	{
	}

	void Collider::Render(HDC hdc)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Math::Vector2<float> pos = tr->Getpos();


		HBRUSH hTransParentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hTransParentBrush);

		HPEN hGreenPen = (HPEN)CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		HPEN hOldPen = (HPEN)SelectObject(hdc, hGreenPen);

		Rectangle(hdc, pos.x - mScale.x / 2.f, pos.y - mScale.y / 2.f,
			pos.x + mScale.x / 2.f, pos.y + mScale.y / 2.f);

		SelectObject(hdc, hOldBrush);
		DeleteObject(hTransParentBrush);

		SelectObject(hdc, hOldPen);
		DeleteObject(hGreenPen);
	}
}
