#pragma once
#include "Input.h"
#include "StartLevel.h"
#include "GameLevel1.h"
#include "LevelEnum.h"
#include "GameDifficulty.h"
#include <vector>
#include <functional>

class CPPGame
{
	Input* input;

	StartLevel* start_level;
	GameLevel1* game_level1;

	GameLevel current_level;
	GameDifficulty current_game_diffic;

	BaseLevel* GetLevel();

	void RenderWindow();	
public:
	COORD window_size;

	CPPGame(COORD window_size);
	void Run();
	~CPPGame();
};

