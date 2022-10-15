#pragma once
#include <set>
#include <map>
#include "Sprite.h"

typedef std::set<Sprite*> SPRITE_PTR_SET;
typedef std::multimap<Sprite*, Sprite*> COLLIDE_SPRITE_PTR_MULTIMAP;

class SpriteGroup
{
public:
	SPRITE_PTR_SET* sprite_ptr_set;
	
	SpriteGroup();

	// ��Ӿ��鵽������
	void Append(Sprite* sprite_ptr);
	// �Ӿ�������ɾ��Killed�ľ���
	void Reset();

	// ��ȡ��ǰ��������Ŀ�꾫���������ص��ľ���
	void GetCollideForGroup(SpriteGroup* target_group_ptr, COLLIDE_SPRITE_PTR_MULTIMAP*);

	// ��ȡ��ǰ��������Ŀ�꾫���ص������о���
	void GetCollideForSprite(Sprite* target_sprite_ptr, SPRITE_PTR_SET*);

	// �����������о���
	void Update();
	// ��Ⱦ�������о���
	void Render();

	~SpriteGroup();
};

