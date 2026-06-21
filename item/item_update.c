#include "../includes/thedump.h"

void	player_heal(t_cub *cub, int amount)
{
	cub->player_hp += amount;
	if (cub->player_hp > PLAYER_MAX_HP)
		cub->player_hp = PLAYER_MAX_HP;
}

void	player_add_ammo(t_cub *cub)
{
	// medic-kit1780649808.xpm also reloads ammo
	int i = 0;
	while (i < WEAPON_COUNT)
	{
		if (cub->weapons[i].type == WEAPON_REVOLVER)
			cub->weapons[i].reserve_ammo += 50;
		else if (cub->weapons[i].type == WEAPON_RIFLE)
			cub->weapons[i].reserve_ammo += 20;
		else if (cub->weapons[i].type == WEAPON_PLASMA)
			cub->weapons[i].reserve_ammo += 40;

		if (cub->weapons[i].reserve_ammo > cub->weapons[i].max_ammo)
			cub->weapons[i].reserve_ammo = cub->weapons[i].max_ammo;
		i++;
	}
}

void	explode_barrel(t_cub *cub, t_item *barrel)
{
	int		i;
	double	dist;

	barrel->active = false;
	play_explosion_sound(cub);
	cub->explosion_flash_timer = 5;

	i = 0;
	while (i < cub->enemy_count)
	{
		if (cub->enemies[i].alive && cub->enemies[i].state != EN_DEAD)
		{
			dist = sqrt(pow(cub->enemies[i].x - barrel->x, 2)
					+ pow(cub->enemies[i].y - barrel->y, 2));
			if (dist < 4.0)
			{
				cub->enemies[i].hp -= 100;
				if (cub->enemies[i].hp <= 0)
				{
					cub->enemies[i].state = EN_DEAD;
					cub->enemies[i].frame = 0;
					cub->enemies[i].frame_timer = 0;
				}
				else
				{
					cub->enemies[i].state = EN_HURT;
					cub->enemies[i].frame_timer = 0;
				}
			}
		}
		i++;
	}
	dist = sqrt(pow(cub->player->pos_x - barrel->x, 2)
			+ pow(cub->player->pos_y - barrel->y, 2));
	if (dist < 3.0 && cub->gold_buff_timer <= 0)
	{
		cub->player_hp -= 50;
		if (cub->player_hp < 0)
			cub->player_hp = 0;
	}
}

static void	collect_item(t_cub *cub, t_item *item)
{
	item->active = false;
	if (item->type == ITEM_MEDIC_KIT)
	{
		player_heal(cub, 25);
		player_add_ammo(cub);
	}
	else if (item->type == ITEM_BLUE_KEY)
	{
		cub->has_blue_key = true;
	}
	else if (item->type == ITEM_GOLD_PLANT)
	{
		cub->gold_buff_timer += 120.0;
		if (cub->gold_buff_timer > cub->max_gold_buff_timer)
			cub->max_gold_buff_timer = cub->gold_buff_timer;
	}
	else if (item->type == ITEM_WELL)
	{
		player_heal(cub, 5);
	}
}

void	update_items(t_cub *cub)
{
	int		i;
	double	dist;

	i = 0;
	while (i < cub->item_count)
	{
		if (cub->items[i].active)
		{
			dist = sqrt(pow(cub->player->pos_x - cub->items[i].x, 2)
					+ pow(cub->player->pos_y - cub->items[i].y, 2));
			cub->items[i].dist = dist;
			if (dist < ITEM_INTERACT_DIST)
				collect_item(cub, &cub->items[i]);
		}
		i++;
	}
}
