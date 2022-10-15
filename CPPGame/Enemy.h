#pragma once
#include "Sprite.h"
class Enemy : public Sprite
{
public:
	Enemy(COORD start_position, COORD window_size);
	virtual void Update();
	~Enemy();
};

