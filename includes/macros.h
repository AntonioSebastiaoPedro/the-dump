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
# define MOVE_SPEED 2
# define ROT_SPEED  0.02
# define MOUSE_SENSITIVITY 0.007
# define PLAYER_COLLISION_RADIUS 0.2

/* Performance Optimization */
# define TARGET_FPS 60
# define FRAME_TIME (1.0 / TARGET_FPS)

/* Threading */
# define NUM_THREADS 4

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
# define KEY_U		117
# define KEY_N       110
# define KEY_MINUS   45
# define KEY_PLUS    61
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

/* Radar Minimap */
# define RADAR_RADIUS      90
# define RADAR_SCALE       10
# define RADAR_CENTER_X    (RADAR_RADIUS + 20)
# define RADAR_CENTER_Y    (RADAR_RADIUS + 20)
# define RADAR_DIR_LEN     12
# define RADAR_PLAYER_SIZE 5

# define RADAR_BG          0x0A1520
# define RADAR_WALL        0x4488CC
# define RADAR_FLOOR       0x1A2A3A
# define RADAR_CROSS       0x1E4A1E
# define RADAR_BORDER      0x22BB55
# define RADAR_BORDER_DIM  0x116633
# define RADAR_PLAYER      0x22FF44
# define RADAR_DIR         0xFFFF00
# define RADAR_DOOR        0xCC6600

# define LOADING_IMG "assets/theme/loading.xpm"
# define MENU_IMG "assets/theme/menu.xpm"
# define ABOUT_IMG "assets/theme/about.xpm"
# define VICTORY_IMG "assets/theme/boss_victory.xpm"
# define GAME_OVER_IMG "assets/theme/game_over.xpm"

/* WEAPON MACROS */
# define WEAPON_FRAMES 13
# define WEAPON_STATES 3
# define WEAPON_IDLE 0
# define WEAPON_MOVE 1
# define WEAPON_SHOT 2
# define WEAPON_SCALE 4.0
# define TRANSPARENT_BACKGROUND 0xFF0000

/* DOOR MACROS */
# define MAX_DOOR_DIST 3.0
# define DOOR_RAY_STEP 0.1
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
# define ENEMY_SPEED       0.050
# define ENEMY_HP          2
# define ENEMY_DAMAGE      2
# define ENEMY_ATK_COOLDOWN 30
# define ENEMY_FRAME_DELAY  10
# define ENEMY_ATTACK_RANGE 8.0

# define LOS_RAY_STEP      0.2
# define LOS_RAY_THICKNESS 0.1

# define DOG_HP            5
# define DOG_DAMAGE        2
# define DOG_SPEED         0.1
# define DOG_ATTACK_RANGE  1.5
# define OFFICER_HP        10
# define OFFICER_DAMAGE    2
# define OFFICER_SPEED     0.1

# define PLAYER_MAX_HP     100

/* WEAPON AMMO */

# define CURRENT_AMMO		  100
# define REVOLVER_MAX_AMMO    100
# define RIFLE_MAX_AMMO  100
# define PLASMA_MAX_AMMO     200
# define WEAPON_MAX_RANGE    9.0
# define WEAPON_DROP_OFF_START 4.0
# define CROSSHAIR_TOLERANCE 0.3

# define ITEM_INTERACT_DIST   0.5
# define BARREL_COLLISION_RADIUS 0.3

# define HEAL_MEDIC_KIT        25
# define HEAL_WELL             5
# define AMMO_REVOLVER_PICKUP  50
# define AMMO_RIFLE_PICKUP     20
# define AMMO_PLASMA_PICKUP    40
# define INVINCIBILITY_DURATION 120.0

# define BARREL_ENEMY_RADIUS   4.0
# define BARREL_ENEMY_DAMAGE   100
# define BARREL_PLAYER_RADIUS  3.0
# define BARREL_PLAYER_DAMAGE  50

#endif