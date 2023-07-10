#include "EHSelectScene.h"
#include "EHObject.h"
#include "EHImage.h"
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
		Image* temp = nullptr;
		// Back
		BackGround* Back = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Back->GetComponent<Transform>()->SetPos(Math::Vector2<float>(0.f, 0.f));
		Back->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		temp = Resources::Load<Image>(L"SelectBackImage", L"..\\Resources\\SelectScene\\Back.png");
		Back->GetComponent<SpriteRenderer>()->SetImg(temp);

		BackGround* Slot1 = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Slot1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(50.f, 105.f));
		Slot1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(380.f, 570.f));
		temp = Resources::Load<Image>(L"Slot", L"..\\Resources\\SelectScene\\SlotBase.png");
		Slot1->GetComponent<SpriteRenderer>()->SetImg(temp);

		BackGround* Slot2 = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Slot2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(450.f, 105.f));
		Slot2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(380.f, 570.f));
		temp = Resources::Load<Image>(L"Slot", L"..\\Resources\\SelectScene\\SlotBase.png");
		Slot2->GetComponent<SpriteRenderer>()->SetImg(temp);

		BackGround* Slot3 = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Slot3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(850.f, 105.f));
		Slot3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(380.f, 570.f));
		temp = Resources::Load<Image>(L"Slot", L"..\\Resources\\SelectScene\\SlotBase.png");
		Slot3->GetComponent<SpriteRenderer>()->SetImg(temp);

		BackGround* Slot1Text = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Slot1Text->GetComponent<Transform>()->SetPos(Math::Vector2<float>(172.f, 150.f));
		Slot1Text->GetComponent<Transform>()->SetScale(Math::Vector2<float>(140.f, 46.f));
		temp = Resources::Load<Image>(L"SlotText1", L"..\\Resources\\SelectScene\\SlotText1.EN.png");
		Slot1Text->GetComponent<SpriteRenderer>()->SetImg(temp);

		BackGround* Slot2Text = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Slot2Text->GetComponent<Transform>()->SetPos(Math::Vector2<float>(572.f, 150.f));
		Slot2Text->GetComponent<Transform>()->SetScale(Math::Vector2<float>(140.f, 46.f));
		temp = Resources::Load<Image>(L"SlotText2", L"..\\Resources\\SelectScene\\SlotText2.EN.png");
		Slot2Text->GetComponent<SpriteRenderer>()->SetImg(temp);

		BackGround* Slot3Text = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Slot3Text->GetComponent<Transform>()->SetPos(Math::Vector2<float>(972.f, 150.f));
		Slot3Text->GetComponent<Transform>()->SetScale(Math::Vector2<float>(140.f, 46.f));
		temp = Resources::Load<Image>(L"SlotText3", L"..\\Resources\\SelectScene\\SlotText3.EN.png");
		Slot3Text->GetComponent<SpriteRenderer>()->SetImg(temp);

		BackGround* Slot1Delete = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Slot1Delete->GetComponent<Transform>()->SetPos(Math::Vector2<float>(116.f, 580.f));
		Slot1Delete->GetComponent<Transform>()->SetScale(Math::Vector2<float>(247.f, 67.f));
		temp = Resources::Load<Image>(L"SlotDelete", L"..\\Resources\\SelectScene\\SlotDeleteButton.png");
		Slot1Delete->GetComponent<SpriteRenderer>()->SetImg(temp);

		BackGround* Slot2Delete = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Slot2Delete->GetComponent<Transform>()->SetPos(Math::Vector2<float>(510.f, 580.f));
		Slot2Delete->GetComponent<Transform>()->SetScale(Math::Vector2<float>(247.f, 67.f));
		temp = Resources::Load<Image>(L"SlotDelete", L"..\\Resources\\SelectScene\\SlotDeleteButton.png");
		Slot2Delete->GetComponent<SpriteRenderer>()->SetImg(temp);

		BackGround* Slot3Delete = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Slot3Delete->GetComponent<Transform>()->SetPos(Math::Vector2<float>(916.f, 580.f));
		Slot3Delete->GetComponent<Transform>()->SetScale(Math::Vector2<float>(247.f, 67.f));
		temp = Resources::Load<Image>(L"SlotDelete", L"..\\Resources\\SelectScene\\SlotDeleteButton.png");
		Slot3Delete->GetComponent<SpriteRenderer>()->SetImg(temp);

		BackGround* Exit = object::Instantiate<BackGround>(enums::eLayerType::UI);
		Exit->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1185.f, 5.f));
		Exit->GetComponent<Transform>()->SetScale(Math::Vector2<float>(83.f, 80.f));
		temp = Resources::Load<Image>(L"Exit", L"..\\Resources\\SelectScene\\FullWindowExitButton.png");
		Exit->GetComponent<SpriteRenderer>()->SetImg(temp);
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