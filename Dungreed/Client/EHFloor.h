#pragma once
#include "EHGameObject.h"

namespace EH
{
	class Floor : public GameObject
	{
	public:
		Floor();
		virtual ~Floor();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
		
		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetDownFloor(bool downfloor) { mIsDownFloor = downfloor; }
		bool GetDownFloor() { return mIsDownFloor; }

	private:
		bool mIsDownFloor;
	};
}


