#pragma once
#include <Windows.h>
#include <vector>
#include <iostream>
#include <map>
#include <set>

class Sprite;

typedef std::set<Sprite*> SPRITE_PTR_SET;
typedef std::multimap<Sprite*, Sprite*> COLLIDE_SPRITE_PTR_MULTIMAP;

// 坐标相加
COORD operator+(COORD p1, COORD p2);
// 坐标相减
COORD operator-(COORD p1, COORD p2);
// 坐标是否相等
bool operator==(COORD p1, COORD p2);
// 坐标比较
bool operator<(COORD p1, COORD p2);

typedef std::map<COORD, std::string> SPRITE_BODY;

class Sprite
{
	void Fill(COORD, std::string);
	// 从精灵组里删除自己

public:
	// 窗口大小
	COORD window_size;
	SPRITE_BODY* body;
	// 左上角的 坐标
	COORD position;
	COORD old_position;
	// 最右下角的body item 的坐标
	COORD position_diagonal;

	// 如果 Sprite 被加入到精灵组中，所在的容器指针
	SPRITE_PTR_SET* group_set_ptr;

	// 是否被Kill
	bool is_killed;

	Sprite(COORD window_size);
	
	// 判断body是否在窗口内
	bool BodyItemIsInWindow(COORD);

	virtual void Update();
	virtual void Update(int key_code);

	void Render();
	void Clear();
	void Kill();

	// 判断两个精灵是否相交
	bool IsCollide(Sprite*);

	~Sprite();
};
