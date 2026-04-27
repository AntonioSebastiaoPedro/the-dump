/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:57:21 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/27 19:05:21 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/* WEAPON MACROS */
# define WEAPON_FRAMES 6
# define WEAPON_STATES 3
# define WEAPON_IDLE 0
# define WEAPON_MOVE 1
# define WEAPON_SHOT 2
# define WEAPON_TRANSPARENT 0xFFFF00FF

typedef enum e_game_state
{
	MENU,
	GAME,
	ABOUT
}	t_game_state;

typedef struct s_menu
{
	int		selected;
	int		total;
}	t_menu;

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

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_textures
{
	t_texture	no;
	t_texture	so;
	t_texture	we;
	t_texture	ea;
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
}	t_mlx;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	camera_x;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	int		hit;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_impact;
	int		texture_column;
	double	step_texture;
	double	texture_pos;
}	t_ray;

typedef struct s_mouse
{
	int		center_x;
	int		center_y;
	int		x;
	int		y;
	int		delta_x;
	bool	show_mouse;
}	t_mouse;

typedef struct s_weapon
{
	t_texture	frames[WEAPON_FRAMES][WEAPON_FRAMES];
	int			state;
	int			current_frame;
	int			frame_timer;
}	t_weapon;

typedef struct s_cub
{
	t_map			*map;
	t_config		*config;
	t_player		*player;
	t_mlx			*mlx;
	t_textures		*textures;
	t_menu			menu;
	t_game_state	state;
	int				floor_color;
	int				ceiling_color;
	int				keys[65536];
	t_mouse			mouse;
	t_weapon		weapon;
}	t_cub;

typedef struct s_fdfil
{
	int	x;
	int	y;
}	t_fdfil;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}			t_rgb;

typedef enum e_line_type
{
	TEXTURE,
	COLOR,
	MAP,
	EMPTY,
	INVALID
}	t_line_type;

#endif
