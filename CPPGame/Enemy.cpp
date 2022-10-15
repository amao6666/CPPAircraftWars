#include "Enemy.h"

Enemy::Enemy(COORD start_position, COORD window_size) : Sprite(window_size)
{
	this->position = start_position;
	this->body = new SPRITE_BODY{
		{ {0, 0}, "*" },
		{ {1, 0}, "*" },
		{ {2, 0}, "*" },
		{ {0, 1}, " " },
		{ {1, 1}, "*" },
		{ {2, 1}, " " }
	};

	this->old_position = start_position;
	this->position_diagonal = start_position + COORD { 2, 1 };
}

void Enemy::Update()
{
	Sprite::Update();
	position = position + COORD{ 0, 1 };
	// 如果飞机超出边界后自动销毁
	if (position.Y > window_size.Y + 1)
	{
		is_killed = true;
	}
}

Enemy::~Enemy()
{
}
