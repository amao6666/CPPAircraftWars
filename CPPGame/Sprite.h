#pragma once
#include <Windows.h>
#include <vector>
#include <iostream>
#include <map>
#include <set>

class Sprite;

typedef std::set<Sprite*> SPRITE_PTR_SET;
typedef std::multimap<Sprite*, Sprite*> COLLIDE_SPRITE_PTR_MULTIMAP;

// �������
COORD operator+(COORD p1, COORD p2);
// �������
COORD operator-(COORD p1, COORD p2);
// �����Ƿ����
bool operator==(COORD p1, COORD p2);
// ����Ƚ�
bool operator<(COORD p1, COORD p2);

typedef std::map<COORD, std::string> SPRITE_BODY;

class Sprite
{
	void Fill(COORD, std::string);
	// �Ӿ�������ɾ���Լ�

public:
	// ���ڴ�С
	COORD window_size;
	SPRITE_BODY* body;
	// ���Ͻǵ� ����
	COORD position;
	COORD old_position;
	// �����½ǵ�body item ������
	COORD position_diagonal;

	// ��� Sprite �����뵽�������У����ڵ�����ָ��
	SPRITE_PTR_SET* group_set_ptr;

	// �Ƿ�Kill
	bool is_killed;

	Sprite(COORD window_size);
	
	// �ж�body�Ƿ��ڴ�����
	bool BodyItemIsInWindow(COORD);

	virtual void Update();
	virtual void Update(int key_code);

	void Render();
	void Clear();
	void Kill();

	// �ж����������Ƿ��ཻ
	bool IsCollide(Sprite*);

	~Sprite();
};
