#pragma once
#include "Commoninclude.h"
#include "EHEntity.h"
#include "EHComponent.h"
#include "EHTransform.h"
#include "EHSpriteRenderer.h"
#include "EHAnimator.h"
#include "EHCollider.h"
#include "EHRigidbody.h"

namespace EH
{
	class GameObject : public Entity
	{
	public:

		enum class eState
		{
			Active,
			Pause,
			Dead,
			None,
		};

		friend __forceinline static void Destroy(GameObject* obj);

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

		eState GetState(){ return mState; }
		void SetState(eState state) {  mState = state; }

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

	private:
		void Dead() { mState = eState::Dead; }

	private:
		eState mState;
		std::vector<Component*> mComponents;
		std::wstring mPath;
	};

	__forceinline static void Destroy(GameObject* obj)
	{
		obj->Dead();
	}
}
