/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:52:24 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/27 19:21:19 by paulcard         ###   ########.fr       */
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

/* ====== HEADERS DO PROJETO ====== */
# include "../libft/libft.h"
# include "mlx.h"
# include "structs_bonus.h"
# include "macros_bonus.h"

/* ====== LOADING SCREEN ====== */
void		init_loading(t_loading *loading, void *mlx);
void		update_loading(t_loading *loading);
void		loading_render(t_cub *game);
int			is_loading_complete(t_loading *loading);
void		draw_rectangle(t_cub *cub, t_ldg_render *ldg, int color);
void		draw_cover(t_cub *game);

/* ====== MENU ====== */
void		init_menu(t_cub *cub);
void		update_menu(t_cub *cub);
void		render_menu(t_cub *cub);
void		render_about(t_cub *cub);
void		handle_menu_input(int key, t_cub *cub);

/* ====== PARSER ====== */
void		ft_check_args(int ac);
int			ft_check_file(char *filename);
int			ft_open_file(char *filename);
void		ft_validate_file(int ac, char **av);
char		**read_file(char *filename);
t_cub		*parse_cub(int ac, char **av);
int			parse_texture(const char *line, t_cub *cub);
int			parse_color(const char *line, t_cub *cub);
int			validate_rgb_format(const char *line);
int			parse_map(char **lines, int map_start, t_cub *cub);
int			is_empty_line(char *line);
int			is_valid_line_map(char *line);
char		**normalize_map(char **map, int height);
int			validate_map(char **map, int height, t_cub *cub);
int			check_player(char **map, t_cub *cub);
bool		is_player(char c);
int			check_borders(char **map, int height, int width);
int			check_inside(char **map, int height, t_cub *cub);
int			flood_fill(char **map, t_fdfil pos, int height, int width);
int			validate_rgb_format(const char *line);

/* ====== UTILS ====== */
void		print_map(char **map);

int			ft_count_lines(int fd);
void		free_split(char **arr);
t_line_type	get_line_type(const char *line);
char		**copy_map(char **lines, int map_start, int height);
void		free_map(char **map, int height);
void		free_split(char **arr);
void		free_config(t_cub *cub);
void		free_mlx(t_cub *cub);
void		free_textures(t_cub *cub);
void		free_cub(t_cub *cub);
int			load_textures(t_cub *cub);
int			scale_texture(t_cub *cub, t_texture *tex, int new_w, int new_h);
int			ft_fprintf_fd(int fd, const char *format, ...);
int			ft_sprintf(char *str, const char *format, ...);
char		ft_delim(const char *s);
char		**ft_split_new(const char *s, const char *delim);

/* ====== MLX SETUP ====== */
t_mlx		*init_mlx(void);
void		hook_close(t_cub *cub);
int			key_press(int key, t_cub *cub);
int			key_release(int key, t_cub *cub);
int			loop_hook(t_cub *cub);

/* ====== RENDER ====== */
void		draw_minimap(t_cub *cub);
void		render(t_cub *cub);
void		ft_put_pixel(t_cub *cub, int x, int y, int color);
void		raycasting(int col, t_ray *ray, t_cub *cub);
void		dda(t_ray *ray, t_cub *cub);
void		draw_vertical_line(int col, t_ray *ray, t_cub *cub);
void		calculate_texture(t_ray *ray, t_cub *cub);

/* ====== PLAYER ====== */
t_player	*init_player(t_cub *cub);
void		update_player(t_cub *cub);
void		set_dir_vectors(t_player *player);
void		rotate(t_player *player, double rot);
void		update_mouse(t_cub *cub);

#endif
