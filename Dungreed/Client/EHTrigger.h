#pragma once
#include "EHGameObject.h"

namespace EH
{
	class Trigger : public GameObject
	{
	public:
		enum class eTriggertype
		{
			  Scenechange
			, None
		};

		Trigger();
		virtual ~Trigger();
		
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetType(eTriggertype type) { mType = type; }
		void SetScenename(std::wstring scenename) { mScenename = scenename; }

		void SceneChange();

		void SetDungeonEater(class GameObject* dungeoneater) { mDungeoneater = dungeoneater; }

	private:
		eTriggertype mType;
		std::wstring mScenename;

		float mCheckTime;
		float mDelayTime;

		UINT mCheck1;

		class Sound* mDungeoneat;
		class GameObject* mDungeoneater;
	};
}


