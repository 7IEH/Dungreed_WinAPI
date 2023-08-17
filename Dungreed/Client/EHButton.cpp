#include "EHButton.h"
#include "EHApplication.h"
#include "EHSceneManager.h"
#include "EHSound.h"
#include "EHCamera.h"
#include "EHPlayer.h"

extern EH::Application application;

namespace EH
{
	Button::Button()
		:
		  mCurState(eButtonState::Idle)
		, mEvent(eClickEvent::None)
		, mScene(L"")
	{
		AddComponent<SpriteRenderer>();
		mTransition.resize((UINT)(UINT)eButtonState::None);
		for (size_t i = 0; i < (UINT)eButtonState::None; i++)
		{
			mTransition[i] = nullptr;
		}
	}

	Button::~Button()
	{
	}

	void Button::Initialize()
	{
	}

	void Button::Update()
	{
		SpriteRenderer* sprite = GetComponent<SpriteRenderer>();
		if (sprite == nullptr)
			return;

		if (OnButton())
		{
			mCurState = eButtonState::Selected;
			if (Input::Getkey(eKeyCode::MouseLeftClick).state == eKeyState::DOWN)
			{
				OnClick();
				mCurState = eButtonState::Pressed;
			}
		}
		else
		{
			mCurState = eButtonState::Idle;
		}
		sprite->SetImg(mTransition[(UINT)mCurState]);
		GameObject::Update();
	}

	void Button::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	bool Button::OnButton()
	{
		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(application.GetHWND(), &pt);

		Transform* tr = GetComponent<Transform>();
		Math::Vector2<float> pos = tr->Getpos();
		Math::Vector2<float> scale = tr->GetScale();

		if ((pt.x >= pos.x-scale.x/2.f && pt.x <= pos.x + scale.x / 2.f) && (pt.y >= pos.y - scale.y / 2.f && pt.y <= pos.y + scale.y / 2.f))
		{
			return true;
		}
		return false;
	}

	// 함수 이벤트
	void Button::OnClick()
	{
		if (mEvent == eClickEvent::SceneChange)
		{
			if (SceneManager::GetCurScene()->GetBGM() != nullptr)
				SceneManager::GetCurScene()->GetBGM()->Stop(true);

			Scene* curscene =  SceneManager::LoadScene(mScene);
			curscene->GetBGM()->Play(true);
			Camera::SetTarget(curscene->GetPlayer());
		}
	}
}
