#pragma once
#include "EHGameObject.h"
#include "EHBackGround.h"

namespace EH
{
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		UINT Level;
		UINT MaxHP;
		UINT CurHp;
		UINT Gold;
		UINT Food;
		BackGround* mHp;
	};
}
