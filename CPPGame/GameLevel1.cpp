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
    // ��ʼ����ʱ��
    this->timer = new Timer;
    // ��ʼ��Player
    this->player = new Player(window_size);
    this->player->Render();

    // ��ʼ���ӵ�������
    this->bullet_group = new SpriteGroup;
    InitBulletGenerater();

    // ��ʼ�����˷ɻ�������
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
    // �ӵ���ʼλ��ΪPlayer�ɻ���ͷ������
    COORD start_position = player->position + COORD {1, -1};
    Bullet* bullet_ptr = new Bullet(start_position, this->window_size);
    this->bullet_group->Append(bullet_ptr);
}

void GameLevel1::InitEnemyGenerater()
{
    // ������Ϸ�Ѷȵ������ɵл��ɻ���Ƶ��
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
    // ������ɷɻ�λ��
    srand((unsigned)time(NULL));
    short x = (rand() % (window_size.X - 3)) + 1;
    short y = -1 * ((rand() % (20 - 2)) + 1);
    COORD start_position = { x, y };
    Enemy* enemy_ptr = new Enemy(start_position, this->window_size);
    this->enemy_group->Append(enemy_ptr);
}

// ÿһ֡ˢ�µ��߼�
void GameLevel1::Update()
{
    if (is_stop) return;
    // �����û�����
    HandleInput();
    // ������Ļ�е�����Ԫ�أ��л����ӵ���
    HandleUpdate();
    // ������ײ �ӵ��͵л���Player�͵л�
    HandleCollide();
    // ��Ⱦ��Ļ�е�����Ԫ��
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
        // ���ع��
        CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
    }
}

void GameLevel1::HandleCollide()
{
    // �ӵ��͵л���ײ
    COLLIDE_SPRITE_PTR_MULTIMAP b_e_multimap;
    bullet_group->GetCollideForGroup(enemy_group, &b_e_multimap);
    for (auto it : b_e_multimap)
    {
        it.first->is_killed = true;
        it.second->is_killed = true;
    }
    bullet_group->Reset();
    enemy_group->Reset();

    // ��Һ͵л���ײ
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