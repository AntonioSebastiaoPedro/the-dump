#ifndef THEDUMP_H
# define THEDUMP_H

/* ====== LIBS PADRÃO ====== */
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <limits.h>
# include <stdbool.h>
# include <stdint.h>
# include <X11/Xlib.h>
# include <sys/time.h>

/* ====== HEADERS DO PROJETO ====== */
# include "libft.h"
# include <mlx.h>
# include "../bass/bass.h"
# include "structs.h"
# include "macros.h"

/* ====== LOADING SCREEN ====== */
void			init_loading(t_cub *cub, t_loading *loading, void *mlx);
void			update_loading(t_loading *loading);
void			loading_render(t_cub *game);
int				is_loading_complete(t_loading *loading);
void			draw_rectangle(t_cub *cub, t_ldg_render *ldg, int color);
void			draw_texture_img(t_cub *cub, t_texture *tex);

/* ====== MENU ====== */
void			init_menu(t_cub *cub);
void			update_menu(t_cub *cub);
void			render_menu(t_cub *cub);
void			render_about(t_cub *cub);
void			handle_menu_input(int key, t_cub *cub);

/* ====== PARSER ====== */
void			ft_check_args(int ac);
int				ft_check_file(char *filename);
int				ft_open_file(char *filename);
void			ft_validate_file(int ac, char **av);
char			**read_file(char *filename);
t_cub			*parse_cub(int ac, char **av);
int				parse_texture(const char *line, t_cub *cub);
int				set_cub_texture(char **dest, char **parts, char *dir);
int				parse_color(const char *line, t_cub *cub);
int				validate_rgb_format(const char *line);
int				parse_map(char **lines, int map_start, t_cub *cub);
int				is_empty_line(char *line);
int				is_valid_line_map(char *line);
char			**normalize_map(char **map, int height);
int				validate_map(char **map, int height, t_cub *cub);
int				check_player(char **map, t_cub *cub);
bool			is_player(char c);
int				check_borders(char **map, int height, int width);
int				check_inside(char **map, int height, t_cub *cub);
int				flood_fill(char **map, t_fdfil pos, int height, int width);
int				validate_rgb_format(const char *line);

/* ====== UTILS ====== */
void			print_map(char **map);

int				ft_count_lines(int fd);
void			free_split(char **arr);
t_line_type		get_line_type(const char *line);
char			**copy_map(char **lines, int map_start, int height);
void			free_map(char **map, int height);
void			free_split(char **arr);
void			free_config(t_cub *cub);
void			free_mlx(t_cub *cub);
void			free_textures(t_cub *cub);
void			free_cub(t_cub *cub);
void			clear_map(t_cub *cub);
void			clear_config(t_cub *cub);
int				load_textures(t_cub *cub);
int				scale_texture(t_cub *cub, t_texture *tex, int new_w, int new_h);
int				ft_fprintf_fd(int fd, const char *format, ...);
int				ft_sprintf(char *str, const char *format, ...);
char			ft_delim(const char *s);
char			**ft_split_new(const char *s, const char *delim);
bool			load_floor_ceiling_texture(t_cub *cub);

/* ====== MLX SETUP ====== */
int				ft_close(t_cub *cub);
t_mlx			*init_mlx(void);
void			hook_close(t_cub *cub);
int				key_press(int key, t_cub *cub);
int				key_release(int key, t_cub *cub);
int				loop_hook(t_cub *cub);

/* ====== RENDER ====== */
void			draw_minimap(t_cub *cub);
void			render(t_cub *cub);
void			ft_put_pixel(t_cub *cub, int x, int y, int color);
void			pixel_put(t_cub *cub, int x, int y, int color);
void			raycasting(int col, t_ray *ray, t_cub *cub);
void			dda(t_ray *ray, t_cub *cub);
void			draw_vertical_line(int col, t_ray *ray, t_cub *cub);
void			calculate_texture(t_ray *ray, t_cub *cub);
unsigned int	get_texture_color(t_texture *texture, int x, int y);
t_texture		*get_texture(t_ray *ray, t_cub *cub);
void			put_fc_color(t_cub *cub, int col, int y, int is_floor);
void			put_floor_or_ceiling(t_cub *cub, t_floorceil_args a);
int				load_single_texture(t_cub *cub, t_texture *tex,
					const char *path);
void			draw_floor_ceiling_pixel(t_cub *cub, t_floorceil_args a,
					t_ray *ray);
void			draw_mira(t_cub *cub);
void			draw_hp_hud(t_cub *cub);
void			draw_ammo_hud(t_cub *cub);
void			draw_tactical_map(t_cub *cub);
void			draw_skybox(t_cub *cub);
void			draw_char_pixel(t_cub *cub, int x, int y, int character, int color);
void			draw_string_graphics(t_cub *cub, int x, int y, char *str, int color);
void			draw_empty_rect(t_cub *cub, t_vec start, t_vec rect_size, uint32_t color);


/* ====== PLAYER ====== */
t_player		*init_player(t_cub *cub);
void			update_player(t_cub *cub);
void			set_dir_vectors(t_player *player);
void			update_mouse(t_cub *cub);
void			rotate(t_player *player, double rot);

/* ====== BONUS (WEAPON) ====== */
int				mouse_hook(int key, int x, int y, void *param);
void			set_weapon_state(t_weapon *weapon, int new_state);
void			free_weapon_textures(t_cub *cub);
void			on_mouse_click(t_cub *cub);
void			update_weapon(t_cub *cub);
void			draw_weapon(t_cub *cub);
void			switch_weapon_next(t_cub *cub);

/* ====== PROJECTILES ====== */
void			init_projectiles(t_cub *cub);
void			fire_projectile(t_cub *cub, double dir_x, double dir_y, int damage);

/* ====== BONUS (DOORS) ====== */
void			init_doors(t_cub *cub);
t_door			*get_door_at(t_cub *cub, int x, int y);
t_door			*find_door_in_front(t_cub *cub);
void			try_interact_door(t_cub *cub);
void			update_doors(t_cub *cub);
int				is_door_open(t_cub *cub, int x, int y);
int				load_door_textures(t_cub *cub);
void			free_door_textures(t_cub *cub);
int				can_walk(t_cub *cub, int x, int y);

/* ====== JOYSTICK ====== */
void			init_joystick(t_cub *cub);
void			poll_joystick(t_cub *cub);
void			close_joystick(t_cub *cub);
void			toggle_mouse_vis(t_cub *cub);

/* ====== AUDIO ====== */
bool			init_audio(t_cub *cub);
void			play_weapon_sound(t_cub *cub);
void			play_door_sound(t_cub *cub);
void			play_button_sound(t_cub *cub);
void			play_run_sound(t_cub *cub);
void			stop_run_sound(t_cub *cub);
void			play_level_done_sound(t_cub *cub);
void			play_player_death_sound(t_cub *cub);
void			play_enemy_death_sound(t_cub *cub);
void			free_audio(t_cub *cub);

/* ====== ENEMY ====== */
void			init_enemies(t_cub *cub);
void			update_enemies(t_cub *cub);
void			draw_enemies(t_cub *cub);
int				load_enemy_textures(t_cub *cub);
void			free_enemies(t_cub *cub);
void			free_enemy_textures(t_cub *cub);
void			enemy_take_damage(t_cub *cub);
void			update_enemy_animation(t_enemy *e);
t_texture		*get_enemy_texture(t_cub *cub, t_enemy *e);
void			enemy_ai_idle(t_cub *cub, t_enemy *e);
void			enemy_ai_chase(t_cub *cub, t_enemy *e);
void			enemy_ai_attack(t_cub *cub, t_enemy *e);
int				enemy_has_line_of_sight(t_cub *cub, t_enemy *e);
int				enemy_can_move(t_cub *cub, double x, double y);

/* ====== ITEM SYSTEM ====== */
void			init_items(t_cub *cub);
void			update_items(t_cub *cub);
void			draw_items(t_cub *cub);
int				load_item_textures(t_cub *cub);
void			free_items(t_cub *cub);
void			player_heal(t_cub *cub, int amount);
void			player_add_ammo(t_cub *cub);

/* ====== LEVEL MANAGER ====== */
void			init_campaign(t_cub *cub, int ac, char **av);
int				check_level_completion(t_cub *cub);
void			load_next_level(t_cub *cub);
void			restart_game(t_cub *cub);
void			render_transition_screen(t_cub *cub);
void			render_game_over(t_cub *cub);
void			render_victory_screen(t_cub *cub);
int				parse_map_into_cub(t_cub *cub, char *filename);
void			start_loader_thread(t_cub *cub);
void			increment_loader(t_cub *cub);

/* ====== PROFILING ====== */
void			prof_enable(int enable);
void			prof_start(void);
long			prof_end(const char *name);
void			prof_start_named(struct timeval *t);
long			prof_end_named(const char *name, struct timeval *t);

/* ====== FPS METER ====== */
void			fps_meter_enable(void);
void			fps_meter_record(double frame_time_ms);
void			fps_meter_print(void);

/* ====== THREADING ====== */
t_thread_pool	*init_raycast_pool(t_cub *cub);
void			cleanup_raycast_pool(t_thread_pool *pool);
void			start_raycast_threads(t_cub *cub);
void			wait_raycast_threads(t_cub *cub);

t_update_thread	*init_update_thread(t_cub *cub);
void			cleanup_update_thread(t_update_thread *upd);

/* ====== UTILITY FUNCTIONS ====== */
unsigned int	apply_depth_shading(unsigned int color, double dist);
int				is_walkable_aabb(t_cub *cub, double new_x, double new_y, double size);
double			ft_get_time(void);

#endif