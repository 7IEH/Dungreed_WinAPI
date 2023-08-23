#pragma once
#include "EHEnemy.h"

namespace EH
{
	enum class ePillarAttack
	{
		  Bullet
		, Barrage
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

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void BulletP();
		void Barrage();

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
		static UINT mNum;

		class Weapon* mAttack;


		// Sound
		class Sound* mIceBulletSound;
	};
}


