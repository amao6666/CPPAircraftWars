#pragma once
#include "Sprite.h"
class Player : public Sprite
{
public:
	Player(COORD window_size);
	void Update(int key_code);
	~Player();
};

