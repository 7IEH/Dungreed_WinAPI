#pragma once
#include "EHComponent.h"

namespace EH
{
	class Collider : public Component
	{
	public:
		enum class eColliderType
		{
			  Box
			, Circle
			, None
		};

		Collider();
		virtual ~Collider();
		
		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void SetScale(Math::Vector2<float> scale) { mScale = scale; }
		void SetOffset(Math::Vector2<float> scale) { mOffset = scale; }

		Math::Vector2<float> GetScale() { return mScale; }
		Math::Vector2<float> GetOffset() { return mOffset; }

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void SetAffectedCamera(bool affect) { mbAffectedCamera = affect; }
		void SetType(eColliderType type) { mType = type; }

		void enabled(bool enabled) { mbEnabled = enabled; }
		bool GetEnabled() { return mbEnabled; }

	private:
		eColliderType mType;
		bool mbisCollision;
		bool mbAffectedCamera;
		Math::Vector2<float> mScale;
		Math::Vector2<float> mOffset;
		bool mbEnabled;
	};
}
