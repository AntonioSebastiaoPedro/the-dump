#include "../includes/thedump.h"

typedef struct s_node
{
	int	x;
	int	y;
}	t_node;

void	init_flow_field(t_cub *cub)
{
	int	y;

	if (cub->map->flow_field)
		return ;
	cub->map->flow_field = ft_calloc(cub->map->height, sizeof(int *));
	if (!cub->map->flow_field)
		return ;
	y = 0;
	while (y < cub->map->height)
	{
		cub->map->flow_field[y] = ft_calloc(cub->map->width, sizeof(int));
		y++;
	}
}

void	free_flow_field(t_cub *cub)
{
	int	y;

	if (!cub->map->flow_field)
		return ;
	y = 0;
	while (y < cub->map->height)
	{
		free(cub->map->flow_field[y]);
		y++;
	}
	free(cub->map->flow_field);
	cub->map->flow_field = NULL;
}

void	update_flow_field(t_cub *cub)
{
	t_node	*queue;
	int		head;
	int		tail;
	int		x;
	int		y;
	int		i;
	int		dx[4] = {0, 0, 1, -1};
	int		dy[4] = {1, -1, 0, 0};
	int		px;
	int		py;

	if (!cub->map->flow_field)
		init_flow_field(cub);
	if (!cub->map->flow_field)
		return ;
	y = 0;
	while (y < cub->map->height)
	{
		x = 0;
		while (x < cub->map->width)
		{
			cub->map->flow_field[y][x] = 999999;
			x++;
		}
		y++;
	}
	queue = ft_calloc(cub->map->width * cub->map->height, sizeof(t_node));
	if (!queue)
		return ;
	head = 0;
	tail = 0;
	px = (int)cub->player->pos_x;
	py = (int)cub->player->pos_y;
	if (px >= 0 && px < cub->map->width && py >= 0 && py < cub->map->height)
	{
		cub->map->flow_field[py][px] = 0;
		queue[tail].x = px;
		queue[tail].y = py;
		tail++;
	}
	while (head < tail)
	{
		x = queue[head].x;
		y = queue[head].y;
		head++;
		i = 0;
		while (i < 4)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (can_walk(cub, nx, ny))
			{
				if (cub->map->flow_field[ny][nx] > cub->map->flow_field[y][x] + 1)
				{
					cub->map->flow_field[ny][nx] = cub->map->flow_field[y][x] + 1;
					queue[tail].x = nx;
					queue[tail].y = ny;
					tail++;
				}
			}
			i++;
		}
	}
	free(queue);
}
