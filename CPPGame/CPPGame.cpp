#include "CPPGame.h"
#include <iostream>

CPPGame::CPPGame(COORD window_size)
{
    input = new Input;

    this->window_size = window_size;
    this->current_level = GameLevel::Start;
    this->current_game_diffic = GameDifficulty::Easy;

    start_level = nullptr;
    game_level1 = nullptr;

    RenderWindow();
}

BaseLevel* CPPGame::GetLevel()
{
    switch (current_level)
    {
    case GameLevel::Start:
        if (!start_level) start_level = new StartLevel(window_size, &current_level, &current_game_diffic, input);
        return start_level;
        break;
    case GameLevel::Level1:
        if (!game_level1) game_level1 = new GameLevel1(window_size, &current_game_diffic, input);
        return game_level1;
        break;
    default:
        break;
    }
}

void CPPGame::RenderWindow()
{
    using namespace std;
    // ºá±ß
    for (short row = 0; row < window_size.X + 1; row++)
    {
        COORD location1 = { row, 0 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), location1);
        cout << "#";
        COORD location2 = { row, window_size.Y + 1 };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), location2);
        cout << "#";
    }

    // Êú±ß
    for (short col = 0; col < window_size.Y + 1; col++)
    {
        COORD location1 = { 0, col };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), location1);
        cout << "#";
        COORD location2 = { window_size.X + 1, col };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), location2);
        cout << "#";
    }
}

void CPPGame::Run()
{
    using namespace std;
    while (true)
    {
        BaseLevel* level = GetLevel();
        level->Update();
        Sleep(60);
    }
}

CPPGame::~CPPGame()
{
    delete input;
    input = nullptr;
    
}
