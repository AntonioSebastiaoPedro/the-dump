/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:25:08 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/02 02:28:58 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

int	loop_hook(t_cub *cub)
{
	if (cub->state == LOADING)
	{
		update_loading(&cub->loading);
		loading_render(cub);
		if (is_loading_complete(&cub->loading))
		{
			cub->state = MENU;
			init_menu(cub);
		}
	}
	else if (cub->state == MENU)
	{
		update_menu(cub);
		render_menu(cub);
	}
	else if (cub->state == ABOUT)
		render_about(cub);
	else if (cub->state == GAME)
	{
		update_player(cub);
		render(cub);
	}
	return (0);
}
