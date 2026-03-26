/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-17 11:52:24 by paulcard          #+#    #+#             */
/*   Updated: 2026-03-17 11:52:24 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include "minilibx-linux/mlx_int.h"
# include <mlx.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <float.h>
# include <limits.h>
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

/*	*/
# define SPACE 32
# define TAB '\t'
# define NEWLINE '\n'
# define ENDLINE '\0'
# define COMMA ','
# define CARRIAGE '\r'

# define NORTE "NO"
# define SUL "SO"
# define LESTE "EA"
# define OESTE "WE"

/*		PARSER				*/
void		ft_check_args(int ac);
int			ft_check_file(char *filename);
int			ft_open_file(char *filename);
void		ft_validate_file(int ac, char **av);
char		**read_file(char *filename);
t_cub		*parse_cub(int ac, char **av);
int			parse_texture(const char *line, t_cub *cub);
int			parse_color(const char *line, t_cub *cub);
int			parse_map(char **lines, int map_start, t_cub *cub);
int			is_empty_line(char *line);
int			is_valid_line_map(char *line);
char		**normalize_map(char **map, int height);
int			validate_map(char **map, int height, t_cub *cub);
int			check_player(char **map, t_cub *cub);
bool		is_player(char c);
int			check_borders(char **map, int height, int width);
int			check_inside(char **map, int height, t_cub *cub);
int			flood_fill(char **map, int x, int y, int height, int width);

/*		UTILS		*/
int			ft_count_lines(int fd);
void		free_split(char **arr);
t_line_type get_line_type(const char *line);
char		**copy_map(char **lines, int map_start, int height);
void		free_cub(t_cub *cub);
void		free_map(char **map, int height);
void		print_map(char **map);

/*	MLX SETUP	*/
t_mlx		*init_mlx(void);
void		put_pixel(t_cub *cub, int x, int y, int color);
void		exit_error(char *msg, t_cub *cub);
void		render(t_cub *cub);
void		hook_close(t_cub *cub);
int			key_press(int key, t_cub *cub);

#endif