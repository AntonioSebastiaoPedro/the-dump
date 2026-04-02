/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:46:31 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/02 13:26:56 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

void	exit_error(char *msg, t_cub *cub)
{
	if (msg)
		(ft_putstr_fd("Error: ", 2), ft_putendl_fd(msg, 2));
	if (cub && cub->mlx)
	{
		if (cub->mlx->img)
			mlx_destroy_image(cub->mlx->mlx, cub->mlx->img);
		if (cub->mlx->win)
			mlx_destroy_window(cub->mlx->mlx, cub->mlx->win);
		if (cub->mlx->mlx)
		{
			mlx_destroy_display(cub->mlx->mlx);
			free(cub->mlx->mlx);
		}
		free(cub->mlx);
	}
	if (cub)
		free_cub(cub);
	exit(EXIT_FAILURE);
}
