/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:09:15 by paulcard          #+#    #+#             */
/*   Updated: 2026/03/27 10:16:55 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/cub.h"


int	main(int ac, char **av)
{
	t_cub	*cub;
	cub = parse_cub(ac, av);
	if (!cub)
		return (1);
	cub->mlx = init_mlx();
	if (!cub->mlx)
	{
		free_cub(cub);
		return (1);
	}
	render(cub);
	mlx_loop(cub->mlx->mlx);
	free_cub(cub);
	return (0);

	
}

