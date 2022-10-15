#pragma once
#include "BaseLevel.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Timer.h"
#include "SpriteGroup.h"
#include "GameDifficulty.h"

class GameLevel1 : public BaseLevel
{
	Player* player;
	Timer* timer;
	SpriteGroup* bullet_group;
	SpriteGroup* enemy_group;

	GameDifficulty* game_diffic;

	bool is_stop;

	virtual void OnKeyDown(int key_code);
	void HandleUpdate();
	void HandleRender();
	void HandleCollide();

	void InitBulletGenerater();
	void GenerateBullet();
	void InitEnemyGenerater();
	void GenerateEnemy();

public:
	GameLevel1(COORD window_size, GameDifficulty* game_diffic, Input* input);
	virtual void Update();
	virtual void Clear();
	~GameLevel1();
};

