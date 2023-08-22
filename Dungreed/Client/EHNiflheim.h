#pragma once
#include "EHIcePillar.h"

namespace EH
{
	enum class eBossAttack
	{
		  Bullet
		, Barrage
		, FourBarrage
		, SquareFourBarrage
		, Bullet2
		, None
	};

	class Niflheim : public Enemy
	{
	public:
		Niflheim();
		virtual ~Niflheim();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void Idle();
		void Dealtime();
		void Attack();
		void Dead();

		void Bullet();
		void Barrage();
		void FourBarrage();
		void SquareFourBarrage();
		void Bullet2();

		void SetCheck(UINT check2) { mCheck2 = check2; }
		UINT GetCheck() { return mCheck2; }

		void SetStop(bool stop) { mStop = stop; }
	private:
		// Enter
		UINT mEnter;

		// IcePillar
		IcePillar* mIcePillar[4];

		// Attack Type
		eBossAttack mType;

		// Attack Time;
		UINT mCheck1;
		UINT mCheck2;

		bool mStop;

		// mMove
		float mMove;
	};
}

