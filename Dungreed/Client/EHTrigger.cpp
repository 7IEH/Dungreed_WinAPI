#include "EHTrigger.h"
#include "EHPlayer.h"
#include "EHSceneManager.h"
#include "EHCamera.h"
#include "EHDungeonManager.h"
#include "EHResources.h"
#include "EHObject.h"
#include "EHCollisionManager.h"
#include "EHObjdata.h"
#include "EHBullet.h"
#include "EHEquipedEffect.h"

namespace EH
{
	Trigger::Trigger()
		:
		  mType(eTriggertype::None)
		, mScenename(L"")
		, mCheckTime(0.f)
		, mDelayTime(0.f)
		, mCheck1(0)
		, mSetKey(eKeyCode::END)
		, mCheck2(0)
	{
		mDungeoneat = Resources::Load<Sound>(L"Dungeonout", L"..\\Resources\\Sound\\Structure\\DungeonOut.wav");
		mOpend = Resources::Load<Sound>(L"opend", L"..\\Resources\\Sound\\Item\\Chest2.wav");
		mNewItem = Resources::Load<Sound>(L"NewItem", L"..\\Resources\\Sound\\Item\\newItems.wav");
	}

	Trigger::~Trigger()
	{
	}

	void Trigger::Initialize()
	{
	}

	void Trigger::Update()
	{
		GameObject::Update();
		if (mScenename == L"JailScene1")
		{
			mDelayTime = 4.f;
		}
		else
		{
			mDelayTime = 0.f;
		}
	}

	void Trigger::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Trigger::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			switch (mType)
			{
			case EH::Trigger::eTriggertype::Scenechange:
				SceneChange();
				break;
			case EH::Trigger::eTriggertype::Tresure:
				break;
			case EH::Trigger::eTriggertype::None:
				break;
			default:
				break;
			}
		}
	}

	void Trigger::OnCollisionStay(Collider* other)
	{
		
		if (mType == eTriggertype::Tresure)
		{
			if (Input::Getkey(eKeyCode::G).state == eKeyState::DOWN && mCheck2 == 0)
			{
				mOpend->Play(false);
				GetComponent<Animator>()->PlayAnimation(L"OpenTresure", false);

				Texture* texture = nullptr;
				if (mWeaponname == L"Gun")
				{
					texture = Resources::Load<Texture>(L"GunItem", L"..\\Resources\\Player\\Basic\\Attack\\Gun\\Right\\Revolver2.png");
				}
				else if (mWeaponname == L"Wand")
				{
					texture = Resources::Load<Texture>(L"WandItem", L"..\\Resources\\Player\\Basic\\Attack\\LalaWand\\Lala'sMagicWand.png");
				}
				else if (mWeaponname == L"TwoHand")
				{
					texture = Resources::Load<Texture>(L"TwoHandItem", L"..\\Resources\\Player\\Basic\\Attack\\TwoHand\\SkeletonKingJewelSword.png");
				}

				Trigger* weapon = object::Instantiate<Trigger>(enums::eLayerType::Trigger);
				weapon->GetComponent<Transform>()->SetPos(Math::Vector2<float>(688.f, 300.f));
				weapon->GetComponent<Transform>()->SetScale(Math::Vector2<float>(84.f, 64.f));
				SpriteRenderer* sr = weapon->AddComponent<SpriteRenderer>();
				sr->SetImg(texture);
				weapon->AddComponent<Collider>();
				weapon->AddComponent<Rigidbody>();
				weapon->GetComponent<Collider>()->SetScale(Math::Vector2<float>(84.f, 64.f));
				weapon->SetType(Trigger::eTriggertype::Weapon);
				weapon->SetWeaponName(mWeaponname);
				mCheck2 = 1;
			}
		}

		if (mType == eTriggertype::Weapon)
		{
			if (Input::Getkey(eKeyCode::F).state == eKeyState::DOWN && mCheck2 == 0)
			{
				mNewItem->Play(false);
				std::wstring inventory[3][5] = {};
				Objdata::GetInventory(inventory);

				if (mWeaponname == L"Gun")
				{
					UINT check1 = 0;
					for (int y = 0;y < 3;y++)
					{
						for (int x = 0;x < 5;x++)
						{
							if (inventory[y][x] == L"")
							{
								inventory[y][x] = mWeaponname;
								check1++;
								mCheck2 = 1;
								break;
							}
						}
						if (check1 == 1)
							break;
					}
					EquipedEffect* back = object::Instantiate<EquipedEffect>(enums::eLayerType::Inventory);
					Transform* backtr = back->GetComponent<Transform>();
					SpriteRenderer* backsr = back->AddComponent<SpriteRenderer>();
					Texture* texture = Resources::Load<Texture>(L"euipedback", L"..\\Resources\\UI\\ItemFont\\ItemEquip.bmp");
					backsr->SetImg(texture);
					backtr->SetPos(Math::Vector2<float>(640.f, 630.f));
					backtr->SetScale(Math::Vector2<float>(330.f, 110.f));
					back->SetDeleteTime(3.f);
					backsr->SetAffectCamera(false);

					EquipedEffect* image1 = object::Instantiate<EquipedEffect>(enums::eLayerType::Inventory);
					backtr = image1->GetComponent<Transform>();
					backsr = image1->AddComponent<SpriteRenderer>();
					texture = Resources::Load<Texture>(L"equipfont", L"..\\Resources\\UI\\ItemFont\\ItemEquipedFont.bmp");
					backsr->SetImg(texture);
					backtr->SetPos(Math::Vector2<float>(640.f, 600.f));
					backtr->SetScale(Math::Vector2<float>(112.f, 24.f));
					image1->SetDeleteTime(3.f);
					backsr->SetAffectCamera(false);

					EquipedEffect* image2 = object::Instantiate<EquipedEffect>(enums::eLayerType::Inventory);
					backtr = image2->GetComponent<Transform>();
					backsr = image2->AddComponent<SpriteRenderer>();
					texture = Resources::Load<Texture>(L"equipgunfont", L"..\\Resources\\UI\\ItemFont\\Gunalphabet.bmp");
					backsr->SetImg(texture);
					backtr->SetPos(Math::Vector2<float>(640.f, 630.f));
					backtr->SetScale(Math::Vector2<float>(138.f, 24.f));
					image2->SetDeleteTime(3.f);
					backsr->SetAffectCamera(false);

					EquipedEffect* image3 = object::Instantiate<EquipedEffect>(enums::eLayerType::Inventory);
					backtr = image3->GetComponent<Transform>();
					backsr = image3->AddComponent<SpriteRenderer>();
					texture = Resources::Load<Texture>(L"equipgunimage", L"..\\Resources\\Player\\Basic\\Attack\\Gun\\Right\\Revolver2.png");
					backsr->SetImg(texture);
					backtr->SetPos(Math::Vector2<float>(530.f, 630.f));
					backtr->SetScale(Math::Vector2<float>(64.f, 36.f));
					image3->SetDeleteTime(3.f);
					backsr->SetAffectCamera(false);
				}
				else if (mWeaponname == L"Wand")
				{
					UINT check1 = 0;
					for (int y = 0;y < 3;y++)
					{
						for (int x = 0;x < 5;x++)
						{
							if (inventory[y][x] == L"")
							{
								inventory[y][x] = mWeaponname;
								check1++;
								mCheck2 = 1;
								break;
							}
						}
						if (check1 == 1)
							break;
					}
					EquipedEffect* back = object::Instantiate<EquipedEffect>(enums::eLayerType::Inventory);
					Transform* backtr = back->GetComponent<Transform>();
					SpriteRenderer* backsr = back->AddComponent<SpriteRenderer>();
					Texture* texture = Resources::Load<Texture>(L"euipedback", L"..\\Resources\\UI\\ItemFont\\ItemEquip.bmp");
					backsr->SetImg(texture);
					backtr->SetPos(Math::Vector2<float>(640.f, 630.f));
					backtr->SetScale(Math::Vector2<float>(330.f, 110.f));
					back->SetDeleteTime(3.f);
					backsr->SetAffectCamera(false);

					EquipedEffect* image1 = object::Instantiate<EquipedEffect>(enums::eLayerType::Inventory);
					backtr = image1->GetComponent<Transform>();
					backsr = image1->AddComponent<SpriteRenderer>();
					texture = Resources::Load<Texture>(L"equipfont", L"..\\Resources\\UI\\ItemFont\\ItemEquipedFont.bmp");
					backsr->SetImg(texture);
					backtr->SetPos(Math::Vector2<float>(640.f, 600.f));
					backtr->SetScale(Math::Vector2<float>(112.f, 24.f));
					image1->SetDeleteTime(3.f);
					backsr->SetAffectCamera(false);

					EquipedEffect* image2 = object::Instantiate<EquipedEffect>(enums::eLayerType::Inventory);
					backtr = image2->GetComponent<Transform>();
					backsr = image2->AddComponent<SpriteRenderer>();
					texture = Resources::Load<Texture>(L"equipwandfont", L"..\\Resources\\UI\\ItemFont\\Wandalphabet.bmp");
					backsr->SetImg(texture);
					backtr->SetPos(Math::Vector2<float>(640.f, 630.f));
					backtr->SetScale(Math::Vector2<float>(136.f, 22.f));
					image2->SetDeleteTime(3.f);
					backsr->SetAffectCamera(false);

					EquipedEffect* image3 = object::Instantiate<EquipedEffect>(enums::eLayerType::Inventory);
					backtr = image3->GetComponent<Transform>();
					backsr = image3->AddComponent<SpriteRenderer>();
					texture = Resources::Load<Texture>(L"equipwandimage", L"..\\Resources\\Player\\Basic\\Attack\\LalaWand\\Lala'sMagicWand.png");
					backsr->SetImg(texture);
					backtr->SetPos(Math::Vector2<float>(530.f, 630.f));
					backtr->SetScale(Math::Vector2<float>(52.f, 52.f));
					image3->SetDeleteTime(3.f);
					backsr->SetAffectCamera(false);
				}
				else if (mWeaponname == L"TwoHand")
				{
					UINT check1 = 0;
					for (int y = 0;y < 3;y++)
					{
						for (int x = 0;x < 5;x++)
						{
							if (inventory[y][x] == L"")
							{
								inventory[y][x] = mWeaponname;
								check1++;
								mCheck2 = 1;
								break;
							}
						}
						if (check1 == 1)
							break;
					}
					EquipedEffect* back = object::Instantiate<EquipedEffect>(enums::eLayerType::Inventory);
					Transform* backtr = back->GetComponent<Transform>();
					SpriteRenderer* backsr = back->AddComponent<SpriteRenderer>();
					Texture* texture = Resources::Load<Texture>(L"euipedback", L"..\\Resources\\UI\\ItemFont\\ItemEquip.bmp");
					backsr->SetImg(texture);
					backtr->SetPos(Math::Vector2<float>(640.f, 630.f));
					backtr->SetScale(Math::Vector2<float>(330.f, 110.f));
					back->SetDeleteTime(3.f);
					backsr->SetAffectCamera(false);

					EquipedEffect* image1 = object::Instantiate<EquipedEffect>(enums::eLayerType::Inventory);
					backtr = image1->GetComponent<Transform>();
					backsr = image1->AddComponent<SpriteRenderer>();
					texture = Resources::Load<Texture>(L"equipfont", L"..\\Resources\\UI\\ItemFont\\ItemEquipedFont.bmp");
					backsr->SetImg(texture);
					backtr->SetPos(Math::Vector2<float>(640.f, 600.f));
					backtr->SetScale(Math::Vector2<float>(112.f, 24.f));
					image1->SetDeleteTime(3.f);
					backsr->SetAffectCamera(false);

					EquipedEffect* image2 = object::Instantiate<EquipedEffect>(enums::eLayerType::Inventory);
					backtr = image2->GetComponent<Transform>();
					backsr = image2->AddComponent<SpriteRenderer>();
					texture = Resources::Load<Texture>(L"equiptwohandfont", L"..\\Resources\\UI\\ItemFont\\twohandalphabet.bmp");
					backsr->SetImg(texture);
					backtr->SetPos(Math::Vector2<float>(640.f, 630.f));
					backtr->SetScale(Math::Vector2<float>(134.f, 24.f));
					image2->SetDeleteTime(3.f);
					backsr->SetAffectCamera(false);

					EquipedEffect* image3 = object::Instantiate<EquipedEffect>(enums::eLayerType::Inventory);
					backtr = image3->GetComponent<Transform>();
					backsr = image3->AddComponent<SpriteRenderer>();
					texture = Resources::Load<Texture>(L"equipedtwohandsimage", L"..\\Resources\\Player\\Basic\\Attack\\TwoHand\\SkeletonKingJewelSword.png");
					backsr->SetImg(texture);
					backtr->SetPos(Math::Vector2<float>(530.f, 630.f));
					backtr->SetScale(Math::Vector2<float>(68.f, 144.f));
					image3->SetDeleteTime(3.f);
					backsr->SetAffectCamera(false);

				}
				Objdata::SetInventory(inventory);
				Destroy(this);
			}
		}

		if (mType == eTriggertype::Scenechange)
		{
			if (SceneManager::GetCurScene()->GetLayer(enums::eLayerType::Enemy).GetObjects().size() == 0)
			{

				if (mSetKey != eKeyCode::END)
				{
					if (Input::Getkey(mSetKey).state == eKeyState::DOWN)
					{
						if (SceneManager::GetCurScene()->GetBGM() != nullptr)
							SceneManager::GetCurScene()->GetBGM()->Stop(true);

						Scene* mCurScene = SceneManager::LoadScene(mScenename);
						if (mCurScene != nullptr)
						{
							if (mCurScene->GetBGM() != nullptr)
								mCurScene->GetBGM()->Play(true);

							if (mCurScene->GetPlayer() != nullptr)
								Camera::SetTarget(mCurScene->GetPlayer());
						}
					}
				}
			}

			Player* player1 = dynamic_cast<Player*>(other->GetOwner());
			if (player1 != nullptr)
			{
				if (mScenename == L"JailScene1" && SceneManager::GetCurScene()->GetName() == L"TownScene")
				{
					mCheckTime += Time::GetDeltaTime();

					if (mDelayTime / 4.f < mCheckTime && mCheck1 == 0)
					{
						SceneManager::GetCurScene()->GetPlayer()->GetComponent<Animator>()->PlayAnimation(L"Trans", false);
						SceneManager::GetCurScene()->GetPlayer()->SetTrans(true);

						mCheck1++;
					}

					if (mDelayTime < mCheckTime)
					{
						Scene* mCurScene = SceneManager::LoadScene(mScenename);
						if (mCurScene != nullptr)
						{
							if (mCurScene->GetBGM() != nullptr)
								mCurScene->GetBGM()->Play(true);

							if (mCurScene->GetPlayer() != nullptr)
								Camera::SetTarget(mCurScene->GetPlayer());
						}
						mCheckTime = 0.f;
						mCheck1 = 0;
					}
					else
					{
						Player* player = dynamic_cast<Player*>(other->GetOwner());
						Transform* playertr = player->GetComponent<Transform>();
						Transform* duntr = mDungeoneater->GetComponent<Transform>();
						Animator* ani = mDungeoneater->GetComponent<Animator>();
						duntr->SetPos(Math::Vector2<float>(playertr->Getpos().x, 1127.f));
						ani->PlayAnimation(L"Dungeoneat", false);
					}
				}
			}
		}
	}

	void Trigger::OnCollisionExit(Collider* other)
	{
	}

	void Trigger::SceneChange()
	{
		if (SceneManager::GetCurScene()->GetBGM() != nullptr)
			SceneManager::GetCurScene()->GetBGM()->Stop(true);

		if (mScenename == L"JailScene1" && SceneManager::GetCurScene()->GetName() == L"TownScene")
		{
			mDungeoneat->Play(false);
			return;
		}
		else if (mSetKey != eKeyCode::END)
		{
			return;
		}
		else
		{
			SceneManager::GetCurScene()->GetPlayer()->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
			SceneManager::GetCurScene()->GetPlayer()->SetState(eAnimationState::Idle);

			Scene* mCurScene = SceneManager::LoadScene(mScenename);
			if (mCurScene != nullptr)
			{
				if (mCurScene->GetBGM() != nullptr)
					mCurScene->GetBGM()->Play(true);

				if (mCurScene->GetPlayer() != nullptr)
					Camera::SetTarget(mCurScene->GetPlayer());
			}
		}
	}

	void Trigger::Tresure()
	{
		return;
	}
}