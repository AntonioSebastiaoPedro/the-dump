/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:42:32 by paulcard          #+#    #+#             */
/*   Updated: 2026/03/26 11:43:11 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

int ft_close(t_cub *cub)
{
    free_cub(cub);
    exit(0);
    return (0);
}

void hook_close(t_cub *cub) 
{
    mlx_hook(cub->mlx->win, 17, 0, ft_close, cub);
}

int	key_press(int key, t_cub *cub)
{
	if (key == 65307)
        ft_close(cub);
	return (0);
}