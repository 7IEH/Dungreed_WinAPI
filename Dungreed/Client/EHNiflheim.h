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
		, Icicle
		, Spear
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

		void Bulletp();
		void Barrage();
		void FourBarrage();
		void SquareFourBarrage();
		void Bullet2();
		void Icicle();
		void Spear();

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
		UINT mCheck3;

		bool mStop;

		// mMove
		float mMove;

		class Weapon* mAttack;

		// Sound
		class Sound* mDefeatSound;

		// Boss UI
		class Canvas* mCanvas;

		// bool
		bool mIsRight;

		// Icicle
		class Bullet* mIcicle[8];
		class GameObject* mRedZone[8];

		// IceSpear; 
		class Bullet* mSpear;
		class GameObject* mRedSpearZone;

		// Phase
		UINT mPhase;
	};
}

