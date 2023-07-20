#pragma once
#include "Commoninclude.h"
#include "EHEntity.h"
#include "EHComponent.h"
#include "EHTransform.h"
#include "EHSpriteRenderer.h"
#include "EHAnimator.h"
#include "EHCollider.h"

namespace EH
{
	class GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void SetImagePath(std::wstring path) { mPath = path; }
		std::wstring GetImagePath() { return mPath; }

		template <typename T>
		T* GetComponent()
		{
			T* temp = nullptr;
			for (Component* comp : mComponents)
			{
				temp = dynamic_cast<T*>(comp);
				if (temp != nullptr)
					return temp;
			}
			return temp;
		}

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			mComponents.push_back(comp);
			comp->SetOwner(this);
			return comp;
		}

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		std::vector<Component*> mComponents;
		std::wstring mPath;
	};
}
