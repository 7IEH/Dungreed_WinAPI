#pragma once
#include "EHEnemy.h"

namespace EH
{
	enum class ePillarAttack
	{
		  Bullet
		, Barrage
		, FourBarrage
		, SquareFourBarrage
		, Bullet2
		, None
	};

	class IcePillar : public Enemy
	{
	public:
		IcePillar();
		virtual ~IcePillar();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void BulletP();
		void Barrage();
		void Barrage2();

		void SetDegree(float degree) { mDegree = degree; }
		float GetDegree() { return mDegree; }

		void SetOwner(class Niflheim* owner) { mOwner = owner; }

		void SetTargetPos(Math::Vector2<float> pos) { mTarget = pos; }

		void SetType(ePillarAttack type) { mType = type;}

	private:
		float mDegree;
		static UINT mCheck1;
		class Niflheim* mOwner;

		Math::Vector2<float> mTarget;

		ePillarAttack mType;
	};
}


