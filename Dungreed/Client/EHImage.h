#pragma once
#include "Commoninclude.h"
#include "EHResource.h"

namespace EH
{
	class Image : public Resource
	{
	public:
		Image();
		virtual ~Image();

		virtual HRESULT Load() override;

		int GetWidth() { return mWidth; }
		int GetHeight() { return mHeight; }
		Gdiplus::Image* GetImage() { return mImg; }

	private:
		Gdiplus::Image* mImg;
		int mWidth;
		int mHeight;
	};
}

