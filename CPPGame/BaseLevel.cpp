#include "BaseLevel.h"

bool BaseLevel::HandleInput()
{
    INPUT_RECORD irInBuf[128];
    DWORD cNumRead = 0, i = 0;

    input->GetInput(irInBuf, cNumRead);
    if (cNumRead <= 0) return false;
    for (i = 0; i < cNumRead; i++)
    {
        switch (irInBuf[i].EventType)
        {
        case KEY_EVENT:
            if (irInBuf[i].Event.KeyEvent.bKeyDown)
            {
                OnKeyDown(irInBuf[i].Event.KeyEvent.wVirtualKeyCode);
            }
            break;
        default:
            break;
        }
    }
    return true;
}

void BaseLevel::OnKeyDown(int key_code)
{
}

BaseLevel::BaseLevel(COORD window_size, Input* input)
{
	this->window_size = window_size;
	this->input = input;
}

void BaseLevel::Update()
{
}

void BaseLevel::Clear()
{
}

BaseLevel::~BaseLevel()
{
	delete input;
	game_level = nullptr;
	input = nullptr;
}
