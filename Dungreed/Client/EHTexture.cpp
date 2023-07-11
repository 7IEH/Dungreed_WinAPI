#include "EHTexture.h"
#include "EHApplication.h"

extern EH::Application application;

namespace EH
{
	Texture::Texture()
		:
		mImg(nullptr),
		mWidth(0.f),
		mHeight(0.f),
		mType(eTextureType::None),
		mHdc(nullptr),
		mBitmap(nullptr)
	{
	}

	Texture::~Texture()
	{

	}

	HRESULT Texture::Load()
	{
		std::wstring type = GetPath().substr(GetPath().find_last_of(L".") + 1);

		if (type == L"bmp")
		{
			mType = eTextureType::Bmp;
			Math::Vector2<int> winsize = application.GetWinSize();
			mBitmap = (HBITMAP)LoadImageW(nullptr, GetPath().c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			if (mBitmap == nullptr)
			{
				return S_FALSE;
			}

			mHdc = CreateCompatibleDC(application.GetMainDC());

			BITMAP info = {};
			GetObject(mBitmap, sizeof(BITMAP), &info);

			mWidth = info.bmWidth;
			mHeight = info.bmHeight;

			HBITMAP defaultbitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
			DeleteObject(defaultbitmap);

		}
		else if (type == L"png")
		{
			mType = eTextureType::Png;
			mImg = Gdiplus::Image::FromFile(GetPath().c_str());
			if (mImg == nullptr)
			{
				return  S_FALSE;
			}
			mHeight = mImg->GetHeight();
			mWidth = mImg->GetWidth();
		}

		return S_OK;
	}
}