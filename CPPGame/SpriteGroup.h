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

	// 添加精灵到精灵组
	void Append(Sprite* sprite_ptr);
	// 从精灵组内删除Killed的精灵
	void Reset();

	// 获取当前精灵组与目标精灵组所有重叠的精灵
	void GetCollideForGroup(SpriteGroup* target_group_ptr, COLLIDE_SPRITE_PTR_MULTIMAP*);

	// 获取当前精灵组与目标精灵重叠的所有精灵
	void GetCollideForSprite(Sprite* target_sprite_ptr, SPRITE_PTR_SET*);

	// 更新组内所有精灵
	void Update();
	// 渲染组内所有精灵
	void Render();

	~SpriteGroup();
};

