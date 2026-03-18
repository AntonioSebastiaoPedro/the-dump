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
# define ESPACO 32
# define TAB '\t'
# define NEWLINE '\n'
# define ENDLINE '\0'
# define COMMA ','


# define NORTE "NO"
# define SUL "SO"
# define LESTE "EA"
# define OESTE "WE"


/*PARSER*/

/*	check file	*/
void	ft_check_args(int ac);
int		ft_check_file(char *filename);
int		ft_open_file(char *filename);
void	ft_validate_file(int ac, char **av);

/*readfile*/
char    **read_file(char *filename);
int		parser(int ac, char **av, t_game *game);
int		parse_texture(const char *line, t_game *game);
int		parse_color(const char *line, t_game *game);
int		parse_map(char **lines, int map_start, t_game *game);

/*		UTILS		*/
int			ft_count_lines(int fd);
void    	free_lines(char **lines);
void		free_split(char **arr);
t_line_type get_line_type(const char *line);

#endif