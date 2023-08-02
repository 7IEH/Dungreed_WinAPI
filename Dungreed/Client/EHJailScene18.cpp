#include "EHJailScene18.h"
#include "EHSceneManager.h"
#include "EHBackGround.h"
#include "EHResources.h"
#include "EHObject.h"
#include "EHPlayer.h"
#include "EHCamera.h"
#include "EHEnemy.h"
#include "EHCollisionManager.h"
#include "EHCanvas.h"
#include "EHObjdata.h"

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
	
		// Playre UI
		Canvas* PlayerUICanvas = object::Instantiate<Canvas>(enums::eLayerType::UI);
		Texture* texture = Resources::Load<Texture>(L"HPBack", L"..\\Resources\\UI\\PlayerLifeBack.png");
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

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		player->SetCanvas(PlayerUICanvas);

		BackGround* JailSubBG18 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailSubBG18->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		JailSubBG18->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
	    texture = Resources::Load<Texture>(L"JailSubBG", L"..\\Resources\\Dungeon\\JailBackGround\\4\\SubBG.bmp");
		JailSubBG18->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailSubBG18->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* JailBG18 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG18->GetComponent<Transform>()->SetPos(Math::Vector2<float>(768.f, 448.f));
		JailBG18->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1536.f, 896.f));
		texture = Resources::Load<Texture>(L"JailBG18", L"..\\Resources\\Dungeon\\JailBackGround\\18\\JailField18.bmp");
		JailBG18->GetComponent<SpriteRenderer>()->SetImg(texture);

		Enemy* testenemy = object::Instantiate<Enemy>(enums::eLayerType::Enemy);
		testenemy->GetComponent<Transform>()->SetPos(Math::Vector2<float>(400.f, 400.f));
		testenemy->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		texture = Resources::Load<Texture>(L"Bat", L"..\\Resources\\Enemy\\JailField\\Bat\\Bat\\Idle\\BatSheet.bmp");
		testenemy->AddComponent<Animator>();
		testenemy->GetComponent<Animator>()->CreateAnimation(L"Bat", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		testenemy->GetComponent<Animator>()->PlayAnimation(L"Bat", true);
		testenemy->GetComponent<Animator>()->SetAffectedCamera(true);
		testenemy->AddComponent<Collider>();
		testenemy->GetComponent<Collider>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		testenemy->GetComponent<Collider>()->SetAffectedCamera(true);

		Enemy* testenemy2 = object::Instantiate<Enemy>(enums::eLayerType::Enemy);
		testenemy2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(800.f, 400.f));
		testenemy2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		texture = Resources::Load<Texture>(L"Bat", L"..\\Resources\\Enemy\\JailField\\Bat\\Bat\\Idle\\BatSheet.bmp");
		testenemy2->AddComponent<Animator>();
		testenemy2->GetComponent<Animator>()->CreateAnimation(L"Bat", texture, Math::Vector2<float>(0.f, 0.f), Math::Vector2<float>(32.f, 32.f), Math::Vector2<float>(0.f, 0.f), 6, 0.1f);
		testenemy2->GetComponent<Animator>()->PlayAnimation(L"Bat", true);
		testenemy2->GetComponent<Animator>()->SetAffectedCamera(true);
		testenemy2->AddComponent<Collider>();
		testenemy2->GetComponent<Collider>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		testenemy2->GetComponent<Collider>()->SetAffectedCamera(true);

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