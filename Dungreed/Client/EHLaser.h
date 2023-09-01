#pragma once
#include "EHGameObject.h"

namespace EH
{
	class Laser : public GameObject
	{
	public:
		Laser();
		virtual ~Laser();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetLaserPos(Math::Vector2<float> pos);
		void SetRight(bool isright) { mIsRight = isright; }

	private:
		bool mIsRight;
		GameObject* mRightLaser[10];
		GameObject* mLeftLaser[10];

		int mDamage;

		class Sound* mHitSound;

		float mCheckTime;
		float mDeleteTime;
	};
}

