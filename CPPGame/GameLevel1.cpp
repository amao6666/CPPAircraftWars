#include "GameLevel1.h"
#include "Player.h"
#include "Timer.h"
#include<random>
#include<stdlib.h>
#include<time.h>

GameLevel1::GameLevel1(COORD window_size, GameDifficulty* game_diffic, Input* input) : BaseLevel(window_size, input)
{
    this->is_stop = false;
    this->game_diffic = game_diffic;
    // 初始化定时器
    this->timer = new Timer;
    // 初始化Player
    this->player = new Player(window_size);
    this->player->Render();

    // 初始化子弹生成器
    this->bullet_group = new SpriteGroup;
    InitBulletGenerater();

    // 初始化敌人飞机生成器
    this->enemy_group = new SpriteGroup;
    InitEnemyGenerater();
}

void GameLevel1::InitBulletGenerater()
{
    timer->SetInterval(
        [this]() { GenerateBullet(); }, 300
    );
}

void GameLevel1::GenerateBullet()
{
    // 子弹开始位置为Player飞机的头部坐标
    COORD start_position = player->position + COORD {1, -1};
    Bullet* bullet_ptr = new Bullet(start_position, this->window_size);
    this->bullet_group->Append(bullet_ptr);
}

void GameLevel1::InitEnemyGenerater()
{
    // 根据游戏难度调整生成敌机飞机的频率
    int time_s = 1200;
    switch (*(this->game_diffic))
    {
    case GameDifficulty::Easy:
        time_s = 1200;
        break;
    case GameDifficulty::Normal:
        time_s = 800;
        break;
    case GameDifficulty::Hard:
        time_s = 400;
        break;
    default:
        break;
    }

    timer->SetInterval(
        [this]() { GenerateEnemy(); }, time_s
    );
}

void GameLevel1::GenerateEnemy()
{
    // 随机生成飞机位置
    srand((unsigned)time(NULL));
    short x = (rand() % (window_size.X - 3)) + 1;
    short y = -1 * ((rand() % (20 - 2)) + 1);
    COORD start_position = { x, y };
    Enemy* enemy_ptr = new Enemy(start_position, this->window_size);
    this->enemy_group->Append(enemy_ptr);
}

// 每一帧刷新的逻辑
void GameLevel1::Update()
{
    if (is_stop) return;
    // 处理用户输入
    HandleInput();
    // 更新屏幕中的所有元素（敌机和子弹）
    HandleUpdate();
    // 处理碰撞 子弹和敌机，Player和敌机
    HandleCollide();
    // 渲染屏幕中的所有元素
    HandleRender();
}

void GameLevel1::HandleUpdate()
{
    this->bullet_group->Update();
    this->enemy_group->Update();
}

void GameLevel1::HandleRender()
{
    this->bullet_group->Render();
    this->enemy_group->Render();
    this->player->Render();
    if (is_stop)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 20, 10 });
        std::cout << "Game Over!" << std::endl;
        // 隐藏光标
        CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
    }
}

void GameLevel1::HandleCollide()
{
    // 子弹和敌机碰撞
    COLLIDE_SPRITE_PTR_MULTIMAP b_e_multimap;
    bullet_group->GetCollideForGroup(enemy_group, &b_e_multimap);
    for (auto it : b_e_multimap)
    {
        it.first->is_killed = true;
        it.second->is_killed = true;
    }
    bullet_group->Reset();
    enemy_group->Reset();

    // 玩家和敌机碰撞
    SPRITE_PTR_SET e_p_set;
    enemy_group->GetCollideForSprite(player, &e_p_set);
    if (!e_p_set.empty())
    {
        this->is_stop = true;
    }
}

void GameLevel1::OnKeyDown(int key_code)
{
    player->Update(key_code);
    player->Render();
}

void GameLevel1::Clear()
{
}

GameLevel1::~GameLevel1()
{
    delete timer;
    delete player;
    delete bullet_group;
    delete enemy_group;
    timer = nullptr;
    player = nullptr;
    bullet_group = nullptr;
    enemy_group = nullptr;
}