/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:52:24 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/17 10:50:45 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

/* ====== LIBS PADRÃO ====== */
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <float.h>
# include <limits.h>
# include <stdbool.h>

/* ====== HEADERS DO PROJETO ====== */
# include "../libft/libft.h"
# include "minilibx-linux/mlx_int.h"
# include "mlx.h"
# include "structs.h"
# include "macros.h"

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

/* ====== UTILS ====== */
int			ft_count_lines(int fd);
void		free_split(char **arr);
t_line_type	get_line_type(const char *line);
char		**copy_map(char **lines, int map_start, int height);
void		free_cub(t_cub *cub);
void		free_map(char **map, int height);
void		print_map(char **map);
int			ft_fprintf_fd(int fd, const char *format, ...);
int			ft_sprintf(char *str, const char *format, ...);
char		ft_delim(const char *s);
char		**ft_split_new(const char *s, const char *delim);

/* ====== MLX SETUP ====== */
t_mlx		*init_mlx(void);
void		put_pixel(t_cub *cub, int x, int y, int color);
void		exit_error(char *msg, t_cub *cub);
void		hook_close(t_cub *cub);
int			key_press(int key, t_cub *cub);
int			key_release(int key, t_cub *cub);
int			loop_hook(t_cub *cub);

/* ====== RENDER ====== */
void		render(t_cub *cub);
void		draw_walls(t_cub *cub);
void		draw_ver_line(t_cub *cub, int x, t_ray *ray);

/* ====== PLAYER ====== */
t_player	*init_player(t_cub *cub);
void		update_player(t_cub *cub);
void		set_dir_vectors(t_player *player);

#endif
