#include "Player.h"

Player::Player(COORD window_size) : Sprite(window_size)
{
	this->body = new SPRITE_BODY { 
		{ {0, 0}, " " },
		{ {1, 0}, "*" },
		{ {2, 0}, " " },
		{ {0, 1}, "*" },
		{ {1, 1}, "*" },
		{ {2, 1}, "*" }
	};
	this->position = { 24, 24 };
    this->old_position = { 24, 24 };
    this->position_diagonal = { 2, 1 };
}

void Player::Update(int key_code)
{
    Sprite::Update(key_code);
    switch (key_code)
    {
    case VK_LEFT:
        position = position + COORD { -1, 0 };
        break;
    case VK_RIGHT:
        position = position + COORD { 1, 0 };
        break;
    case VK_UP:
        position = position + COORD { 0, -1 };
        break;
    case VK_DOWN:
        position = position + COORD { 0, 1 };
        break;
    default:
        break;
    }
    // ÒÆ¶¯·¶Î§ÏÞÖÆ
    if (position.X < 1) position.X = 1;
    if (position.Y < 1) position.Y = 1;
    if ((position.X + position_diagonal.X) > (window_size.X)) position.X = (window_size.X - position_diagonal.X);
    if ((position.Y + position_diagonal.Y) > (window_size.Y)) position.Y = (window_size.Y - position_diagonal.Y);
}

Player::~Player()
{
    delete body;
    body = nullptr;
}
