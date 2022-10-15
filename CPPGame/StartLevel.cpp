#include "StartLevel.h"
#include <iostream>

StartLevel::StartLevel(COORD window_size, GameLevel* game_level, GameDifficulty* game_diffic, Input* input) : BaseLevel(window_size, input)
{
	this->game_level = game_level;
	this->game_diffic = game_diffic;
	this->info_sprite = new Sprite(window_size);
	this->cursor_sprite = new Sprite(window_size);
	InitWindow();
}

void StartLevel::InitWindow()
{
	info_sprite->body = new SPRITE_BODY {
		{ {1, 0}, "===============" },
		{ {1, 1}, "    飞机大战"},
		{ {1, 2}, "===============" },
		
		{ {1, 5}, "    选择模式："},
		{ {1, 7}, "      简单"},
		{ {1, 8}, "      正常"},
		{ {1, 9}, "      困难"},
		   
		{ {1, 11}, "[按Enter开始游戏]"}
	};

	cursor_sprite->body = new SPRITE_BODY { { {0, 0}, "*" } };

	info_sprite->position = { 17, 4 };
	cursor_sprite->position = { 21, 11 };

	info_sprite->Render();
	cursor_sprite->Render();
}

void StartLevel::StartGame()
{
	*game_diffic = GameDifficulty(cursor_sprite->position.Y - 11);
	*game_level = GameLevel::Level1;
	Clear();
}

void StartLevel::OnKeyDown(int key_code)
{
	cursor_sprite->Update();
	COORD& position = cursor_sprite->position;
	switch (key_code)
	{
	case VK_UP:
		position = position + COORD{ 0, -1 };
		break;
	case VK_DOWN:
		position = position + COORD{ 0, 1 };
		break;
	case VK_RETURN:
		StartGame();
		return;
	default:
		break;
	}
	// 限制坐标
	if (position.Y < 11) position.Y = 11;
	if (position.Y > 13) position.Y = 13;
	cursor_sprite->Render();
}

void StartLevel::Update()
{
	HandleInput();
}

void StartLevel::Clear()
{
	this->info_sprite->Clear();
	this->cursor_sprite->Clear();
}

StartLevel::~StartLevel()
{
	delete info_sprite;
	delete cursor_sprite;
	info_sprite = nullptr;
	cursor_sprite = nullptr;
}
