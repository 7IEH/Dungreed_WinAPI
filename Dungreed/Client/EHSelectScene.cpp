#include "EHSelectScene.h"
#include "EHObject.h"
#include "EHTexture.h"
#include "EHResources.h"
#include "EHBackGround.h"

namespace EH
{
    SelectScene::SelectScene()
    {
    }

    SelectScene::~SelectScene()
    {
    }

    void SelectScene::Initialize()
    {
		Texture* temp = nullptr;
		// Back
		BackGround* Back = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Back->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 360.f));
		Back->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		temp = Resources::Load<Texture>(L"SelectBackImage", L"..\\Resources\\SelectScene\\Back.png");
		Back->GetComponent<SpriteRenderer>()->SetImg(temp);
		Back->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Slot1 = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Slot1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(240.f, 390.f));
		Slot1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(380.f, 570.f));
		temp = Resources::Load<Texture>(L"Slot", L"..\\Resources\\SelectScene\\SlotBase.png");
		Slot1->GetComponent<SpriteRenderer>()->SetImg(temp);
		Slot1->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Slot2 = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Slot2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(640.f, 390.f));
		Slot2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(380.f, 570.f));
		temp = Resources::Load<Texture>(L"Slot", L"..\\Resources\\SelectScene\\SlotBase.png");
		Slot2->GetComponent<SpriteRenderer>()->SetImg(temp);
		Slot2->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Slot3 = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Slot3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1040.f, 390.f));
		Slot3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(380.f, 570.f));
		temp = Resources::Load<Texture>(L"Slot", L"..\\Resources\\SelectScene\\SlotBase.png");
		Slot3->GetComponent<SpriteRenderer>()->SetImg(temp);
		Slot3->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Slot1Text = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Slot1Text->GetComponent<Transform>()->SetPos(Math::Vector2<float>(242.f, 173.f));
		Slot1Text->GetComponent<Transform>()->SetScale(Math::Vector2<float>(140.f, 46.f));
		temp = Resources::Load<Texture>(L"SlotText1", L"..\\Resources\\SelectScene\\SlotText1.EN.png");
		Slot1Text->GetComponent<SpriteRenderer>()->SetImg(temp);
		Slot1Text->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Slot2Text = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Slot2Text->GetComponent<Transform>()->SetPos(Math::Vector2<float>(642.f, 173.f));
		Slot2Text->GetComponent<Transform>()->SetScale(Math::Vector2<float>(140.f, 46.f));
		temp = Resources::Load<Texture>(L"SlotText2", L"..\\Resources\\SelectScene\\SlotText2.EN.png");
		Slot2Text->GetComponent<SpriteRenderer>()->SetImg(temp);
		Slot2Text->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Slot3Text = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Slot3Text->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1042.f, 173.f));
		Slot3Text->GetComponent<Transform>()->SetScale(Math::Vector2<float>(140.f, 46.f));
		temp = Resources::Load<Texture>(L"SlotText3", L"..\\Resources\\SelectScene\\SlotText3.EN.png");
		Slot3Text->GetComponent<SpriteRenderer>()->SetImg(temp);
		Slot3Text->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Slot1Delete = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Slot1Delete->GetComponent<Transform>()->SetPos(Math::Vector2<float>(239.5f, 613.5f));
		Slot1Delete->GetComponent<Transform>()->SetScale(Math::Vector2<float>(247.f, 67.f));
		temp = Resources::Load<Texture>(L"SlotDelete", L"..\\Resources\\SelectScene\\SlotDeleteButton.png");
		Slot1Delete->GetComponent<SpriteRenderer>()->SetImg(temp);
		Slot1Delete->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Slot2Delete = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Slot2Delete->GetComponent<Transform>()->SetPos(Math::Vector2<float>(633.5f, 613.5f));
		Slot2Delete->GetComponent<Transform>()->SetScale(Math::Vector2<float>(247.f, 67.f));
		temp = Resources::Load<Texture>(L"SlotDelete", L"..\\Resources\\SelectScene\\SlotDeleteButton.png");
		Slot2Delete->GetComponent<SpriteRenderer>()->SetImg(temp);
		Slot2Delete->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Slot3Delete = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Slot3Delete->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1039.5f, 613.5f));
		Slot3Delete->GetComponent<Transform>()->SetScale(Math::Vector2<float>(247.f, 67.f));
		temp = Resources::Load<Texture>(L"SlotDelete", L"..\\Resources\\SelectScene\\SlotDeleteButton.png");
		Slot3Delete->GetComponent<SpriteRenderer>()->SetImg(temp);
		Slot3Delete->GetComponent<SpriteRenderer>()->SetAffectCamera(false);

		BackGround* Exit = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Exit->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1226.5f, 45.f));
		Exit->GetComponent<Transform>()->SetScale(Math::Vector2<float>(83.f, 80.f));
		temp = Resources::Load<Texture>(L"Exit", L"..\\Resources\\SelectScene\\FullWindowExitButton.png");
		Exit->GetComponent<SpriteRenderer>()->SetImg(temp);
		Exit->GetComponent<SpriteRenderer>()->SetAffectCamera(false);
    }

    void SelectScene::Update()
    {
		if (Input::Getkey(eKeyCode::Z).state == eKeyState::DOWN)
		{
			SceneManager::LoadScene(L"TownScene");
		}
        Scene::Update();
    }

    void SelectScene::Render(HDC hdc)
    {
        Scene::Render(hdc);
    }
}