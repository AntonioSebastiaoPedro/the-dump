/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mira_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:42:46 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/04 15:50:30 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub_bonus.h"

void	draw_mira(t_cub *cub)
{
	int	cx;
	int	cy;
	int	i;

	if (!cub->show_mira)
		return ;
	cx = WIDTH / 2;
	cy = HEIGHT / 2;
	i = -10;
	while (i <= 10)
	{
		ft_put_pixel(cub, cx + i, cy, GREEN);
		ft_put_pixel(cub, cx, cy + i, GREEN);
		i++;
	}
}
