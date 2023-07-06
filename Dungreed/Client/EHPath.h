#pragma once
#include "Commoninclude.h"

namespace EH
{
	class Path
	{
	public:
		static void Initialize();
		__forceinline static wchar_t* GetPath() { return mRelativePath; }

	private:
		static wchar_t mRelativePath[MAX];
	};
}
