/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:42:32 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/01 16:33:23 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

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

static void	toggle_mouse(t_cub *cub)
{
	cub->mouse.show_mouse = !cub->mouse.show_mouse;
	if (cub->mouse.show_mouse)
		mlx_mouse_show(cub->mlx->mlx, cub->mlx->win);
	else
		mlx_mouse_hide(cub->mlx->mlx, cub->mlx->win);
}

t_door	*get_door_at(t_cub *cub, int x, int y)
{
	int	i;

	i = 0;
	while (i < cub->n_door)
	{
		if (cub->door[i].x == x && cub->door[i].y == y)
			return (&cub->door[i]);
		i++;
	}
	return (NULL);
}

t_door	*find_door_in_front(t_cub *cub)
{
	int		x;
	int		y;
	double	dist;
	t_door	*door;

	dist = 0.0;
	while (dist <= MAX_DOOR_DIST)
	{
		// verificar se nessa posicao ha porta e retornar a porta em causa...
		x = (int)(cub->player->pos_x + cub->player->dir_x * dist);
		y = (int)(cub->player->pos_y + cub->player->dir_y * dist);
		if (cub->map->grid[y][x] == '1') // Evita abrir porta com parede em frente
			return (NULL);
		door = get_door_at(cub, x, y);
		if (door)
			return (door);
		dist += 0.1;
	}
	return (NULL);
}

void	try_interact_door(t_cub *cub)
{
	t_door	*door;

	door = find_door_in_front(cub);
	if (!door)
		return ;
	if (door->state == DOOR_OPENING || door->state == DOOR_CLOSING)
		return ;
	if (door->state == DOOR_OPEN)
		door->state = DOOR_CLOSING;
	else if (door->state == DOOR_CLOSED)
		door->state = DOOR_OPENING;
}

int	key_press(int key, t_cub *cub)
{
	if (key == ESC && cub->state == GAME)
		ft_close(cub);
	if (key == KEY_P && cub->state == GAME)
		toggle_mouse(cub);
	if (cub->state == MENU || cub->state == ABOUT)
		handle_menu_input(key, cub);
	if (key >= 0 && key < 65536)
		cub->keys[key] = 1;
	if (key == KEY_W || key == KEY_S || key == KEY_A || key == KEY_D)
		cub->player->is_moving = 1;
	if (key == SPACE)
		try_interact_door(cub);
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
