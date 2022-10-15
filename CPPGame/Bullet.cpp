#include "Bullet.h"

Bullet::Bullet(COORD start_position, COORD window_size) : Sprite(window_size)
{
	this->position = start_position;
	this->body = new SPRITE_BODY{
		{ {0, 0}, "*"}
	};

	this->old_position = start_position;
	this->position_diagonal = start_position;
}

void Bullet::Update()
{
	Sprite::Update();
	position = position + COORD { 0, -1 };
	// 如果子弹碰到边界后自动销毁
	if (position.Y < 1)
	{
		is_killed = true;
		position.Y = 1;
	}
}

Bullet::~Bullet()
{
	delete body;
	body = nullptr;
}
