#include "EHPath.h"

namespace EH
{
	 wchar_t Path::mRelativePath[100] = L"";

	void Path::Initialize()
	{
		GetCurrentDirectory(MAX, mRelativePath);
	}
}