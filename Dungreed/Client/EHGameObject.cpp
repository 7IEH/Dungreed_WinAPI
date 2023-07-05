#include "EHGameObject.h"

namespace EH
{
	GameObject::GameObject()
		:
		mPath(L"")
	{
		mComponents.push_back(new Transform());
		mComponents.push_back(new SpriteRenderer());

		for (Component* temp : mComponents)
		{
			temp->SetOwner(this);
		}
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			comp->Update();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* comp : mComponents)
		{
			comp->Render(hdc);
		}
	}
}