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
	
		Texture* texture = nullptr;
		// Player
		Player* player = object::Instantiate<Player>(enums::eLayerType::Player);
		player->GetComponent<Transform>()->SetPos(Math::Vector2<float>(420.f, 500.f));
		player->GetComponent<Transform>()->SetScale(Math::Vector2<float>(128.f, 128.f));

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