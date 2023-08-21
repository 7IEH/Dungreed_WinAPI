#pragma once
#include "Commoninclude.h"

namespace EH
{
	class Objdata
	{
	public:
		static void Initialize();

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

		static void SetWeapon(class Weapon* weapon) { mWeapon = weapon; }
		static class Weapon* GetWeapon() { return mWeapon; }

		static void SetSwing(bool swing) { mIsSwing = swing; }
		static bool GetSwing() { return mIsSwing; }

		static void SetActiveWeapon(enums::eWeapon weapon) { mActiveWeapon = weapon; }
		static enums::eWeapon GetActiveWeapon() { return mActiveWeapon; }

		static void SetWeaponCollider(class Weapon* weaponcollider) { mWeaponCollider = weaponcollider; }
		static class Weapon* GetWeaponCollider() { return mWeaponCollider; }

		static class Weapon* GetSword() { return sword; }
		static class Weapon* GetSwordCollider() { return swordCollider; }
		static class Weapon* GetMagicWand() { return magicwand; }
		static class Weapon* GetBelialSword() { return BelialSword; }
		static class Weapon* GetBelialSwordCollider() { return BelialSwordCollider; }

		static void GetInventory(std::wstring inventory[3][5]) 
		{ 
			for (int y = 0;y < 3;y++)
			{
				for (int x = 0;x < 5;x++)
				{
					inventory[y][x] = mInventory[y][x];
				}
			}
		}
		static void SetInventory(std::wstring inventory[3][5])
		{
			for (int y = 0;y < 3;y++)
			{
				for (int x = 0;x < 5;x++)
				{
					mInventory[y][x] = inventory[y][x];
				}
			}
		}

	private:
		static int mMaxhp;
		static int mCurHp;
		static UINT mGold;
		static UINT mFood;
		static UINT mLevel;
		static UINT mDash;

		static class Weapon* mWeapon;
		static bool mIsSwing;
		static enums::eWeapon mActiveWeapon;
		static class Weapon* mWeaponCollider;

		// Weapon
		static class Weapon* sword;
		static class Weapon* swordCollider;
		static class Weapon* magicwand;
		static class Weapon* BelialSword;
		static class Weapon* BelialSwordCollider;

		// Inventory
		static std::wstring mInventory[3][5];
	};
}


