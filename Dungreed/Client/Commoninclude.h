#pragma once
#include <vector>
#include <map>
#include <set>
#include <list>
#include <functional>
#include <string>
#include "framework.h"
#include <bitset>
#include <assert.h>

#define MAX 100


// Sound
#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

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
		  BackGround
		, Floor
		, Enemy
		, Npc
		, UI
		, Player
		, Item
		, Sword
		, Bullet
		, Laser
		, Trigger
		, Detect
		, Steel
		, End
	};

	enum class eComponentType
	{
		  Transform
		, SpriteRenderer
		, Animator
		, Collider
		, Rigidbody
		, End
		,
	};

	enum class eWeapon
	{
		  Onehand
		, Twohand
		, Gun
		, None
	};
}