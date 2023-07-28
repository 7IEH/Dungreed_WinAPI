#include "EHJailArchor.h"
#include "EHPlayer.h"
#include "EHProjectile.h"
#include "EHObject.h"
#include "EHCamera.h"

namespace EH
{
	JailArchor::JailArchor()
	{
		SetDelayTime(5.f);

	}

	JailArchor::~JailArchor()
	{
	}

	void JailArchor::Initialize()
	{
	}

	void JailArchor::Update()
	{
		GameObject::Update();
		float checktime = GetCheckTime();
		SetCheckTime(checktime += Time::GetDeltaTime());
		if (GetDelayTime() < checktime)
		{
			Projectile* arrow = object::Instantiate<Projectile>(enums::eLayerType::UI);
			Transform* archortr = GetComponent<Transform>();
			Transform* arrowtr = arrow->GetComponent<Transform>();
			Transform* targettr = GetTarget()->GetComponent<Transform>();
;			Math::Vector2<float> archorpos = archortr->Getpos();
;			Math::Vector2<float> targetpos = targettr->Getpos();
			arrowtr->SetPos(Math::Vector2<float>(archorpos.x, archorpos.y));
			targetpos = Camera::CaculatePos(targetpos);
			archorpos = Camera::CaculatePos(archorpos);
			// 원래 공식으로 반대로 나감
			float radian = Math::Radian(targettr->Getpos() , archortr->Getpos());
			arrow->SetRadian(radian);
			arrow->AddComponent<Collider>();
			arrow->GetComponent<Collider>()->SetScale(Math::Vector2<float>(40.f, 40.f));
			SetCheckTime(0.f);
		}
	}

	void JailArchor::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void JailArchor::OnCollisionEnter(Collider* other)
	{
	}

	void JailArchor::OnCollisionStay(Collider* other)
	{
	}

	void JailArchor::OnCollisionExit(Collider* other)
	{
	}
}

