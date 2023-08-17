#pragma once
#include "EHGameObject.h"

namespace EH
{
	class DeadObj : public GameObject
	{
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		
	};
}


