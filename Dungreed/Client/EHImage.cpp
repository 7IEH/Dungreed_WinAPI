#include "EHImage.h"

namespace EH
{
	Image::Image()
		:
		mImg(nullptr),
		mWidth(0.f),
		mHeight(0.f)
	{
	}

	Image::~Image()
	{

	}

	HRESULT Image::Load()
	{
		mImg = Gdiplus::Image::FromFile(GetPath().c_str());
		if (mImg == nullptr)
		{
			return  S_FALSE;
		}


		mHeight = mImg->GetHeight();
		mWidth = mImg->GetWidth();


		return S_OK;
	}
}