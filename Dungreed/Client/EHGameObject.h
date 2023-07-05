#pragma once
#include "Commoninclude.h"
#include "EHEntity.h"
#include "EHComponent.h"
#include "EHTransform.h"
#include "EHSpriteRenderer.h"

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

	private:
		std::vector<Component*> mComponents;
	};
}
