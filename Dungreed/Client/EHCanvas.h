#pragma once
#include "EHGameObject.h"

namespace EH
{
	class Canvas : public GameObject
	{
	public:
		Canvas();
		virtual ~Canvas();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		class ImageObject* AddImageObject(const std::wstring& name, Texture* texture, bool affectedcamera
			, Math::Vector2<float> pos, Math::Vector2<float> scale
			, Math::Vector2<float> offset = Math::Vector2<float>(0.f,0.f), float alpha = 1.f);

		class ImageObject* Find(const std::wstring& name);

		void SetActive(bool enabled);

	private:
		std::map<std::wstring, class ImageObject*> mImageObjects;
	};
}

