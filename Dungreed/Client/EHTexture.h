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

	class GameObject;
	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		virtual HRESULT Load() override;

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		Math::Vector2<int> GetPos() { return mPos; }
		Gdiplus::Image* GetImage() { return mImg; }
		eTextureType GetType() { return mType; }
		HDC GetHDC() { return mHdc; }
		void Render(HDC hdc, GameObject* obj,
			bool affectedcamera,
			Math::Vector2<float> size,
			Math::Vector2<float> lefttop = Math::Vector2<float>(0.f,0.f), 
			Math::Vector2<float> offset = Math::Vector2<float>(0.f, 0.f),
			float alpha = 0.9f);

	    void SetWidth(UINT width) { mWidth = width; }
		void SetHeight(UINT height) { mHeight = height; }
		void SetPos(Math::Vector2<int> pos) { mPos = pos; }
		void SetDegree(float degree) { mDegree = degree; }

		// pixel collide
		COLORREF GetTexturePixel(int x, int y);

		void Enabled(bool enabled) { mEnabled = enabled; }

	private:
		eTextureType mType;
		Gdiplus::Image* mImg;

		HBITMAP mBitmap;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;
		float mDegree;
		Math::Vector2<int> mPos;

		bool mEnabled;
	};
}

