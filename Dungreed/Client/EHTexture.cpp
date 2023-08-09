#include "EHTexture.h"
#include "EHApplication.h"
#include "EHCamera.h"
#include "EHGameObject.h"

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
		mBitmap(nullptr),
		mPos(0,0),
		mDegree(0.f)
	{
	}

	Texture::~Texture()
	{
		delete mImg;
		mImg = nullptr;

		DeleteObject(mBitmap);
		mBitmap = NULL;
	}

	HRESULT Texture::Load()
	{
		std::wstring type = GetPath().substr(GetPath().find_last_of(L".") + 1);

		if (type == L"bmp")
		{
			mType = eTextureType::Bmp;
			Math::Vector2<int> winsize = application.GetWinSize();
			std::wstring test = GetPath();
			mBitmap = (HBITMAP)LoadImageW(nullptr, GetPath().c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
			int a = 0;
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

	void Texture::Render(HDC hdc, GameObject* obj, bool affectedcamera, Math::Vector2<float>size, Math::Vector2<float> lefttop, Math::Vector2<float> offset,float alpha)
	{
		if (mImg == nullptr && mBitmap == nullptr)
			return;

		Transform* tf = obj->GetComponent<Transform>();

		Math::Vector2<float> pos = tf->Getpos();
		Math::Vector2<float> scale = tf->GetScale();

		if (affectedcamera)
			pos = Camera::CaculatePos(pos);

		if (mType == eTextureType::Bmp)
		{
			if (alpha <= 1.0f)
			{
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				alpha = (int)(alpha * 255.0f);
				func.SourceConstantAlpha = alpha;

				AlphaBlend(hdc,
					pos.x - scale.x / 2.f + offset.x, pos.y - scale.y / 2.f + offset.y,
					scale.x, scale.y,
					mHdc,
					lefttop.x, lefttop.y,
					size.x, size.y,
					func);
			}
			else
			{
				TransparentBlt(hdc,
					pos.x - scale.x / 2.f + offset.x, pos.y - scale.y / 2.f + offset.y,
					scale.x, scale.y,
					mHdc,
					lefttop.x, lefttop.y,
					size.x, size.y,
					RGB(255, 0, 255));
			}
		}
		else if (mType == eTextureType::Png)
		{
			Gdiplus::ImageAttributes imageAtt = {};
			::Graphics g(hdc);

			if (mDegree == 0.f)
			{
				g.SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
				g.DrawImage(mImg,
					Rect(pos.x - scale.x / 2.f + offset.x, pos.y - scale.y / 2.f + offset.y, scale.x, scale.y),
					lefttop.x, lefttop.y,
					size.x, size.y,
					Gdiplus::UnitPixel,
					&imageAtt);
			}
			else
			{
				//Gdiplus::Matrix matrix;
				g.TranslateTransform(pos.x, pos.y);
				g.RotateTransform(mDegree);
				g.TranslateTransform(-pos.x, -pos.y);
				/*matrix.RotateAt(mDegree, Gdiplus::PointF(pos.x, pos.y));
				g.SetTransform(&matrix);*/
				g.SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
				g.DrawImage(mImg,
					Rect(pos.x - scale.x / 2.f + offset.x, pos.y - scale.y / 2.f + offset.y, scale.x, scale.y),
					lefttop.x, lefttop.y,
					size.x, size.y,
					Gdiplus::UnitPixel,
					&imageAtt);

				int a = 0;
			}
		}
	}

	COLORREF Texture::GetTexturePixel(int x, int y)
	{
		COLORREF rgb = GetPixel(mHdc, x, y);
		return rgb;
	}
}