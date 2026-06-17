#include "../includes/cub.h"

void	on_mouse_click(t_cub *cub)
{
	if (!cub->current_weapon || cub->current_weapon->state == WEAPON_SHOT)
		return ;
	if (cub->current_weapon->current_ammo <= 0)
	{
		// To do: play empty click sound
		return ;
	}
	cub->current_weapon->current_ammo--;
	set_weapon_state(cub->current_weapon, WEAPON_SHOT);
	play_weapon_sound(cub);
	enemy_take_damage(cub);
}

void	switch_weapon_next(t_cub *cub)
{
	cub->current_weapon_index++;
	if (cub->current_weapon_index >= WEAPON_COUNT)
		cub->current_weapon_index = 0;
	cub->current_weapon = &cub->weapons[cub->current_weapon_index];
}

int	mouse_hook(int key, int x, int y, void *param)
{
	t_cub *cub = (t_cub *)param;
	(void)x;
	(void)y;
	if (cub->state == GAME)
	{
		if (key == 1 && cub->mouse.show_mouse == false)
			on_mouse_click(cub);
	}
	return (0);
}