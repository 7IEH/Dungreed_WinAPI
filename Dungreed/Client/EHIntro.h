#pragma once
#include "EHGameObject.h"

namespace EH
{
	class Intro : public GameObject
	{
	public:
		Intro();
		virtual ~Intro();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		UINT mCheck1;
		float mCheckTime;
	};
}


