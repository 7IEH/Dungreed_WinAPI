#pragma once
#include "Commoninclude.h"

namespace EH
{
	class DungeonManager
	{
	public:
		static void Initialize();
		static void Update();
		static void EnterDungeon();

	private:
		static std::map<std::wstring, bool> mClear;
		static float mSubCheckTime;
		static float mDelayTime;

		static UINT Check1;
	};
}


