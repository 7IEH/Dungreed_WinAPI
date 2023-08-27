#pragma once
#include "EHGameObject.h"

namespace EH
{
	class Bullet : public GameObject
	{
	public:
		Bullet();
		virtual ~Bullet();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetRadian(float radian) { mRadian = radian; }
		float GetRadian() { return mRadian; }

		void SetDamage(UINT damage) { mDamage = damage; }
		UINT GetDamage() { return mDamage; }

		void SetDeleteTime(float deletetime) { mDeleteTime = deletetime; }
		float GetDeleteTime() { return mDeleteTime; }

		void SetStop(bool stop) { mIsStop = stop; }
		bool GetStop() { return mIsStop; }

		void SetPass(bool pass) { mIsPass = pass; }
		bool GetPass() { return mIsPass; }

		void SetDelete(bool deleted) { mIsDelete = deleted; }
		bool GetDelete() { return mIsDelete; }

		void SetSpeed(float speed) { mSpeed = speed; }
		float GetSpeed() { return mSpeed; }

		void SetPlayer(bool isplayer) { mIsPlayer = isplayer; }
		bool GetPlayer() { return mIsPlayer; }

		void SetTarget(class Enemy* enemy) { mTarget = enemy; }

		void setHoming(bool homing) { mHoming = homing; }

		void SetLaser(bool islaser) { mIsLaser = islaser; }

		void SetStar(bool isstar) { mIsStar = isstar; }

		void SetHit(bool hit) { mIsHit = hit; }
	private:
		float mRadian;
		UINT mDamage;
		float mDeleteTime;
		float mCheckTime;

		float mHomingTime;
		float mHomingCheckTime;
		bool mIsStop;
		bool mIsPass;
		float mSpeed;
		bool mIsDelete;

		bool mIsStar;

		//
		class Sound* mHitSound;

		bool mIsPlayer;
		bool mIsLaser;

		bool mHoming;
		class Enemy* mTarget;

		bool mIsHit;
	};
}
