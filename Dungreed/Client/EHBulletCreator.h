#pragma once
#include "EHEnemy.h"

namespace EH
{
	enum class AttackType
	{
		 Barrage
		,None
	};

	class BulletCreator : public Enemy
	{
	public:
		BulletCreator();
		virtual ~BulletCreator();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void Barrage();

		void SetType(AttackType type) { mType = type; }

		void SetDegree(float degree) { mDegree = degree; }

		void SetOwner(class Boss* owner) { mOwner = owner; }

	private:
		float mDegree;
		AttackType mType;

		class Sound* mBulletSound;
		class Boss* mOwner;
	};
}


