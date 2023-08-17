#pragma once
#include "EHGameObject.h"

namespace EH
{
	class Effect : public GameObject
	{
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:

	};
}