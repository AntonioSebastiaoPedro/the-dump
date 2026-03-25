/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-25 14:46:31 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-25 14:46:31 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

void	exit_error(char *msg, t_mlx *mlx)
{
	if (msg)
        (ft_putstr_fd("Error: ", 2), ft_putendl_fd(msg, 2));
	if (mlx)
	{
		if (mlx->img)
			mlx_destroy_image(mlx->mlx, mlx->img);
		if (mlx->win)
			mlx_destroy_window(mlx->mlx, mlx->win);
		if (mlx->mlx)
			(mlx_destroy_display(mlx->mlx), free(mlx->mlx));
        if (mlx->game)
            free_game(mlx->game);
	}
	exit(EXIT_FAILURE);
}