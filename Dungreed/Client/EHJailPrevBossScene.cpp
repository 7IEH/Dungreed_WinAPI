#include "EHJailPrevBossScene.h"
#include "EHSceneManager.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHTexture.h"
#include "EHResources.h"
#include "EHPlayer.h"
#include "EHCamera.h"
#include "EHCanvas.h"

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
		SetSize(Math::Vector2<float>(1400.f, 720.f));
		
		Texture* texture = nullptr;

		// UI Canvas
		Canvas* PlayerUICanvas = object::Instantiate<Canvas>(enums::eLayerType::UI);
		texture = Resources::Load<Texture>(L"HPBack", L"..\\Resources\\UI\\PlayerLifeBack.png");
		PlayerUICanvas->AddImageObject(L"HPBack", texture, false, Math::Vector2<float>(157.f, 42.f), Math::Vector2<float>(296.f, 64.f));

		texture = Resources::Load<Texture>(L"HP", L"..\\Resources\\UI\\PlayerLife.png");
		PlayerUICanvas->AddImageObject(L"HP", texture, false, Math::Vector2<float>(194.f, 42.f), Math::Vector2<float>(198.f, 56.f));

		texture = Resources::Load<Texture>(L"HPBase", L"..\\Resources\\UI\\PlayerLifeBase 1.png");
		PlayerUICanvas->AddImageObject(L"HPBase", texture, false, Math::Vector2<float>(157.f, 42.f), Math::Vector2<float>(296.f, 64.f));

		texture = Resources::Load<Texture>(L"DashBase", L"..\\Resources\\UI\\DashCountBase.png");
		PlayerUICanvas->AddImageObject(L"DashBase", texture, false, Math::Vector2<float>(135.f, 97.f), Math::Vector2<float>(252.f, 34.f));

		texture = Resources::Load<Texture>(L"CoinUI", L"..\\Resources\\UI\\Coin.png");
		PlayerUICanvas->AddImageObject(L"CoinUI", texture, false, Math::Vector2<float>(29.f, 657.f), Math::Vector2<float>(17.f, 14.f));

		texture = Resources::Load<Texture>(L"FoodUI", L"..\\Resources\\UI\\Food.png");
		PlayerUICanvas->AddImageObject(L"FoodUI", texture, false, Math::Vector2<float>(29.f, 690.f), Math::Vector2<float>(34.f, 28.f));

		texture = Resources::Load<Texture>(L"WeaponSlot", L"..\\Resources\\UI\\EquippedWeaponBase.png");
		PlayerUICanvas->AddImageObject(L"WeaponSlot", texture, false, Math::Vector2<float>(1210.f, 641.f), Math::Vector2<float>(140.f, 102.f));
		PlayerUICanvas->AddImageObject(L"WeaponSlot2", texture, false, Math::Vector2<float>(1190.f, 657.f), Math::Vector2<float>(140.f, 102.f));

		BackGround* JailBossPrevBackGround = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBossPrevBackGround->GetComponent<Transform>()->SetPos(Math::Vector2<float>(700.f,360.f));
		JailBossPrevBackGround->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1400.f,720.f));
		texture = Resources::Load<Texture>(L"JailBossPrevBackGround", L"..\\Resources\\Dungeon\\Belial\\BossPrev.bmp");
		JailBossPrevBackGround->GetComponent<SpriteRenderer>()->SetImg(texture);
		//JailBossPrevBackGround->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Torch1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Torch1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(252.f, 380.f));
		Torch1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		texture = Resources::Load<Texture>(L"Torch", L"..\\Resources\\Dungeon\\Belial\\Torch0.png");
		Torch1->GetComponent<SpriteRenderer>()->SetImg(texture);
		//Torch1->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Torch2 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Torch2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(704.f, 380.f));
		Torch2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		texture = Resources::Load<Texture>(L"Torch", L"..\\Resources\\Dungeon\\Belial\\Torch0.png");
		Torch2->GetComponent<SpriteRenderer>()->SetImg(texture);
		//Torch2->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Torch3 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Torch3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1160.f, 380.f));
		Torch3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		texture = Resources::Load<Texture>(L"Torch", L"..\\Resources\\Dungeon\\Belial\\Torch0.png");
		Torch3->GetComponent<SpriteRenderer>()->SetImg(texture);
		//Torch3->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Door = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Door->GetComponent<Transform>()->SetPos(Math::Vector2<float>(482.f, 398.f));
		Door->GetComponent<Transform>()->SetScale(Math::Vector2<float>(228.f, 260.f));
		texture = Resources::Load<Texture>(L"Door1", L"..\\Resources\\Dungeon\\Belial\\Door9.png");
		Door->GetComponent<SpriteRenderer>()->SetImg(texture);
		//Door->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* TortureTable1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		TortureTable1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(926.f, 490.f));
		TortureTable1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(180.f, 76.f));
		texture = Resources::Load<Texture>(L"TortureTable2", L"..\\Resources\\Dungeon\\Belial\\TortureTable1.png");
		TortureTable1->GetComponent<SpriteRenderer>()->SetImg(texture);
		//TortureTable1->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Skull1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Skull1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1086.f, 514.f));
		Skull1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(60.f, 28.f));
		texture = Resources::Load<Texture>(L"Skull2", L"..\\Resources\\Dungeon\\Belial\\Skull1.png");
		Skull1->GetComponent<SpriteRenderer>()->SetImg(texture);
		//Skull1->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Banshee1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Banshee1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(300.f, 400.f));
		Banshee1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 88.f));
		texture = Resources::Load<Texture>(L"BansheeIdle", L"..\\Resources\\Enemy\\JailField\\Banshee\\Idle\\BansheeIdleSheet.bmp");
		Banshee1->AddComponent<Animator>();
		Banshee1->GetComponent<Animator>()->CreateAnimation(L"BansheeIdle", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 22.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		Banshee1->GetComponent<Animator>()->PlayAnimation(L"BansheeIdle", true);
		Banshee1->GetComponent<Animator>()->SetAffectedCamera(true);

		BackGround* Bat1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		Bat1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(400.f, 400.f));
		Bat1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		texture = Resources::Load<Texture>(L"Bat", L"..\\Resources\\Enemy\\JailField\\Bat\\Bat\\Idle\\BatSheet.bmp");
		Bat1->AddComponent<Animator>();
		Bat1->GetComponent<Animator>()->CreateAnimation(L"Bat", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		Bat1->GetComponent<Animator>()->PlayAnimation(L"Bat", true);
		Bat1->GetComponent<Animator>()->SetAffectedCamera(true);

		BackGround* RedBat1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		RedBat1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(550.f, 400.f));
		RedBat1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		texture = Resources::Load<Texture>(L"RedBat", L"..\\Resources\\Enemy\\JailField\\Bat\\BatRed\\Idle\\RedBatSheet.bmp");
		RedBat1->AddComponent<Animator>();
		RedBat1->GetComponent<Animator>()->CreateAnimation(L"RedBat", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		RedBat1->GetComponent<Animator>()->PlayAnimation(L"RedBat", true);
		RedBat1->GetComponent<Animator>()->SetAffectedCamera(true);

		BackGround* BombBat1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		BombBat1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(650.f, 400.f));
		BombBat1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(76.f, 48.f));
		texture = Resources::Load<Texture>(L"BombBat", L"..\\Resources\\Enemy\\JailField\\Bat\\BombBat\\Idle\\BombBatSheet.bmp");
		BombBat1->AddComponent<Animator>();
		BombBat1->GetComponent<Animator>()->CreateAnimation(L"BombBat", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(19.f, 12.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		BombBat1->GetComponent<Animator>()->PlayAnimation(L"BombBat", true);
		BombBat1->GetComponent<Animator>()->SetAffectedCamera(true);

		BackGround* GiantBat1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		GiantBat1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(800.f, 400.f));
		GiantBat1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(256.f, 256.f));
		texture = Resources::Load<Texture>(L"GiantBat", L"..\\Resources\\Enemy\\JailField\\Bat\\GiantBat\\Idle\\GiantBatSheet.bmp");
		GiantBat1->AddComponent<Animator>();
		GiantBat1->GetComponent<Animator>()->CreateAnimation(L"GiantBat", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(64.f, 64.f), Math::Vector2<float>(0.f, 0.f), 7, 0.1f);
		GiantBat1->GetComponent<Animator>()->PlayAnimation(L"GiantBat", true);
		GiantBat1->GetComponent<Animator>()->SetAffectedCamera(true);

		BackGround* RedGiantBat1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		RedGiantBat1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(950.f, 400.f));
		RedGiantBat1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(256.f, 256.f));
		texture = Resources::Load<Texture>(L"RedGiantBat", L"..\\Resources\\Enemy\\JailField\\Bat\\RedGiantBat\\Idle\\RedBatSheet.bmp");
		RedGiantBat1->AddComponent<Animator>();
		RedGiantBat1->GetComponent<Animator>()->CreateAnimation(L"RedGiantBat", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(64.f, 64.f), Math::Vector2<float>(0.f, 0.f), 7, 0.1f);
		RedGiantBat1->GetComponent<Animator>()->PlayAnimation(L"RedGiantBat", true);
		RedGiantBat1->GetComponent<Animator>()->SetAffectedCamera(true);

		BackGround* LittleGhost1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		LittleGhost1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(300.f, 300.f));
		LittleGhost1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 80.f));
		texture = Resources::Load<Texture>(L"LittleGhost", L"..\\Resources\\Enemy\\JailField\\Ghost\\LittleGhost\\Idle\\LittleGhostIdleSheet.bmp");
		LittleGhost1->AddComponent<Animator>();
		LittleGhost1->GetComponent<Animator>()->CreateAnimation(L"LittleGhost", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 20.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		LittleGhost1->GetComponent<Animator>()->PlayAnimation(L"LittleGhost", true);
		LittleGhost1->GetComponent<Animator>()->SetAffectedCamera(true);

		BackGround* BigWhiteSkel1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		BigWhiteSkel1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(450.f, 300.f));
		BigWhiteSkel1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(132.f, 120.f));
		texture = Resources::Load<Texture>(L"BigWhiteSkel", L"..\\Resources\\Enemy\\JailField\\Skell\\BigWhiteSkel\\Idle\\BigWhiteSkelIdleSheet.bmp");
		BigWhiteSkel1->AddComponent<Animator>();
		BigWhiteSkel1->GetComponent<Animator>()->CreateAnimation(L"BigWhiteSkel", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(33.f, 30.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		BigWhiteSkel1->GetComponent<Animator>()->PlayAnimation(L"BigWhiteSkel", true);
		BigWhiteSkel1->GetComponent<Animator>()->SetAffectedCamera(true);

		BackGround* SkelDog1 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		SkelDog1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(650.f, 300.f));
		SkelDog1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(80.f, 72.f));
		texture = Resources::Load<Texture>(L"SkelDog", L"..\\Resources\\Enemy\\JailField\\Skell\\SkelDog\\Idle\\SkelDogIdleSheet.bmp");
		SkelDog1->AddComponent<Animator>();
		SkelDog1->GetComponent<Animator>()->CreateAnimation(L"SkelDog", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(20.f, 18.f), Math::Vector2<float>(0.f, 0.f), 5, 0.1f);
		SkelDog1->GetComponent<Animator>()->PlayAnimation(L"SkelDog", true);
		SkelDog1->GetComponent<Animator>()->SetAffectedCamera(true);
	}

	void JailPrevBossScene::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailBossScene")->GetBGM()->Play(true);
			Camera::SetTarget(nullptr);
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