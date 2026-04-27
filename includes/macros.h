/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:57:21 by paulcard          #+#    #+#             */
/*   Updated: 2026/04/27 13:28:33 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

/* Characters */
# define SPACE 32
# define TAB '\t'
# define NEWLINE '\n'
# define ENDLINE '\0'
# define COMMA ','
# define CARRIAGE '\r'

/* RGB Error */
# define FORA "Error\nRGB fora do intervalo (0-255)"
# define VALOR "Error\nvalor RGB inválido"

/* Directions */
# define NORTH "NO"
# define SOUTH "SO"
# define EAST "EA"
# define WEST "WE"

/* Movement */
# define MOVE_SPEED 0.03
# define ROT_SPEED  0.02

/* Keys */
# define KEY_W       119
# define KEY_S       115
# define KEY_A       97
# define KEY_D       100
# define KEY_LEFT    65361
# define KEY_RIGHT   65363
# define KEY_UP      65362
# define KEY_DOWN    65364
# define KEY_ENTER   65293
# define ESC         65307

/* Screen */
# define WIDTH 1920
# define HEIGHT 1010

/* Colors */
# define RED 0xFF0000
# define DARK_RED 0x780000
# define WHITE 0xFFFFFF
# define GRAY 0x808080
# define BLACK 0x000000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define MAGENTA 0xFF00FF
# define CYAN 0x00FFFF
# define TRANSP 0x00FFFFFF

/* Minimap */
# define TILE_SIZE 10
# define PLAYER_SIZE 4

#endif
