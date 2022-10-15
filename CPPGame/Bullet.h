#pragma once
#include "Sprite.h"

class Bullet : public Sprite
{
public:
	Bullet(COORD start_position, COORD window_size);
	virtual void Update();
	~Bullet();
};

