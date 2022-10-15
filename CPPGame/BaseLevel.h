#pragma once
#include "Input.h"
#include "LevelEnum.h"

class BaseLevel
{
protected:
	COORD window_size;
	Input* input;
	GameLevel* game_level;
	
	bool HandleInput();
	virtual void OnKeyDown(int key_code) = 0;
public:
	BaseLevel(COORD window_size, Input* input);
	virtual void Update();
	virtual void Clear();
	~BaseLevel();
};

