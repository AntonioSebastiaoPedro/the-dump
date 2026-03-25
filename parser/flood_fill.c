/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-25 08:06:28 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-25 13:26:00 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"

static int	check_neighbor(char **map, int nx, int ny, int limits[2])
{
	if (nx < 0 || ny < 0 || ny >= limits[1] || nx >= limits[0])
		return (0);
	if (map[ny][nx] == ' ')
		return (0);
	return (1);
}

int	flood_fill(char **map, int start_x, int start_y, int height, int width)
{
	int	*queue;
	int	front;
	int	rear;
	int	limits[2];
	int	dx[4];
	int	dy[4];
	int	d;
	int	nx;
	int	ny;
	int	cx;
	int	cy;

	dx[0] = 1;
	dx[1] = -1;
	dx[2] = 0;
	dx[3] = 0;
	dy[0] = 0;
	dy[1] = 0;
	dy[2] = 1;
	dy[3] = -1;
	limits[0] = width;
	limits[1] = height;
	queue = malloc(sizeof(int) * height * width * 2);
	if (!queue)
		return (0);
	front = 0;
	rear = 0;
	queue[rear++] = start_x;
	queue[rear++] = start_y;
	map[start_y][start_x] = 'F';
	while (front < rear)
	{
		cx = queue[front++];
		cy = queue[front++];
		d = 0;
		while (d < 4)
		{
			nx = cx + dx[d];
			ny = cy + dy[d];
			if (!check_neighbor(map, nx, ny, limits))
				return (free(queue), 0);
			if (map[ny][nx] != '1' && map[ny][nx] != 'F')
			{
				map[ny][nx] = 'F';
				queue[rear++] = nx;
				queue[rear++] = ny;
			}
			d++;
		}
	}
	return (free(queue), 1);
}

