#include "../includes/thedump.h"

void	free_map(char **map, int height)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	clear_map(t_cub *cub)
{
	if (cub->map)
	{
		if (cub->map->grid)
		{
			free_map(cub->map->grid, cub->map->height);
			cub->map->grid = NULL;
		}
		free_flow_field(cub);
		cub->map->height = 0;
		cub->map->width = 0;
	}
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	clear_config(t_cub *cub)
{
	if (cub->config)
	{
		if (cub->config->no)
			free(cub->config->no);
		if (cub->config->so)
			free(cub->config->so);
		if (cub->config->we)
			free(cub->config->we);
		if (cub->config->ea)
			free(cub->config->ea);
		if (cub->config->f_tex)
			free(cub->config->f_tex);
		if (cub->config->c_tex)
			free(cub->config->c_tex);
		cub->config->no = NULL;
		cub->config->so = NULL;
		cub->config->we = NULL;
		cub->config->ea = NULL;
		cub->config->f_tex = NULL;
		cub->config->c_tex = NULL;
		cub->config->floor_color = -1;
		cub->config->ceiling_color = -1;
	}
}

void	free_config(t_cub *cub)
{
	if (cub->config)
	{
		clear_config(cub);
		free(cub->config);
		cub->config = NULL;
	}
}

void	free_mlx(t_cub *cub)
{
	if (cub->mlx)
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
		cub->mlx = NULL;
	}
}