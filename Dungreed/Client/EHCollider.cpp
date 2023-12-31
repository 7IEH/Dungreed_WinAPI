#include "EHCollider.h"
#include "EHTransform.h"
#include "EHGameObject.h"
#include "EHCamera.h"

namespace EH
{
	bool Collider::mRender = false;

	Collider::Collider()
		:
		Component(enums::eComponentType::Collider)
		, mbisCollision(false)
		, mScale(Math::Vector2<float>(0.f, 0.f))
		, mOffset(Math::Vector2<float>(0.f, 0.f))
		, mbAffectedCamera(true)
		, mType(eColliderType::Box)
		, mbEnabled(true)
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

		if (mRender)
		{
			if (mbAffectedCamera)
				pos = Camera::CaculatePos(pos);

			HBRUSH hTransParentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hTransParentBrush);

			HPEN hPen = nullptr;
			HPEN hOldPen = nullptr;

			if (mbisCollision)
			{
				hPen = (HPEN)CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
				hOldPen = (HPEN)SelectObject(hdc, hPen);
			}
			else
			{
				hPen = (HPEN)CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
				hOldPen = (HPEN)SelectObject(hdc, hPen);
			}

			if (mType == eColliderType::Box)
			{
				Rectangle(hdc, pos.x - mScale.x / 2.f + mOffset.x, pos.y - mScale.y / 2.f + mOffset.y,
					pos.x + mScale.x / 2.f + mOffset.x, pos.y + mScale.y / 2.f + mOffset.y);
			}
			else if (mType == eColliderType::Circle)
			{
				Ellipse(hdc, pos.x - mScale.x / 2.f + mOffset.x, pos.y - mScale.y / 2.f + mOffset.y,
					pos.x + mScale.x / 2.f + mOffset.x, pos.y + mScale.y / 2.f + mOffset.y);
			}

			SelectObject(hdc, hOldBrush);
			DeleteObject(hTransParentBrush);

			SelectObject(hdc, hOldPen);
			DeleteObject(hPen);
		}
	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		mbisCollision = true;
		GetOwner()->OnCollisionEnter(other);
	}

	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}

	void Collider::OnCollisionExit(Collider* other)
	{
		mbisCollision = false;
		GetOwner()->OnCollisionExit(other);
	}
}
