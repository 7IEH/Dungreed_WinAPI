#include "EHSpriteRenderer.h"
#include "EHSceneManager.h"

namespace EH
{
	SpriteRenderer::SpriteRenderer()
		:
		Component(enums::eComponentType::SpriteRenderer)
		, mSrcPos(0.f,0.f)
		, mSrcScale(0.f,0.f)
		, mCurImg(nullptr)
		, mImg{}
	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::AddImg(const std::wstring& path,const std::wstring& name)
	{
		wchar_t temp[100] = L"";
		for (int i = 0;i < 100;i++)
		{
			temp[i] = Path::GetPath()[i];
		}
		std::wstring absPath = temp + path;
		Image* img = Image::FromFile(absPath.c_str());
		mImg.insert(std::make_pair(name, img));
	}

	void SpriteRenderer::SetImg(const std::wstring& name)
	{
		std::map<std::wstring, Gdiplus::Image*>::iterator iter = mImg.find(name);

		if (iter == mImg.end())
			return;

		mCurImg = iter->second;
	}

	void SpriteRenderer::Initialize()
	{
	}

	void SpriteRenderer::Update()
	{
	}

	void SpriteRenderer::Render(HDC hdc)
	{
		Transform* tf = GetOwner()->GetComponent<Transform>();
		Math::Vector2<float> pos = tf->Getpos();
		Math::Vector2<float> scale = tf->GetScale();
		if (GetOwner()->GetImagePath()==L"")//mCurImg==nullptr
		{
			wchar_t szFloat[50] = {};

			swprintf_s(szFloat, 50, SceneManager::GetCurScene()->GetName().c_str());
			int strLen = wcsnlen_s(szFloat, 50);

			TextOut(hdc, 20, 20, szFloat, strLen);
			if(GetOwner()->GetName()==L"Player")
			{
				HBRUSH hNewBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
				HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc,hNewBrush);
				HPEN hNewPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
				HPEN hOldPen = (HPEN)SelectObject(hdc, hNewPen);
				Rectangle(hdc, pos.x, pos.y, pos.x + scale.x, pos.y + scale.y);
				SelectObject(hdc, hOldBrush);
				SelectObject(hdc, hOldPen);
				DeleteObject(hNewBrush);
				DeleteObject(hNewPen);
			}
			else
			{
				Rectangle(hdc, pos.x, pos.y, pos.x + scale.x, pos.y + scale.y);
			}
		}
		else
		{
			::Graphics g(hdc);
			g.DrawImage(mCurImg,Rect(pos.x, pos.y, scale.x, scale.y), mSrcPos.x, mSrcPos.y, mSrcScale.x, mSrcScale.y, UnitPixel);
			//delete g;
		}
	}
}