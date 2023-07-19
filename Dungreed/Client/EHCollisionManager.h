#pragma once
#include "Commoninclude.h"

namespace EH
{
	union ColliderID
	{
		struct
		{
			UINT left;
			UINT right;
		};
		UINT64 id;
	};

	class CollisionManager
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

	private:
		static std::map<UINT64, bool> mCollisionMap;
		static std::bitset<(UINT)enums::eLayerType::End> mLayersMasks[(UINT)enums::eLayerType::End];
	};
}
