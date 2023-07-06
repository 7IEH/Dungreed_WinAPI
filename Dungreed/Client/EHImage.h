#pragma once
#include "EHGameObject.h"

namespace EH
{
	class Image : public GameObject
	{
	public:
		Image();
		virtual ~Image();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
	};
}

