# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/02 17:06:55 by aamandio          #+#    #+#              #
#    Updated: 2026/05/05 10:28:27 by paulcard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ==============================================================================
# CONFIGURATION
# ==============================================================================

NAME = cub3D
BONUS_NAME = cub3D_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -Iminilibx-linux
CFLAGS += -O3
CPPFLAGS = -I includes -I $(LIBFT_DIR) -MMD -MP
LDFLAGS = -lft -L$(LIBFT_DIR)
LDFLAGS += -lmlx -Lminilibx-linux -lX11 -lXext -lm
RM = rm -rf

# ==============================================================================
# LIBFT
# ==============================================================================

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# ==============================================================================
# MINILIBX
# ==============================================================================
MINILIBX_DIR = minilibx-linux
MINILIBX = $(MINILIBX_DIR)/libmlx.a


# ==============================================================================
# Bass Library (Bonus Only)
# ==============================================================================
BASSPATH = bass
BONUS_INCLUDES = -I$(BASSPATH)
BONUS_LDFLAGS = -L./$(BASSPATH) -lbass -Wl,-rpath=./$(BASSPATH)

# ==============================================================================
# DIRECTORIES
# ==============================================================================

BUILD_DIR = build
BONUS_BUILD_DIR = build_bonus
PARSER_DIR = parser
MLX_DIR = init_mlx
RENDER_DIR = render
UTILS_DIR = utils
PLAYER_DIR = player
BONUS_DIR = bonus

# Bonus Directories
BONUS_PARSER_DIR = parser_bonus
BONUS_MLX_DIR = init_mlx_bonus
BONUS_RENDER_DIR = render_bonus
BONUS_UTILS_DIR = utils_bonus
BONUS_PLAYER_DIR = player_bonus
BONUS_UI_DIR = ui_bonus
BONUS_INCLUDES_DIR = includes_bonus
BONUS_AUDIO_DIR = audio_bonus

# ==============================================================================
# SOURCE FILES
# ==============================================================================

PARSER_FILES = check_file.c read_line.c parser.c get_line_type.c parse_color.c parser_testura.c parse_map.c normalize_map.c valid_line_map.c validate_map.c check_player.c check_inside.c check_borders.c flood_fill.c validate_rgb_format.c
MLX_FILES = mlx_init.c hooks.c
RENDER_FILES = render.c ft_put_pixel.c raycasting.c dda.c draw_vertical_line.c textures.c
UTILS_FILES = count_lines.c free_cub.c copy_map.c free_cub_helpers.c load_textures.c new_split.c
PLAYER_FILES = init_player.c update_player.c set_dir_vectors.c

# ==============================================================================
# SOURCE PATHS AND OBJECTS
# ==============================================================================

PARSER = $(addprefix $(PARSER_DIR)/, $(PARSER_FILES))
MLX = $(addprefix $(MLX_DIR)/, $(MLX_FILES))
RENDER = $(addprefix $(RENDER_DIR)/, $(RENDER_FILES))
UTILS = $(addprefix $(UTILS_DIR)/, $(UTILS_FILES))
PLAYER = $(addprefix $(PLAYER_DIR)/, $(PLAYER_FILES))

# Mandatory SRC
SRC = main.c $(PARSER) $(MLX) $(RENDER) $(UTILS) $(PLAYER)
OBJ = $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))
DEP = $(addprefix $(BUILD_DIR)/, $(SRC:.c=.d))

# Bonus SRC
BONUS_PARSER_FILES = $(PARSER_FILES:.c=_bonus.c)
BONUS_MLX_FILES = $(MLX_FILES:.c=_bonus.c) loop_hook_bonus.c  weapon_hooks_bonus.c
BONUS_RENDER_FILES = $(RENDER_FILES:.c=_bonus.c) minimap_bonus.c update_weapon_bonus.c draw_weapon_bonus.c door_bonus.c door_helped_bonus.c draw_floor_ceiling_pixel_bonus.c put_fl_cl_bonus.c mira_bonus.c
BONUS_UTILS_FILES = $(UTILS_FILES:.c=_bonus.c) image_utils_bonus.c ft_delim_bonus.c free_textures_bonus.c load_floor_ceiling_texture_bonus.c
BONUS_PLAYER_FILES = $(PLAYER_FILES:.c=_bonus.c) mouse_move_bonus.c
BONUS_UI_FILES = loading_bonus.c menu_bonus.c menu_about_bonus.c render_menu_bonus.c loading_render_bonus.c
BONUS_AUDIO_FILES = audio_bonus.c free_audio_bonus.c play_door_sound_bonus.c play_weapon_sound_bonus.c run_sound_bonus.c play_button_sound_bonus.c

BONUS_PARSER = $(addprefix $(BONUS_PARSER_DIR)/, $(BONUS_PARSER_FILES))
BONUS_MLX = $(addprefix $(BONUS_MLX_DIR)/, $(BONUS_MLX_FILES))
BONUS_RENDER = $(addprefix $(BONUS_RENDER_DIR)/, $(BONUS_RENDER_FILES))
BONUS_UTILS = $(addprefix $(BONUS_UTILS_DIR)/, $(BONUS_UTILS_FILES))
BONUS_PLAYER = $(addprefix $(BONUS_PLAYER_DIR)/, $(BONUS_PLAYER_FILES))
BONUS_UI = $(addprefix $(BONUS_UI_DIR)/, $(BONUS_UI_FILES))
BONUS_AUDIO = $(addprefix $(BONUS_AUDIO_DIR)/, $(BONUS_AUDIO_FILES))

BONUS_SRC_FILES = main_bonus.c $(BONUS_PARSER) $(BONUS_MLX) $(BONUS_RENDER) $(BONUS_UTILS) $(BONUS_PLAYER) $(BONUS_UI) $(BONUS_AUDIO)
BONUS_SRC = $(addprefix $(BONUS_DIR)/, $(BONUS_SRC_FILES))
BONUS_OBJ = $(addprefix $(BONUS_BUILD_DIR)/, $(BONUS_SRC_FILES:.c=.o))
BONUS_DEP = $(addprefix $(BONUS_BUILD_DIR)/, $(BONUS_SRC_FILES:.c=.d))

# ==============================================================================
# BUILD RULES
# ==============================================================================

# Default target
all: $(NAME)

# Include dependency files
-include $(DEP)
-include $(BONUS_DEP)

# Rule for mandatory objects
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Rule for bonus objects
$(BONUS_BUILD_DIR)/%.o: $(BONUS_DIR)/%.c | $(BONUS_BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(BONUS_INCLUDES) -I$(BONUS_DIR) -I$(BONUS_DIR)/$(BONUS_INCLUDES_DIR) -I$(LIBFT_DIR) -I. -MMD -MP -c $< -o $@

# Create build folders
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BONUS_BUILD_DIR):
	@mkdir -p $(BONUS_BUILD_DIR)

# Link final executable
$(NAME): $(LIBFT) $(MINILIBX) $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJ) $(LDFLAGS) -o $@

# Bonus target
bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(MINILIBX) $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(BONUS_OBJ) $(LDFLAGS) $(BONUS_LDFLAGS) -o $@

# Compile libft
$(LIBFT):
	make -C $(LIBFT_DIR)

# Compile minilibx
$(MINILIBX):
	make -C $(MINILIBX_DIR)

norm:
	cc -Wall -Wextra -Werror norm.c -o norm && ./norm
# ==============================================================================
# CLEAN RULES
# ==============================================================================

clean:
	$(RM) $(BUILD_DIR)
	$(RM) $(BONUS_BUILD_DIR)
	$(RM) ./norm
	make clean -C $(LIBFT_DIR)
	make clean -C $(MINILIBX_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MINILIBX_DIR)

re: fclean all

.PHONY: all bonus clean fclean re
