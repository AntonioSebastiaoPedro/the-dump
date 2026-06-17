#include "../includes/cub.h"

int	ft_close(t_cub *cub)
{
	free_cub(cub);
	exit(0);
	return (0);
}

void	hook_close(t_cub *cub)
{
	mlx_hook(cub->mlx->win, 17, 0, ft_close, cub);
}

void	toggle_mouse_vis(t_cub *cub)
{
	cub->mouse.show_mouse = !cub->mouse.show_mouse;
	if (cub->mouse.show_mouse)
		mlx_mouse_show(cub->mlx->mlx, cub->mlx->win);
	else
		mlx_mouse_hide(cub->mlx->mlx, cub->mlx->win);
}

int	key_press(int key, t_cub *cub)
{
	if (key == ESC && cub->state == GAME)
		ft_close(cub);
	if (key == KEY_P && cub->state == GAME)
		toggle_mouse_vis(cub);
	if (cub->state == MENU || cub->state == ABOUT)
	{
		handle_menu_input(key, cub);
	}
	if (key >= 0 && key < 65536)
		cub->keys[key] = 1;
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
		cub->player->is_moving = 1;
	if (key == SPACE && cub->state == GAME)
		try_interact_door(cub);
	if (key == KEY_M)
		cub->show_mira = !cub->show_mira;
	if (key == KEY_RCTRL)
		on_mouse_click(cub);
	if (key == KEY_V)
		cub->state = MENU;
	if (key == KEY_1)
		cub->current_weapon_index = 0;
	if (key == KEY_2)
		cub->current_weapon_index = 2; // Gatling
	if (key == KEY_3)
		cub->current_weapon_index = 1; // Machinegun
	if (key == KEY_UP && cub->state == GAME)
		cub->crosshair.scale += 0.2f;
	if (key == KEY_DOWN && cub->state == GAME)
	{
		cub->crosshair.scale -= 0.2f;
		if (cub->crosshair.scale < 0.2f)
			cub->crosshair.scale = 0.2f;
	}
	if (key == KEY_U)
	{
		cub->show_full_map = !cub->show_full_map;
		cub->game_paused = cub->show_full_map;
	}
	cub->current_weapon = &cub->weapons[cub->current_weapon_index];
	return (0);
}

int	key_release(int key, t_cub *cub)
{
	if (key >= 0 && key < 65536)
		cub->keys[key] = 0;
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
		cub->player->is_moving = 0;
	return (0);
}