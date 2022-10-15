#include "Sprite.h"

COORD operator+(COORD p1, COORD p2)
{
    COORD temp_p = { p1.X + p2.X, p1.Y + p2.Y };
    return temp_p;
}

COORD operator-(COORD p1, COORD p2)
{
    COORD temp_p = { p1.X - p2.X, p1.Y - p2.Y };
    return temp_p;
}

bool operator==(COORD p1, COORD p2)
{
    return p1.X == p2.X && p1.Y == p2.Y;
}

bool operator<(COORD p1, COORD p2)
{
    if (p1.X != p2.X) return p1.X < p2.X;
    return p1.Y < p2.Y;
}

Sprite::Sprite(COORD window_size)
{
    this->group_set_ptr = nullptr;
    this->body = nullptr;
    this->position = { 0, 0 };
    this->old_position = { 0, 0 };
    this->position_diagonal = { 0, 0 };
    this->is_killed = false;
    this->window_size = window_size;
}

bool Sprite::BodyItemIsInWindow(COORD body_item_position)
{
    bool y_is_in = body_item_position.Y >= 1 && body_item_position.Y <= window_size.Y;
    bool x_is_in = body_item_position.X >= 1 && body_item_position.X <= window_size.X;
    return y_is_in && x_is_in;
}

void Sprite::Update()
{
    old_position = position;
}

void Sprite::Update(int key_code)
{
    Update();
}

void Sprite::Fill(COORD location, std::string fill)
{
    using namespace std;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), location);
    cout << fill;
    // 隐藏光标
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void Sprite::Render()
{
    // 清除残影
    for (auto& body_item : *body)
    {
        COORD location = body_item.first + this->old_position;
        if (BodyItemIsInWindow(location)) Fill(location, " ");
    }
 
    // 渲染新的图形
    for (auto& body_item : *body)
    {
        COORD location = body_item.first + this->position;
        if (BodyItemIsInWindow(location)) Fill(location, body_item.second);
    }
}

void Sprite::Clear()
{
    for (auto& item : (*body))
    {
        COORD location = item.first + this->position;
        // 重影坐标
        COORD old_location = item.first + this->old_position;
        int fill_length = item.second.length();
        
        std::string empty_fill(fill_length, ' ');

        if (BodyItemIsInWindow(location)) Fill(location, empty_fill);
        if (BodyItemIsInWindow(old_location)) Fill(old_location, empty_fill);
    }
}

void Sprite::Kill()
{
    Clear();
    delete this;
}

bool Sprite::IsCollide(Sprite* target_sprite)
{
    for (auto& body_item : *body)
    {
        COORD target_position = body_item.first + position - target_sprite->position;
        if (target_sprite->body->count(target_position))
        {
            return true;
        }
    }
    return false;
}

Sprite::~Sprite()
{
    delete body;
    body = nullptr;
    group_set_ptr = nullptr;
}
