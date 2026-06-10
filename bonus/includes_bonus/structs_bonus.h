#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

# include "macros_bonus.h"
# include <stdbool.h>
# include <pthread.h>

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_loader
{
	pthread_t		thread;
	pthread_mutex_t	mutex;
	int				done;
	int				total_items;
	int				items_loaded;
}	t_loader;



typedef enum e_weapon_type
{
	WEAPON_REVOLVER,
	WEAPON_RIFLE,
	WEAPON_PLASMA,
	WEAPON_COUNT
}	t_weapon_type;

typedef enum e_game_state
{
	LOADING,
	MENU,
	GAME,
	ABOUT,
	LEVEL_TRANSITION,
	VICTORY,
	GAME_OVER
}	t_game_state;

typedef struct s_level_mgr
{
	char	**campaign_maps;
	int		current_level_idx;
	int		total_levels;
	int		is_campaign;
	int		level_completed;
}	t_level_mgr;

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

typedef enum e_enemy_state
{
	EN_IDLE,
	EN_CHASE,
	EN_ATTACK,
	EN_HURT,
	EN_DEAD
}	t_enemy_state;

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
	t_texture	skybox;
}	t_textures;

typedef struct s_menu
{
	int			selected;
	int			total;
	t_texture	loading_img;
	t_texture	about_img;
	t_texture	menu_img;
}	t_menu;

typedef enum e_enemy_type
{
	SOLDIER_TYPE,
	DOG_TYPE,
	OFFICER_TYPE,
}	t_enemy_type;

typedef struct s_enemy_anims
{
	t_texture	idle[8][ENEMY_IDLE_FRAMES];
	t_texture	walk[8][ENEMY_WALK_FRAMES];
	t_texture	attack[8][ENEMY_ATTACK_FRAMES];
	t_texture	dead[ENEMY_DEAD_FRAMES];
}	t_enemy_anims;

typedef struct s_enemy
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			speed;
	double			dist;
	int				hp;
	int				damage;
	int				alive;
	int				is_boss;
	int				frame;
	int				frame_timer;
	int				attack_timer;
	t_enemy_state	state;
	t_enemy_type	type;
}	t_enemy;

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

typedef struct s_crosshair
{
	float	scale;
	int		color;
	bool	enabled;
}	t_crosshair;

typedef struct s_weapon
{
	t_texture		frames[WEAPON_STATES][WEAPON_FRAMES];
	int				state;
	int				current_frame;
	int				frame_timer;
	int				frame_delay;
	t_weapon_type	type;
	unsigned int	shoot_sound;
	t_texture		hud_icon;
	int				current_ammo;
	int				max_ammo;
	int				reserve_ammo;
}	t_weapon;

typedef enum e_item_type
{
	ITEM_BARREL,
	ITEM_GOLD_PLANT,
	ITEM_WELL,
	ITEM_BLUE_KEY,
	ITEM_MEDIC_KIT,
	ITEM_TYPE_COUNT
}	t_item_type;

typedef struct s_item
{
	double			x;
	double			y;
	t_item_type		type;
	bool			active;
	double			dist;
}	t_item;

typedef struct s_door
{
	//t_texture		door_frames[DOOR_FRAMES];
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
	t_door			*door;
	bool			show_mira;
	t_crosshair		crosshair;
	double			last_time;
	double			current_time;
	double			delta_time;
	double			t_elapsed_time;
	double			elapsed_time;
	int				n_door;
	unsigned int	run_sound;
	unsigned int	door_sound;
	unsigned int	back_sound;
	unsigned int	button_sound;
	unsigned int	run_channel;
	unsigned int	back_channel;
	unsigned int	level_done_sound;
	unsigned int	player_death_sound;
	unsigned int	enemy_death_sound;

	t_texture		door_frames[DOOR_FRAMES];
	int				joy_fd;
	int				joy_axis[8];
	t_enemy			*enemies;
	int				enemy_count;
	t_enemy_anims	enemy_anims[ENEMY_TYPE_COUNT];
	double			zbuffer[WIDTH];
	int				player_hp;
	t_level_mgr		level_mgr;
	t_weapon		weapons[WEAPON_COUNT];
	t_weapon		*current_weapon;
	int				current_weapon_index;
	t_loader		loader;
	t_item			*items;
	int				item_count;
	t_texture		item_textures[ITEM_TYPE_COUNT];
	bool			has_blue_key;
	bool			show_full_map;
	bool			game_paused;
	
	/* Performance optimization */
	bool			render_dirty;
	double			last_player_x;
	double			last_player_y;
	double			last_player_angle;
	double			frame_start_time;
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
