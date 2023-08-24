#include "EHObjdata.h"
#include "EHBackGround.h"
#include "EHWeapon.h"
#include "EHObject.h"
#include "EHResources.h"

namespace EH
{
	int Objdata::mMaxhp = 0;
	int Objdata::mCurHp = 0;
	UINT Objdata::mGold = 0;
	UINT Objdata::mFood = 0;
	UINT Objdata::mLevel = 0;
	UINT Objdata::mDash = 0;

	Weapon* Objdata::sword = nullptr;
	Weapon* Objdata::swordCollider = nullptr;
	Weapon* Objdata::magicwand = nullptr;
	Weapon* Objdata::BelialSword = nullptr;
	Weapon* Objdata::BelialSwordCollider = nullptr;
	Weapon* Objdata::Gun = nullptr;


	Weapon* Objdata::mWeapon = nullptr;
	bool Objdata::mIsSwing = false;
	enums::eWeapon Objdata::mActiveWeapon = enums::eWeapon::None;
	enums::eWeapon Objdata::mSubWeapon = enums::eWeapon::None;
	Weapon* Objdata::mWeaponCollider = nullptr;

	std::wstring Objdata::mInventory[3][5] = {};

	void Objdata::Initialize()
	{
		sword = object::Instantiate<Weapon>(enums::eLayerType::UI);
		Texture* texture = Resources::Load<Texture>(L"Onehand", L"..\\Resources\\Player\\Basic\\Attack\\ShortSword\\ShortSword.png");
		Transform* tr = sword->GetComponent<Transform>();
		tr->SetScale(Math::Vector2<float>(76.f, 28.f));
		sword->AddComponent<SpriteRenderer>();
		sword->GetComponent<SpriteRenderer>()->SetImg(texture);
		sword->GetComponent<SpriteRenderer>()->SetAffectCamera(true);
		texture->Enabled(false);

		swordCollider = object::Instantiate<Weapon>(enums::eLayerType::Sword);
		Collider* weaponcol = swordCollider->AddComponent<Collider>();
		weaponcol->SetScale(Math::Vector2<float>(120.f, 120.f));
		weaponcol->SetType(Collider::eColliderType::Circle);
		weaponcol->enabled(false);
		swordCollider->SetDelayTime(0.1f);

		magicwand = object::Instantiate<Weapon>(enums::eLayerType::UI);
		texture = Resources::Load<Texture>(L"Wand", L"..\\Resources\\Player\\Basic\\Attack\\LalaWand\\Lala'sMagicWand.png");
		tr = magicwand->GetComponent<Transform>();
		tr->SetScale(Math::Vector2<float>(52.f, 52.f));
		magicwand->AddComponent<SpriteRenderer>();
		magicwand->GetComponent<SpriteRenderer>()->SetImg(texture);
		magicwand->GetComponent<SpriteRenderer>()->SetAffectCamera(true);
		texture->Enabled(false);

		BelialSword = object::Instantiate<Weapon>(enums::eLayerType::UI);
		texture = Resources::Load<Texture>(L"TwoHand", L"..\\Resources\\Player\\Basic\\Attack\\TwoHand\\SkeletonKingJewelSword.png");
		tr = BelialSword->GetComponent<Transform>();
		tr->SetScale(Math::Vector2<float>(68.f, 144.f));
		BelialSword->AddComponent<SpriteRenderer>();
		BelialSword->GetComponent<SpriteRenderer>()->SetImg(texture);
		BelialSword->GetComponent<SpriteRenderer>()->SetAffectCamera(true);
		texture->Enabled(false);

		BelialSwordCollider = object::Instantiate<Weapon>(enums::eLayerType::Sword);
		weaponcol = BelialSwordCollider->AddComponent<Collider>();
		weaponcol->SetScale(Math::Vector2<float>(120.f, 120.f));
		weaponcol->SetType(Collider::eColliderType::Circle);
		weaponcol->enabled(false);
		BelialSwordCollider->SetDelayTime(0.1f);

		Gun = object::Instantiate<Weapon>(enums::eLayerType::UI);
		texture = Resources::Load<Texture>(L"GunLeft", L"..\\Resources\\Player\\Basic\\Attack\\Gun\\Left\\Revolver2.png");
		texture = Resources::Load<Texture>(L"GunRight", L"..\\Resources\\Player\\Basic\\Attack\\Gun\\Right\\Revolver2.png");		
		tr = Gun->GetComponent<Transform>();
		tr->SetScale(Math::Vector2<float>(64.f, 36.f));
		Gun->AddComponent<SpriteRenderer>();
		Gun->GetComponent<SpriteRenderer>()->SetImg(texture);
		Gun->GetComponent<SpriteRenderer>()->SetAffectCamera(true);
		texture->Enabled(false);
	}
}