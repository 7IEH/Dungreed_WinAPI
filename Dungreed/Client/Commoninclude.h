#pragma once
#include <vector>
#include <map>
#include <set>
#include <list>
#include <functional>
#include <string>
#include "framework.h"
#include <mmsystem.h>
#include <bitset>

#define MAX 100

// DX11
#include<imgui.h>

// GDI+
#include<ole2.h>
#include<gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib") 

// WindowGraphic
#pragma comment(lib, "msimg32.lib")

// EH
#include "EHMath.h"

// Enum
namespace EH::enums
{
	enum class eLayerType
	{
		BackGround,
		Floor,
		Enemy,
		UI,
		Npc,
		Player,
		End,
	};

	enum class eComponentType
	{
		Transform,
		SpriteRenderer,
		Animator,
		Collider,
		Rigidbody,
		End,
	};
}