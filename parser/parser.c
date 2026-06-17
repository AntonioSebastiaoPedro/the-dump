#include "../includes/thedump.h"

static int	handle_line(char *line, t_cub *cub, int *map_start, int i)
{
	t_line_type	type;

	type = get_line_type(line);
	if (type == TEXTURE)
	{
		if (parse_texture(line, cub) == 0)
			return (0);
	}
	else if (type == COLOR)
	{
		if (parse_color(line, cub) == 0)
			return (0);
	}
	else if (type == MAP)
	{
		if (*map_start == -1)
			*map_start = i;
		return (2);
	}
	else if (type == INVALID && line[0] != '\0')
	{
		ft_putendl_fd("Error\nMapa invalido", 2);
		return (0);
	}
	return (1);
}

static int	is_config_complete(t_cub *cub)
{
	if (!cub->config->no || !cub->config->so || !cub->config->we
		|| !cub->config->ea)
	{
		ft_putendl_fd("Error\nConfiguracao incompleta", 2);
		return (0);
	}
	if ((cub->config->floor_color == -1 && !cub->config->f_tex)
		|| (cub->config->ceiling_color == -1 && !cub->config->c_tex))
	{
		ft_putendl_fd("Error\nConfiguracao incompleta", 2);
		return (0);
	}
	return (1);
}

static int	process_config(char **lines, t_cub *cub, int *map_start)
{
	int	i;
	int	res;

	i = 0;
	while (lines[i] != NULL)
	{
		res = handle_line(lines[i], cub, map_start, i);
		if (res == 0)
			return (0);
		if (res == 2)
			break ;
		i++;
	}
	if (*map_start == -1)
	{
		ft_putendl_fd("Error\nFicheiro Nao encontrado no mapa", 2);
		return (0);
	}
	if (!is_config_complete(cub))
		return (0);
	return (1);
}

t_cub	*init_cub(void)
{
	t_cub	*cub;

	cub = ft_calloc(1, sizeof(t_cub));
	if (!cub)
		return (NULL);
	cub->map = ft_calloc(1, sizeof(t_map));
	cub->config = ft_calloc(1, sizeof(t_config));
	cub->player = ft_calloc(1, sizeof(t_player));
	cub->textures = ft_calloc(1, sizeof(t_textures));
	if (!cub->map || !cub->config || !cub->player || !cub->textures)
		return (free_cub(cub), NULL);
	cub->config->ceiling_color = -1;
	cub->menu.loading_img.img = NULL;
	cub->menu.about_img.img = NULL;
	cub->enemies = NULL;
	cub->door = NULL;
	return (cub);
}

int	parse_map_into_cub(t_cub *cub, char *filename)
{
	char	**lines;
	int		map_start;

	map_start = -1;
	if (!ft_check_file(filename))
		return (0);
	lines = read_file(filename);
	if (!lines)
		return (0);
	if (!process_config(lines, cub, &map_start))
	{
		free_split(lines);
		return (0);
	}
	if (parse_map(lines, map_start, cub) == 0)
	{
		free_split(lines);
		return (0);
	}
	free_split(lines);
	return (1);
}

t_cub	*parse_cub(int ac, char **av)
{
	t_cub	*cub;

	if (ac != 1)
	{
		//ft_validate_file(ac, av);
		return(NULL);
	}
	cub = init_cub();
	if (!cub)
		return (NULL);
	init_campaign(cub, ac, av);
	if (!parse_map_into_cub(cub, cub->level_mgr.campaign_maps[0]))
		return (free_cub(cub), NULL);
	return (cub);
}