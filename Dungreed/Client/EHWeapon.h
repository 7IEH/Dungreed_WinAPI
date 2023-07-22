#pragma once
#include "EHGameObject.h"


namespace EH
{
	class Weapon : public GameObject
	{
	public:
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:

	};
}

