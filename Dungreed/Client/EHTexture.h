#pragma once
#include "Commoninclude.h"
#include "EHResource.h"

namespace EH
{
	enum class eTextureType
	{
		Bmp,
		Png,
		None,
	};

	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		virtual HRESULT Load() override;

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		Gdiplus::Image* GetImage() { return mImg; }
		eTextureType GetType() { return mType; }
		HDC GetHDC() { return mHdc; }

	private:
		eTextureType mType;
		Gdiplus::Image* mImg;

		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
	};
}

