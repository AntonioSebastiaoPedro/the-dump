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

typedef struct  s_game
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor_color;
	int		f_set;
	int		ceiling_color;
	int		c_set;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	char    player_dir;
}              t_game;

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
int			parser(int ac, char **av, t_game *game);
int			parse_texture(const char *line, t_game *game);
int			parse_color(const char *line, t_game *game);
int			parse_map(char **lines, int map_start, t_game *game);
int			is_empty_line(char *line);
int			is_valid_line_map(char *line);
char		**normalize_map(char **map, int height);
int			validate_map(char **map, int height, t_game *game);
int			check_player(char **map);
bool		is_player(char c);
int			check_borders(char **map, int height, int width);
int			check_inside(char **map, int height);
int flood_fill(char **map, int x, int y);


/*		UTILS		*/
int			ft_count_lines(int fd);
void		free_split(char **arr);
t_line_type get_line_type(const char *line);
char    	**copy_map(char **lines, int map_start, int height);
void		free_game(t_game *game);
void    	free_map(char **map, int height);
void		print_map(char **map);

#endif