#include "EHJailScene11.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"
#include "EHPlayer.h"
#include "EHCanvas.h"

namespace EH
{
	void JailScene11::Initialize()
	{
		SetSize(Math::Vector2<float>(1600.f, 768.f));
		BackGround* JailBG11 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG11->GetComponent<Transform>()->SetPos(Math::Vector2<float>(800.f, 384.f));
		JailBG11->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1600.f, 768.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG11", L"..\\Resources\\Dungeon\\JailBackGround\\11\\JailField11.bmp");
		JailBG11->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG11->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

		// Playre UI
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

		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));
		player->SetCanvas(PlayerUICanvas);

		// SceneChanger Player
		SetPlayer(player);
	}

	void JailScene11::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene12");
		}
		Scene::Update();
	}

	void JailScene11::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene11", 11);
	}
}