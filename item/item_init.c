#include "../includes/cub.h"

static void	add_item(t_cub *cub, double x, double y, t_item_type type)
{
	t_item	*new_items;
	int		i;

	new_items = malloc(sizeof(t_item) * (cub->item_count + 1));
	if (!new_items)
		return ;
	i = 0;
	while (i < cub->item_count)
	{
		new_items[i] = cub->items[i];
		i++;
	}
	new_items[cub->item_count].x = x + 0.5;
	new_items[cub->item_count].y = y + 0.5;
	new_items[cub->item_count].type = type;
	new_items[cub->item_count].active = true;
	new_items[cub->item_count].dist = 0;
	if (cub->items)
		free(cub->items);
	cub->items = new_items;
	cub->item_count++;
}

void	init_items(t_cub *cub)
{
	int	y;
	int	x;

	cub->items = NULL;
	cub->item_count = 0;
	y = 0;
	while (y < cub->map->height)
	{
		x = 0;
		while (x < cub->map->width)
		{
			if (cub->map->grid[y][x] == 'B')
				add_item(cub, x, y, ITEM_BARREL);
			else if (cub->map->grid[y][x] == 'G')
				add_item(cub, x, y, ITEM_GOLD_PLANT);
			else if (cub->map->grid[y][x] == 'P' || cub->map->grid[y][x] == 'O')
				add_item(cub, x, y, ITEM_WELL);
			else if (cub->map->grid[y][x] == 'K')
				add_item(cub, x, y, ITEM_BLUE_KEY);
			else if (cub->map->grid[y][x] == 'H')
				add_item(cub, x, y, ITEM_MEDIC_KIT);
			x++;
		}
		y++;
	}
}

int	load_item_textures(t_cub *cub)
{
	if (!load_single_texture(cub, &cub->item_textures[ITEM_BARREL], "assets/obj/barrel1780649808.xpm")) return (0);
	if (!load_single_texture(cub, &cub->item_textures[ITEM_GOLD_PLANT], "assets/obj/gold-plant1780649808.xpm")) return (0);
	if (!load_single_texture(cub, &cub->item_textures[ITEM_WELL], "assets/obj/well-water1780649808.xpm")) return (0);
	if (!load_single_texture(cub, &cub->item_textures[ITEM_BLUE_KEY], "assets/obj/bkue-key1780649808.xpm")) return (0);
	if (!load_single_texture(cub, &cub->item_textures[ITEM_MEDIC_KIT], "assets/obj/medic-kit1780649808.xpm")) return (0);
	return (1);
}

void	free_items(t_cub *cub)
{
	int	i;

	if (cub->items)
		free(cub->items);
	i = 0;
	while (i < ITEM_TYPE_COUNT)
	{
		if (cub->item_textures[i].img)
			mlx_destroy_image(cub->mlx->mlx, cub->item_textures[i].img);
		i++;
	}
}
