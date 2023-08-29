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
			, Attack
			, Dealtime
			, Dead
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

		void SetHP(int hp) { mHP = hp; }
		int GetHP() { return mHP; }

		void SetMaxHP(int maxhp) { mMaxHp = maxhp; }
		int GetMaxHP() { return mMaxHp; }
		
		class Sound* GetHitSound() { return mHitMonster; }

		class ImageObject* GetHpBaseImage() { return mHpbaseimage; }
		class ImageObject* GetHpImage() { return mHpimage; }

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
		int mHP;
		int mMaxHp;

		class ImageObject* mHpbaseimage;
		class ImageObject* mHpimage;

		// check
		static UINT mCheck1;

	};
}

