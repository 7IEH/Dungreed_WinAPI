#include "EHJailScene18.h"
#include "EHSceneManager.h"
#include "EHBackGround.h"
#include "EHResources.h"
#include "EHObject.h"
#include "EHPlayer.h"
#include "EHCamera.h"
#include "EHEnemy.h"
#include "EHCollisionManager.h"

namespace EH
{
	JailScene18::JailScene18()
	{
	}

	JailScene18::~JailScene18()
	{
	}

	void JailScene18::Initialize()
	{
		SetSize(Math::Vector2<float>(1536.f, 896.f));
		// HP
		BackGround* HPBack = object::Instantiate<BackGround>(enums::eLayerType::UI);
		HPBack->GetComponent<Transform>()->SetPos(Math::Vector2<float>(157.f, 42.f));
		HPBack->GetComponent<Transform>()->SetScale(Math::Vector2<float>(296.f, 64.f));
		Texture* temp = Resources::Load<Texture>(L"HPBack", L"..\\Resources\\UI\\PlayerLifeBack.png");
		HPBack->GetComponent<SpriteRenderer>()->SetImg(temp);
		HPBack->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* HPBase = object::Instantiate<BackGround>(enums::eLayerType::UI);
		HPBase->GetComponent<Transform>()->SetPos(Math::Vector2<float>(157.f, 42.f));
		HPBase->GetComponent<Transform>()->SetScale(Math::Vector2<float>(296.f, 64.f));
		temp = Resources::Load<Texture>(L"HPBase", L"..\\Resources\\UI\\PlayerLifeBase 1.png");
		HPBase->GetComponent<SpriteRenderer>()->SetImg(temp);
		HPBase->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// DASH
		BackGround* DashBase = object::Instantiate<BackGround>(enums::eLayerType::UI);
		DashBase->GetComponent<Transform>()->SetPos(Math::Vector2<float>(135.f, 97.f));
		DashBase->GetComponent<Transform>()->SetScale(Math::Vector2<float>(252.f, 34.f));
		temp = Resources::Load<Texture>(L"DashBase", L"..\\Resources\\UI\\DashCountBase.png");
		DashBase->GetComponent<SpriteRenderer>()->SetImg(temp);
		DashBase->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// COIN
		BackGround* Coin = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Coin->GetComponent<Transform>()->SetPos(Math::Vector2<float>(29.f, 657.f));
		Coin->GetComponent<Transform>()->SetScale(Math::Vector2<float>(17.f, 14.f));
		temp = Resources::Load<Texture>(L"CoinUI", L"..\\Resources\\UI\\Coin.png");
		Coin->GetComponent<SpriteRenderer>()->SetImg(temp);
		Coin->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// FOOD
		BackGround* Food = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Food->GetComponent<Transform>()->SetPos(Math::Vector2<float>(29.f, 690.f));
		Food->GetComponent<Transform>()->SetScale(Math::Vector2<float>(34.f, 28.f));
		temp = Resources::Load<Texture>(L"FoodUI", L"..\\Resources\\UI\\Food.png");
		Food->GetComponent<SpriteRenderer>()->SetImg(temp);
		Food->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// Weapon Swap
		BackGround* WeaponSlot = object::Instantiate<BackGround>(enums::eLayerType::UI);
		WeaponSlot->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1210.f, 641.f));
		WeaponSlot->GetComponent<Transform>()->SetScale(Math::Vector2<float>(140.f, 102.f));
		temp = Resources::Load<Texture>(L"WeaponSlot", L"..\\Resources\\UI\\EquippedWeaponBase.png");
		WeaponSlot->GetComponent<SpriteRenderer>()->SetImg(temp);
		WeaponSlot->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* WeaponSlot2 = object::Instantiate<BackGround>(enums::eLayerType::UI);
		WeaponSlot2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1190.f, 657.f));
		WeaponSlot2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(140.f, 102.f));
		temp = Resources::Load<Texture>(L"WeaponSlot", L"..\\Resources\\UI\\EquippedWeaponBase.png");
		WeaponSlot2->GetComponent<SpriteRenderer>()->SetImg(temp);
		WeaponSlot2->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Minimap = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Minimap->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1105.f, 58.f));
		Minimap->GetComponent<Transform>()->SetScale(Math::Vector2<float>(350.f, 85.f));
		Minimap->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailSubBG18 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailSubBG18->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		JailSubBG18->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		Texture* texture = Resources::Load<Texture>(L"JailSubBG", L"..\\Resources\\Dungeon\\JailBackGround\\4\\SubBG.bmp");
		JailSubBG18->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailSubBG18->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailBG18 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG18->GetComponent<Transform>()->SetPos(Math::Vector2<float>(768.f, 448.f));
		JailBG18->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1536.f, 896.f));
		temp = Resources::Load<Texture>(L"JailBG18", L"..\\Resources\\Dungeon\\JailBackGround\\18\\JailField18.bmp");
		JailBG18->GetComponent<SpriteRenderer>()->SetImg(temp);

		Enemy* testenemy = object::Instantiate<Enemy>(enums::eLayerType::Enemy);
		testenemy->GetComponent<Transform>()->SetPos(Math::Vector2<float>(400.f, 400.f));
		testenemy->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		temp = Resources::Load<Texture>(L"Bat", L"..\\Resources\\Enemy\\JailField\\Bat\\Bat\\Idle\\BatSheet.bmp");
		testenemy->AddComponent<Animator>();
		testenemy->GetComponent<Animator>()->CreateAnimation(L"Bat", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		testenemy->GetComponent<Animator>()->PlayAnimation(L"Bat", true);
		testenemy->GetComponent<Animator>()->SetAffectedCamera(true);
		testenemy->AddComponent<Collider>();
		testenemy->GetComponent<Collider>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		testenemy->GetComponent<Collider>()->SetAffectedCamera(true);

		Enemy* testenemy2 = object::Instantiate<Enemy>(enums::eLayerType::Enemy);
		testenemy2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(800.f, 400.f));
		testenemy2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		temp = Resources::Load<Texture>(L"Bat", L"..\\Resources\\Enemy\\JailField\\Bat\\Bat\\Idle\\BatSheet.bmp");
		testenemy2->AddComponent<Animator>();
		testenemy2->GetComponent<Animator>()->CreateAnimation(L"Bat", temp, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		testenemy2->GetComponent<Animator>()->PlayAnimation(L"Bat", true);
		testenemy2->GetComponent<Animator>()->SetAffectedCamera(true);
		testenemy2->AddComponent<Collider>();
		testenemy2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		testenemy2->GetComponent<Collider>()->SetAffectedCamera(true);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailScene18::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailPrevBossScene");
		}
		Scene::Update();
	}

	void JailScene18::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene18", 11);
	}

}