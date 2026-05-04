/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamandio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:52:24 by paulcard          #+#    #+#             */
/*   Updated: 2026/05/04 20:07:39 by aamandio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_BONUS_H
# define CUB_BONUS_H

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

/* ====== HEADERS DO PROJETO ====== */
# include "../libft/libft.h"
# include <mlx.h>
# include <mlx_int.h>
# include "../bass/bass.h"
# include "structs_bonus.h"
# include "macros_bonus.h"

/* ====== LOADING SCREEN ====== */
void			init_loading(t_loading *loading, void *mlx);
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
int				load_textures(t_cub *cub);
int				scale_texture(t_cub *cub, t_texture *tex, int new_w, int new_h);
int				ft_fprintf_fd(int fd, const char *format, ...);
int				ft_sprintf(char *str, const char *format, ...);
char			ft_delim(const char *s);
char			**ft_split_new(const char *s, const char *delim);
bool			load_floor_ceiling_texture(t_cub *cub);

/* ====== MLX SETUP ====== */
t_mlx			*init_mlx(void);
void			hook_close(t_cub *cub);
int				key_press(int key, t_cub *cub);
int				key_release(int key, t_cub *cub);
int				loop_hook(t_cub *cub);

/* ====== RENDER ====== */
void			draw_minimap(t_cub *cub);
void			render(t_cub *cub);
void			ft_put_pixel(t_cub *cub, int x, int y, int color);
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

/* ====== PLAYER ====== */
t_player		*init_player(t_cub *cub);
void			update_player(t_cub *cub);
void			set_dir_vectors(t_player *player);
void			update_mouse(t_cub *cub);
void			rotate(t_player *player, double rot);

/* ====== BONUS (WEAPON) ====== */
int				mouse_hook(int key, int x, int y, t_cub *cub);
void			set_weapon_state(t_weapon *weapon, int new_state);
void			free_weapon_textures(t_cub *cub);
void			on_mouse_click(t_cub *cub);
void			update_weapon(t_cub *cub);
void			draw_weapon(t_cub *cub);

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

/* ====== AUDIO ====== */
bool			init_audio(t_cub *cub);
void			play_weapon_sound(t_cub *cub);
void			play_door_sound(t_cub *cub);
void			play_button_sound(t_cub *cub);
void			play_run_sound(t_cub *cub);
void			stop_run_sound(t_cub *cub);
void			free_audio(t_cub *cub);
#endif
