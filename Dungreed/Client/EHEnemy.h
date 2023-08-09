#pragma once
#include "EHGameObject.h"

namespace EH
{
	class Enemy : public GameObject
	{
	public:
		enum class eState
		{
			Idle
			,Attack
			,Dead
		};

		Enemy();
		virtual ~Enemy();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetTarget(class Player* target) { mTarget = target; }
		class Player* GetTarget() { return mTarget; }

		void SetDelayTime(float delaytime) { mDelayTime = delaytime; }
		void SetCheckTime(float checktime) { mCheckTime = checktime; }

		void SetSubDelayTime(float delaytime) { mSubDelayTime = delaytime; }
		void SetSubCheckTime(float checktime) { mSubCheckTime = checktime; }

		float GetDelayTime() { return mDelayTime; }
		float GetCheckTime() { return mCheckTime; }

		float GetSubDelayTime() { return mSubDelayTime; }
		float GetSubCheckTime() { return mSubCheckTime; }

		void SetState(eState state) { mCurState = state; }
		eState GetState() { return mCurState; }

		void SetHP(UINT hp) { mHP = hp; }
		UINT GetHP() { return mHP; }
		
		class Sound* GetHitSound() { return mHitMonster; }

	private:
		class Player* mTarget;
		eState mCurState;
		float mDelayTime;
		float mCheckTime;
		float mSubDelayTime;
		float mSubCheckTime;

		// Sound
		class Sound* mHitMonster;
 
		// stat
		UINT mHP;
	};
}

