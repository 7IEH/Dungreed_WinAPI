#include "EHGameObject.h"

namespace EH
{
	GameObject::GameObject()
		:
		  mPath(L"")
		, mState(eState::Active)
	{
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			delete comp;
			comp = nullptr;
		}
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::Update()
	{
		if (mState == eState::Active)
		{
			for (Component* comp : mComponents)
			{
				comp->Update();
			}
		}
	}

	void GameObject::Render(HDC hdc)
	{
		if (mState == eState::Active)
		{
			for (Component* comp : mComponents)
			{
				comp->Render(hdc);
			}
		}
	}

	void GameObject::OnCollisionEnter(Collider* other)
	{
	}

	void GameObject::OnCollisionStay(Collider* other)
	{
	}

	void GameObject::OnCollisionExit(Collider* other)
	{
	}
}