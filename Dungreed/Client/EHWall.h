#pragma once
#include "EHGameObject.h"

namespace EH
{
	class Wall : public GameObject
	{
	public:
		Wall();
		virtual ~Wall();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetRight(bool right) { mIsRight = right; }

		void SetSteel(bool steel) { mIsSteel = steel; }

	private:
		bool mIsRight;
		bool mIsSteel;
	};
}

