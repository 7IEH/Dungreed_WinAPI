#pragma once
#include "Commoninclude.h"
#include "EHGameObject.h"

namespace EH
{
	enum class eButtonState
	{
		 Idle
		,Selected
		,Pressed
		,None
	};

	enum class eClickEvent
	{
		  SceneChange
		, BugReport
		, None  
	};

	class Button : public GameObject
	{
	public:
		Button();
		virtual ~Button();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		bool OnButton();
		// 함수 포인터 만들어서 해보자
		void OnClick();
		void SetTransition(eButtonState state, Texture* texture) { mTransition[(UINT)state] = texture; }

		void SetScene(std::wstring scene) {mScene = scene;}
		void SetClickEvent(eClickEvent event) { mEvent = event; }
	private:
		eButtonState mCurState;
		std::vector<Texture*> mTransition;
		std::wstring mScene;
		eClickEvent mEvent;
	};
}