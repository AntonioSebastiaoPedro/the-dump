/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulcard <paulcard@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:57:21 by paulcard          #+#    #+#             */
/*   Updated: 2026/06/04 15:47:42 by paulcard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_BONUS_H
# define MACROS_BONUS_H

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
# define MOUSE_SENSITIVITY 0.007

/* Keys */
# define KEY_W       119
# define KEY_S       115
# define KEY_A       97
# define KEY_D       100
# define KEY_P       112
# define KEY_M		 109
# define KEY_LEFT    65361
# define KEY_RIGHT   65363
# define KEY_UP      65362
# define KEY_DOWN    65364
# define KEY_ENTER   65293
# define KEY_LCTRL 65507
# define KEY_RCTRL 65508
# define KEY_V		118
# define KEY_1		49
# define KEY_2		50
# define KEY_3		51
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
# define DARK_GREEN 0x006400
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define MAGENTA 0xFF00FF
# define CYAN 0x00FFFF
# define TRANSP 0x00FFFFFF
# define BG_COLOR 0x1A1A1A
# define LIGHT_GRAY 0xCCCCCC
# define SKY_BLUE 0x00AAFF
# define MEDIUM_GRAY 0xAAAAAA

/* Minimap */
# define MNP_MAX_SIZE 200
# define MNP_OFFSET 20
# define PLAYER_SIZE 4

# define COVER "assets/textures/cover5.xpm"
# define MENU_IMG "assets/textures/menu.xpm"
# define ABOUT_IMG "assets/textures/about.xpm"

/* WEAPON MACROS */
# define WEAPON_FRAMES 9
# define WEAPON_STATES 3
# define WEAPON_IDLE 0
# define WEAPON_MOVE 1
# define WEAPON_SHOT 2
# define WEAPON_SCALE 4.0
# define TRANSPARENT_BACKGROUND 0xFF0000

/* DOOR MACROS */
# define MAX_DOOR_DIST 3.0
# define DOOR_FRAMES 9
# define DOOR_FRAME_DELAY 5

/* JOYSTICK */
# define JOY_DEADZONE     8000
# define JOY_ROT_SENS     0.0000003

/* ENEMY */
# define ENEMY_TYPE_COUNT    3
# define EN_SOLDIER          0
# define EN_DOG              1
# define EN_OFFICER          2

# define ENEMY_IDLE_FRAMES   4
# define ENEMY_WALK_FRAMES   4
# define ENEMY_ATTACK_FRAMES 4
# define ENEMY_DEAD_FRAMES   5

/* DIRECTIONS (8-WAY) */
# define DIR_FRONT        0
# define DIR_FRONT_RIGHT  1
# define DIR_RIGHT        2
# define DIR_BACK_RIGHT   3
# define DIR_BACK         4
# define DIR_BACK_LEFT    5
# define DIR_LEFT         6
# define DIR_FRONT_LEFT   7

# define DETECTION_RADIUS  10.0
# define ENEMY_SPEED       0.015
# define ENEMY_HP          2
# define ENEMY_DAMAGE      2
# define ENEMY_ATK_COOLDOWN 60
# define ENEMY_FRAME_DELAY  10

# define DOG_HP            3
# define DOG_DAMAGE        1
# define DOG_SPEED         0.025
# define OFFICER_HP        25
# define OFFICER_DAMAGE    15
# define OFFICER_SPEED     0.018

# define PLAYER_MAX_HP     100

#endif
