#pragma once
#include "Commoninclude.h"

namespace EH
{
	class Objdata
	{
	public:
		static void SetMaxHP(int hp) { mMaxhp = hp; }
		static int GetMaxHP() { return mMaxhp; }

		static void SetHP(int hp) { mCurHp = hp; }
		static int GetHP() { return mCurHp; }

		static void SetGold(int gold) { mGold = gold; }
		static UINT GetGold() { return mGold; }

		static void SetFood(int food) { mFood = food; }
		static UINT GetFood() { return mFood; }

		static void SetLevel(int level) { mLevel = level; }
		static UINT GetLevel() { return mLevel; }

		static void SetDash(int dash) { mDash = dash; }
		static UINT GetDash() { return mDash; }

		static void SetWeapon(class BackGround* weapon) { mWeapon = weapon; }
		static class BackGround* GetWeapon() { return mWeapon; }

		static void SetSwing(bool swing) { mIsSwing = swing; }
		static bool GetSwing() { return mIsSwing; }

		static void SetActiveWeapon(enums::eWeapon weapon) { mActiveWeapon = weapon; }
		static enums::eWeapon GetActiveWeapon() { return mActiveWeapon; }

		static void SetWeaponCollider(class Weapon* weaponcollider) { mWeaponCollider = weaponcollider; }
		static class Weapon* GetWeaponCollider() { return mWeaponCollider; }

	private:
		static int mMaxhp;
		static int mCurHp;
		static UINT mGold;
		static UINT mFood;
		static UINT mLevel;
		static UINT mDash;

		static class BackGround* mWeapon;
		static bool mIsSwing;
		static enums::eWeapon mActiveWeapon;
		static class Weapon* mWeaponCollider;
	};
}


