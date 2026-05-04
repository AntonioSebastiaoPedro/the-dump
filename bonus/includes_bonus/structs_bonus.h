/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:57:21 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/04 15:49:08 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

# include "macros_bonus.h"
# include <stdbool.h>

typedef enum e_game_state
{
	LOADING,
	MENU,
	GAME,
	ABOUT
}	t_game_state;

typedef enum e_line_type
{
	TEXTURE,
	COLOR,
	MAP,
	EMPTY,
	INVALID
}	t_line_type;

typedef enum e_door_state
{
	DOOR_CLOSED,
	DOOR_OPENING,
	DOOR_OPEN,
	DOOR_CLOSING
}	t_door_state;

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
	t_texture	floor;
	t_texture	ceiling;
}	t_textures;

typedef struct s_menu
{
	int			selected;
	int			total;
	t_texture	cover;
	t_texture	about_img;
	t_texture	menu_img;
}	t_menu;

typedef struct s_loading
{
	int		progress;
	int		max_progress;
	int		frame_count;
}	t_loading;

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
	char	*f_tex;
	char	*c_tex;
	int		floor_color;
	int		ceiling_color;
}	t_config;

typedef struct s_floorceil_args
{
	int	col;
	int	y;
	int	is_floor;
}	t_floorceil_args;

typedef struct s_tex_info
{
	int	w;
	int	h;
}	t_tex_info;

typedef struct s_floorceil_ctx
{
	double	fx;
	double	fy;
	double	dist;
}	t_floorceil_ctx;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	char	dir;
	int		is_moving;
}	t_player;

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
	bool	is_door;
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
	t_texture	frames[WEAPON_STATES][WEAPON_FRAMES];
	int			state;
	int			current_frame;
	int			frame_timer;
	int			frame_delay;
}	t_weapon;

typedef struct s_door
{
	int				x;
	int				y;
	t_door_state	state;
	int				frame;
	int				timer;
}	t_door;

typedef struct s_cub
{
	t_map			*map;
	t_config		*config;
	t_player		*player;
	t_mlx			*mlx;
	t_textures		*textures;
	t_loading		loading;
	t_menu			menu;
	t_game_state	state;
	int				floor_color;
	int				ceiling_color;
	int				keys[65536];
	t_mouse			mouse;
	t_weapon		weapon;
	t_texture		door_frames[DOOR_FRAMES];
	t_door			*door;
	bool			show_mira;
	int				n_door;
	unsigned int	weapon_sound;
	unsigned int	run_sound;
	unsigned int	door_sound;
	unsigned int	back_sound;
	unsigned int	button_sound;
	unsigned int	run_channel;
	unsigned int	back_channel;
}	t_cub;

typedef struct s_ldg_render
{
	int		x;
	int		y;
	int		w;
	int		h;
	int		bar_width;
	int		bar_height;
	int		filled_width;
}	t_ldg_render;

typedef struct s_fdfil
{
	int	x;
	int	y;
}	t_fdfil;

typedef struct s_mmap_render
{
	double	scale;
	int		off_x;
	int		off_y;
}	t_mmap_render;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}			t_rgb;

typedef struct s_draw_weapon
{
	int				start_x;
	int				start_y;
	unsigned int	color;
	int				scaled_width;
	int				scaled_height;
}	t_draw_weapon;

typedef struct s_draw
{
	t_cub	*cub;
	int		margin;
	int		*y;
	int		color;
}	t_draw;

#endif
