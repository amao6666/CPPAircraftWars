#include "SpriteGroup.h"

SpriteGroup::SpriteGroup()
{
	this->sprite_ptr_set = new std::set<Sprite*>;
}

void SpriteGroup::Append(Sprite* sprite_ptr)
{
	(*sprite_ptr_set).insert(sprite_ptr);
}

void SpriteGroup::Reset()
{
	// set����ʱɾ��
	for (auto it = sprite_ptr_set->begin(); it != sprite_ptr_set->end();)
	{
		if ((*it)->is_killed)
		{
			(*it)->Kill();
			sprite_ptr_set->erase(it++);
		}
		else
		{
			it++;
		}
	}
}

void SpriteGroup::GetCollideForGroup(SpriteGroup* target_group_ptr, COLLIDE_SPRITE_PTR_MULTIMAP* multi_map_container)
{
	// ʹ��multi map�� �غϵ�Spriteָ��
	for (auto& self_sprite : *sprite_ptr_set)
	{
		for (auto& target_sprite : *target_group_ptr->sprite_ptr_set)
		{
			if (self_sprite->IsCollide(target_sprite))
			{
				multi_map_container->insert(std::make_pair(self_sprite, target_sprite));
			}
		}
	}
}

void SpriteGroup::GetCollideForSprite(Sprite* target_sprite_ptr, SPRITE_PTR_SET* set_container)
{
	// ʹ��set�浱ǰ��������Ŀ�꾫���غϵľ���ָ��
	for (auto& sprite_item : *sprite_ptr_set)
	{
		if (sprite_item->IsCollide(target_sprite_ptr))
		{
			set_container->insert(sprite_item);
		}
	}

}

// �����������о���
void SpriteGroup::Update()
{
	if (!sprite_ptr_set) return;
	for (auto& sprite_item : *sprite_ptr_set)
	{
		if(sprite_item) sprite_item->Update();
	}
	Reset();
}

void SpriteGroup::Render()
{
	if (!sprite_ptr_set) return;
	for (auto& sprite_item : *sprite_ptr_set)
	{
		sprite_item->Render();
	}
}

SpriteGroup::~SpriteGroup()
{
	delete sprite_ptr_set;
	sprite_ptr_set = nullptr;
}
