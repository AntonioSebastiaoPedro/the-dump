/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:57:21 by paulcard          #+#    #+#             */
/*   Updated: 2026/03/27 13:57:21 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_config
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor_color;
	int		ceiling_color;
}	t_config;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	dir;
}	t_player;

typedef struct s_textures
{
	void	*no;
	void	*so;
	void	*we;
	void	*ea;
	int		width;
	int		height;
}	t_textures;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_mlx;

typedef struct s_cub
{
	t_map		*map;
	t_config	*config;
	t_player	*player;
	t_mlx		*mlx;
	t_textures	*textures;
	int			floor_color;
	int			ceiling_color;
}	t_cub;

typedef enum e_line_type
{
	TEXTURE,
	COLOR,
	MAP,
	EMPTY,
	INVALID
}	t_line_type;

#endif
