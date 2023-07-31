#pragma once
#include "EHGameObject.h"

namespace EH
{
	class Slope : public GameObject
	{
	public:
		Slope();
		virtual ~Slope();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;


		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetIntercept(float intercept) { mYintercept = intercept; }

		void SetCorrection(float correction) { mCorrection = correction; }

		void SetRight(bool right) { mIsRight = right; }

	private:
		float mYintercept;
		float mCorrection;
		bool mIsRight;
		UINT mEnterCounter;
	};
}

