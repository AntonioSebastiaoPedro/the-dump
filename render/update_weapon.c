#include "../includes/cub.h"

static int	get_max_frames(t_weapon *weapon, int state)
{
	if (state == WEAPON_IDLE)
		return (1);
	else if (state == WEAPON_MOVE)
	{
		if (weapon->type == WEAPON_REVOLVER)
			return (7);
		else if (weapon->type == WEAPON_RIFLE)
			return (6);
		else if (weapon->type == WEAPON_PLASMA)
			return (6);
		return (1);
	}
	else if (state == WEAPON_SHOT)
	{
		if (weapon->type == WEAPON_REVOLVER)
			return (9);
		else if (weapon->type == WEAPON_RIFLE)
			return (13);
		else if (weapon->type == WEAPON_PLASMA)
			return (6);
		return (5);
	}
	return (0);
}

void	set_weapon_state(t_weapon *weapon, int new_state)
{
	if (weapon->state == new_state)
		return ;
	weapon->state = new_state;
	weapon->current_frame = 0;
	weapon->frame_timer = 0;
	if (new_state == WEAPON_IDLE)
		weapon->frame_delay = 15;
	else if (new_state == WEAPON_MOVE)
		weapon->frame_delay = 4;
	else if (new_state == WEAPON_SHOT)
	{
		if (weapon->type == WEAPON_REVOLVER)
			weapon->frame_delay = 6;
		else if (weapon->type == WEAPON_RIFLE)
			weapon->frame_delay = 2;
		else if (weapon->type == WEAPON_PLASMA)
			weapon->frame_delay = 4;
	}
}

static void	update_frame(t_weapon *weapon)
{
	weapon->frame_timer++;
	if (weapon->frame_timer >= weapon->frame_delay)
	{
		weapon->frame_timer = 0;
		weapon->current_frame++;
	}
}

void	update_weapon(t_cub *cub)
{
	t_weapon	*weapon;

	weapon = cub->current_weapon;
	if (!weapon)
		return ;
	if (weapon->state == WEAPON_SHOT)
	{
		update_frame(weapon);
		if (weapon->current_frame >= get_max_frames(weapon, weapon->state))
		{
			if (cub->player->is_moving)
				set_weapon_state(weapon, WEAPON_MOVE);
			else
				set_weapon_state(weapon, WEAPON_IDLE);
		}
		return ;
	}
	if (cub->player->is_moving)
		set_weapon_state(weapon, WEAPON_MOVE);
	else
		set_weapon_state(weapon, WEAPON_IDLE);
	update_frame(weapon);
	if (weapon->current_frame >= get_max_frames(weapon, weapon->state))
		weapon->current_frame = 0;
}