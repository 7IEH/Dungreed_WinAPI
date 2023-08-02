#pragma once
#include "Commoninclude.h"

namespace EH
{
	class Objdata
	{
	public:
		static void SetHP(int hp) { mHp = hp; }
		static int GetHP() { return mHp; }

		static void SetGold(int gold) { mGold = gold; }
		static UINT GetGold() { return mGold; }

		static void SetFood(int food) { mFood = food; }
		static UINT GetFood() { return mFood; }

		static void SetLevel(int level) { mLevel = level; }
		static UINT GetLevel() { return mLevel; }

		static void SetDash(int dash) { mDash = dash; }
		static UINT GetDash() { return mDash; }

	private:
		static int mHp;
		static UINT mGold;
		static UINT mFood;
		static UINT mLevel;
		static UINT mDash;
	};
}


