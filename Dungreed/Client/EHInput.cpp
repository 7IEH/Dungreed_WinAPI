#include "EHInput.h"

namespace EH
{
	std::vector<Input::Key> Input::mKeys = {};

	int ASCII[(UINT)eKeyCode::END] =
	{
		'Q','W','E','R','T','Y','U','I','O','P',
		'A','S','D','F','G','H','J','K','L',
		'Z','X','C','V','B','N','M'
	};

	void Input::Initialize()
	{
		for (size_t i = 0; i < (UINT)eKeyCode::END; i++)
		{
			Key temp = {};
			temp.code = (eKeyCode)i;
			temp.state = eKeyState::NONE;
			temp.bPressed = false;

			mKeys.push_back(temp);
		}
	}

	void Input::Update()
	{
		for (size_t i = 0; i < (UINT)eKeyCode::END; i++)
		{
			// ���� ����
			if (GetAsyncKeyState(ASCII[i]) & 0x8000) 
			{
				// ���� �������� �ִ�.
				if (mKeys[i].bPressed)
				{
					mKeys[i].state = eKeyState::PRESSED;
				}
				// ����.
				else
				{
					mKeys[i].state = eKeyState::DOWN;
					mKeys[i].bPressed = true;
				}
			}
			// ���� �ȴ���
			else
			{
				if (mKeys[i].bPressed)
				{
					mKeys[i].state = eKeyState::UP;
					mKeys[i].bPressed = false;
				}
				else
				{
					mKeys[i].state = eKeyState::NONE;
				}
			}
		}
	}

}