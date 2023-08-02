#include "EHCanvas.h"
#include "EHSceneManager.h"
#include "EHGameObject.h"
#include "EHImageObject.h"
#include "EHTexture.h"
#include "EHObject.h"
#include "EHResources.h"


namespace EH
{
	Canvas::Canvas()
	{
	}

	Canvas::~Canvas()
	{
	}

	void Canvas::Initialize()
	{
	}

	void Canvas::Update()
	{
		GameObject::Update();

	}

	void Canvas::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	ImageObject* Canvas::AddImageObject(const std::wstring& name, Texture* texture, bool affectedcamera
		, Math::Vector2<float> pos, Math::Vector2<float> scale
		, Math::Vector2<float> offset, float alpha)
	{
		ImageObject* image = Find(name);
		if (image != nullptr)
		{
			return image;
		}
		image = object::Instantiate<ImageObject>(enums::eLayerType::UI);
		Transform* tr = image->GetComponent<Transform>();
		SpriteRenderer* sr = image->GetComponent<SpriteRenderer>();
		tr->SetPos(Math::Vector2<float>(pos.x, pos.y));
		tr->SetScale(Math::Vector2<float>(scale.x, scale.y));
		sr->SetImg(texture);
		sr->SetAffectCamera(affectedcamera);
		sr->SetAlpha(alpha);
		mImageObjects.insert(std::make_pair(name, image));
		return image;
	}

	ImageObject* Canvas::Find(const std::wstring& name)
	{
		std::map<std::wstring, class ImageObject*>::iterator iter = mImageObjects.find(name);
		if (iter == mImageObjects.end())
		{
			return nullptr;
		}
		return iter->second;
	}

	void Canvas::SetActive(bool enabled)
	{
		if (enabled)
		{
			std::map<std::wstring, class ImageObject*>::iterator iter = mImageObjects.begin();
			for (;iter != mImageObjects.end();iter++)
			{
				iter->second->SetState(eState::Active);
			}
		}
		else
		{
			std::map<std::wstring, class ImageObject*>::iterator iter = mImageObjects.begin();
			for (;iter != mImageObjects.end();iter++)
			{
				iter->second->SetState(eState::None);
			}
		}
	}
}