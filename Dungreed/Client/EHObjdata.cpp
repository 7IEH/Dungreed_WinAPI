#include "EHObjdata.h"
#include "EHBackGround.h"
#include "EHWeapon.h"

namespace EH
{
	int Objdata::mMaxhp = 0;
	int Objdata::mCurHp = 0;
	UINT Objdata::mGold = 0;
	UINT Objdata::mFood = 0;
	UINT Objdata::mLevel = 0;
	UINT Objdata::mDash = 0;

	BackGround* Objdata::mWeapon = nullptr;
	bool Objdata::mIsSwing = false;
	enums::eWeapon Objdata::mActiveWeapon = enums::eWeapon::None;
	Weapon* Objdata::mWeaponCollider = nullptr;
}