#pragma once
#include "BaseLevel.h"
#include "Sprite.h"
#include "GameDifficulty.h"

class StartLevel : public BaseLevel
{
	Sprite* info_sprite;
	Sprite* cursor_sprite;
	GameLevel* game_level;
	GameDifficulty* game_diffic;

public:
	StartLevel(COORD window_size, GameLevel* game_level, GameDifficulty* game_diffic, Input* input);
	void InitWindow();
	void StartGame();
	virtual void OnKeyDown(int key_code);
	virtual void Update();
	virtual void Clear();
	~StartLevel();
};

