/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:09:15 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/20 20:42:32 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/cub.h"

static int	load_single_texture(t_cub *cub, t_texture *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(cub->mlx->mlx, path, &tex->width,
		&tex->height);
	if (!tex->img)
		return (0);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
		&tex->endian);
	if (!tex->addr)
		return (0);
	return (1);
}

int	load_textures(t_cub *cub)
{
	if (!load_single_texture(cub, &cub->textures->no, cub->config->no))
		return (0);
	if (!load_single_texture(cub, &cub->textures->so, cub->config->so))
		return (0);
	if (!load_single_texture(cub, &cub->textures->we, cub->config->we))
		return (0);
	if (!load_single_texture(cub, &cub->textures->ea, cub->config->ea))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_cub	*cub;
	cub = parse_cub(ac, av);
	if (!cub)
		return (1);
	cub->mlx = init_mlx();
	if (!cub->mlx)
		return (free_cub(cub),1);
	if (!init_player(cub))
		return (free_cub(cub),1);
	if (!load_textures(cub))
		return (free_cub(cub), 1);
	hook_close(cub);
	mlx_hook(cub->mlx->win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->mlx->win, 3, 1L << 1, key_release, cub);
	mlx_loop_hook(cub->mlx->mlx, loop_hook, cub);
	mlx_loop(cub->mlx->mlx);
	free_cub(cub);
	return (0);
}

