#include "EHJailPrevBossScene.h"
#include "EHSceneManager.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHTexture.h"
#include "EHResources.h"
#include "EHPlayer.h"

namespace EH
{
	JailPrevBossScene::JailPrevBossScene()
	{
	}

	JailPrevBossScene::~JailPrevBossScene()
	{
	}

	void JailPrevBossScene::Initialize()
	{
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

		BackGround* JailBossPrevBackGround = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBossPrevBackGround->GetComponent<Transform>()->SetPos(Math::Vector2<float>(700.f,360.f));
		JailBossPrevBackGround->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1400.f,720.f));
		temp = Resources::Load<Texture>(L"JailBossPrevBackGround", L"..\\Resources\\Dungeon\\Belial\\BossPrev.png");
		JailBossPrevBackGround->GetComponent<SpriteRenderer>()->SetImg(temp);
		//JailBossPrevBackGround->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Torch1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Torch1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(252.f, 380.f));
		Torch1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		temp = Resources::Load<Texture>(L"Torch", L"..\\Resources\\Dungeon\\Belial\\Torch0.png");
		Torch1->GetComponent<SpriteRenderer>()->SetImg(temp);
		//Torch1->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Torch2 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Torch2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(704.f, 380.f));
		Torch2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		temp = Resources::Load<Texture>(L"Torch", L"..\\Resources\\Dungeon\\Belial\\Torch0.png");
		Torch2->GetComponent<SpriteRenderer>()->SetImg(temp);
		//Torch2->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Torch3 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Torch3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1160.f, 380.f));
		Torch3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		temp = Resources::Load<Texture>(L"Torch", L"..\\Resources\\Dungeon\\Belial\\Torch0.png");
		Torch3->GetComponent<SpriteRenderer>()->SetImg(temp);
		//Torch3->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Door = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Door->GetComponent<Transform>()->SetPos(Math::Vector2<float>(482.f, 398.f));
		Door->GetComponent<Transform>()->SetScale(Math::Vector2<float>(228.f, 260.f));
		temp = Resources::Load<Texture>(L"Door1", L"..\\Resources\\Dungeon\\Belial\\Door9.png");
		Door->GetComponent<SpriteRenderer>()->SetImg(temp);
		//Door->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* TortureTable1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		TortureTable1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(926.f, 490.f));
		TortureTable1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(180.f, 76.f));
		temp = Resources::Load<Texture>(L"TortureTable2", L"..\\Resources\\Dungeon\\Belial\\TortureTable1.png");
		TortureTable1->GetComponent<SpriteRenderer>()->SetImg(temp);
		//TortureTable1->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Skull1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Skull1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1086.f, 514.f));
		Skull1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(60.f, 28.f));
		temp = Resources::Load<Texture>(L"Skull2", L"..\\Resources\\Dungeon\\Belial\\Skull1.png");
		Skull1->GetComponent<SpriteRenderer>()->SetImg(temp);
		//Skull1->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(300.f, 630.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		temp = Resources::Load<Texture>(L"player", L"..\\Resources\\Player\\Basic\\Idle\\CharIdle0.png");
		player->GetComponent<SpriteRenderer>()->SetImg(temp);
	}

	void JailPrevBossScene::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			SceneManager::LoadScene(L"JailBossScene");
		}
		Scene::Update();
	}

	void JailPrevBossScene::Render(HDC hdc)
	{
		HBRUSH hNewBrush = (HBRUSH)CreateSolidBrush(RGB(51, 49, 67));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush);

		HPEN hNewPen = (HPEN)CreatePen(PS_SOLID, 1, RGB(51, 49, 67));
		HPEN hOldPen = (HPEN)SelectObject(hdc, hNewPen);

		Rectangle(hdc, -1, -1, 1280, 720);

		SelectObject(hdc, hOldBrush);
		SelectObject(hdc, hOldPen);

		DeleteObject(hNewBrush);
		DeleteObject(hNewPen);
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailPrevScene", 13);
	}
}