#pragma once
#include "EHGameObject.h"

namespace EH
{
	class ImageObject : public GameObject
	{
	public:
		ImageObject();
		virtual ~ImageObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}


