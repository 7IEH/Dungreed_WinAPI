#include "EHJailField8.h"
#include "EHBackGround.h"
#include "EHObject.h"
#include "EHResources.h"
#include "EHCamera.h"
#include "EHPlayer.h"
#include "EHCanvas.h"

namespace EH
{
	void JailField8::Initialize()
	{
		SetSize(Math::Vector2<float>(2752.f, 1088.f));
		BackGround* JailBG8 = object::Instantiate<BackGround>(enums::eLayerType::BackGround);
		JailBG8->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1376.f, 544.f));
		JailBG8->GetComponent<Transform>()->SetScale(Math::Vector2<float>(2752.f, 1088.f));
		Texture* texture = Resources::Load<Texture>(L"JailBG8", L"..\\Resources\\Dungeon\\JailBackGround\\8\\JailField8.bmp");
		JailBG8->GetComponent<SpriteRenderer>()->SetImg(texture);
		JailBG8->GetComponent<SpriteRenderer>()->SetAffectCamera(true);

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
	void JailField8::Update()
	{
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			Camera::SetLookAt(Math::Vector2<float>(640.f, 360.f));
			SceneManager::LoadScene(L"JailScene9");
		} 
		Scene::Update();
	}
	void JailField8::Render(HDC hdc)
	{
		Scene::Render(hdc);
		TextOut(hdc, 10, 10, L"JailScene8", 10);
	}
}