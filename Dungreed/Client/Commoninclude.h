#pragma once
#include <vector>
#include <map>
#include <set>
#include <list>
#include <functional>
#include <string>
#include "framework.h"

#define MAX 100

// DX11
#include<imgui.h>

// GDI+
#include<ole2.h>
#include<gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib") 

// EH
#include "EHMath.h"

// Enum
namespace EH::enums
{
	enum class eLayerType
	{
		BackGround,
		Player,
		Enemy,
		UI,
		End,
	};

	enum class eComponentType
	{
		Transform,
		SpriteRenderer,
		End,
	};
}