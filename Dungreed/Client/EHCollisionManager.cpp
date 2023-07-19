#include "EHCollisionManager.h"

namespace EH
{
	std::map<UINT64, bool> CollisionManager::mCollisionMap = {};
	std::bitset<(UINT)enums::eLayerType::End> CollisionManager::mLayersMasks[(UINT)enums::eLayerType::End] = {};
}
