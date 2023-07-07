#include "EHSelectScene.h"
#include "EHObject.h"
#include "EHImage.h"

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
		// Back
		Image* Back = object::Instantiate<Image>(enums::eLayerType::UI);
		Back->GetComponent<Transform>()->SetPos(Math::Vector2<float>(0.f, 0.f));
		Back->GetComponent<Transform>()->SetScale(Math::Vector2<float>(1280.f, 720.f));
		Back->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
		Back->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(320.f, 180.f));
		Back->SetImagePath(L"\\Resources\\SelectScene\\Back.png");

		Image* Slot1 = object::Instantiate<Image>(enums::eLayerType::UI);
		Slot1->GetComponent<Transform>()->SetPos(Math::Vector2<float>(50.f, 105.f));
		Slot1->GetComponent<Transform>()->SetScale(Math::Vector2<float>(380.f, 570.f));
		Slot1->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
		Slot1->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(96.f, 143.f));
		Slot1->SetImagePath(L"\\Resources\\SelectScene\\SlotBase.png");

		Image* Slot2 = object::Instantiate<Image>(enums::eLayerType::UI);
		Slot2->GetComponent<Transform>()->SetPos(Math::Vector2<float>(450.f, 105.f));
		Slot2->GetComponent<Transform>()->SetScale(Math::Vector2<float>(380.f, 570.f));
		Slot2->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
		Slot2->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(96.f, 143.f));
		Slot2->SetImagePath(L"\\Resources\\SelectScene\\SlotBase.png");

		Image* Slot3 = object::Instantiate<Image>(enums::eLayerType::UI);
		Slot3->GetComponent<Transform>()->SetPos(Math::Vector2<float>(850.f, 105.f));
		Slot3->GetComponent<Transform>()->SetScale(Math::Vector2<float>(380.f, 570.f));
		Slot3->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
		Slot3->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(96.f, 143.f));
		Slot3->SetImagePath(L"\\Resources\\SelectScene\\SlotBase.png");

		Image* Slot1Text = object::Instantiate<Image>(enums::eLayerType::UI);
		Slot1Text->GetComponent<Transform>()->SetPos(Math::Vector2<float>(172.f, 150.f));
		Slot1Text->GetComponent<Transform>()->SetScale(Math::Vector2<float>(140.f, 46.f));
		Slot1Text->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
		Slot1Text->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(38.f, 12.f));
		Slot1Text->SetImagePath(L"\\Resources\\SelectScene\\SlotText1.EN.png");

		Image* Slot2Text = object::Instantiate<Image>(enums::eLayerType::UI);
		Slot2Text->GetComponent<Transform>()->SetPos(Math::Vector2<float>(572.f, 150.f));
		Slot2Text->GetComponent<Transform>()->SetScale(Math::Vector2<float>(140.f, 46.f));
		Slot2Text->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
		Slot2Text->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(38.f, 12.f));
		Slot2Text->SetImagePath(L"\\Resources\\SelectScene\\SlotText2.EN.png");

		Image* Slot3Text = object::Instantiate<Image>(enums::eLayerType::UI);
		Slot3Text->GetComponent<Transform>()->SetPos(Math::Vector2<float>(972.f, 150.f));
		Slot3Text->GetComponent<Transform>()->SetScale(Math::Vector2<float>(140.f, 46.f));
		Slot3Text->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
		Slot3Text->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(38.f, 12.f));
		Slot3Text->SetImagePath(L"\\Resources\\SelectScene\\SlotText3.EN.png");

		Image* Slot1Delete = object::Instantiate<Image>(enums::eLayerType::UI);
		Slot1Delete->GetComponent<Transform>()->SetPos(Math::Vector2<float>(116.f, 580.f));
		Slot1Delete->GetComponent<Transform>()->SetScale(Math::Vector2<float>(247.f, 67.f));
		Slot1Delete->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
		Slot1Delete->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(62.f, 17.f));
		Slot1Delete->SetImagePath(L"\\Resources\\SelectScene\\SlotDeleteButton.png");

		Image* Slot2Delete = object::Instantiate<Image>(enums::eLayerType::UI);
		Slot2Delete->GetComponent<Transform>()->SetPos(Math::Vector2<float>(510.f, 580.f));
		Slot2Delete->GetComponent<Transform>()->SetScale(Math::Vector2<float>(247.f, 67.f));
		Slot2Delete->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
		Slot2Delete->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(62.f, 17.f));
		Slot2Delete->SetImagePath(L"\\Resources\\SelectScene\\SlotDeleteButton.png");

		Image* Slot3Delete = object::Instantiate<Image>(enums::eLayerType::UI);
		Slot3Delete->GetComponent<Transform>()->SetPos(Math::Vector2<float>(916.f, 580.f));
		Slot3Delete->GetComponent<Transform>()->SetScale(Math::Vector2<float>(247.f, 67.f));
		Slot3Delete->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
		Slot3Delete->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(62.f, 17.f));
		Slot3Delete->SetImagePath(L"\\Resources\\SelectScene\\SlotDeleteButton.png");

		Image* Exit = object::Instantiate<Image>(enums::eLayerType::UI);
		Exit->GetComponent<Transform>()->SetPos(Math::Vector2<float>(1185.f, 5.f));
		Exit->GetComponent<Transform>()->SetScale(Math::Vector2<float>(83.f, 80.f));
		Exit->GetComponent<SpriteRenderer>()->SetSrcPos(Math::Vector2<float>(0.f, 0.f));
		Exit->GetComponent<SpriteRenderer>()->SetSrcScale(Math::Vector2<float>(22.f, 19.f));
		Exit->SetImagePath(L"\\Resources\\SelectScene\\FullWindowExitButton.png");
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