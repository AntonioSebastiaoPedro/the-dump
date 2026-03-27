/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:57:21 by paulcard          #+#    #+#             */
/*   Updated: 2026/03/27 13:57:21 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_H
# define MACRO_H

/* Characters */
# define SPACE 32
# define TAB '\t'
# define NEWLINE '\n'
# define ENDLINE '\0'
# define COMMA ','
# define CARRIAGE '\r'

/* Directions */
# define NORTE "NO"
# define SUL "SO"
# define LESTE "EA"
# define OESTE "WE"

/* Movement */
# define MOVE_SPEED 0.2
# define ROT_SPEED  0.1

/* Keys */
# define KEY_W       119
# define KEY_S       115
# define KEY_A       97
# define KEY_D       100

/* Arrow keys */
# define KEY_LEFT    65361
# define KEY_RIGHT   65363
# define KEY_ESC     65307

/* Screen */
# define WIDTH 1920
# define HEIGHT 1080

/* Colors */
# define RED 0xFF0000
# define WHITE 0xFFFFFF
# define GRAY 0x808080
# define BLACK 0x000000

/* Minimap */
# define TILE_SIZE 10
# define PLAYER_SIZE 4

#endif
