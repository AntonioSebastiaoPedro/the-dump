# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paulcard <paulcard@student.42luanda.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/02 17:06:55 by aamandio          #+#    #+#              #
#    Updated: 2026/04/21 08:34:49 by paulcard         ###   ########.fr        #
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
CFLAGS += -g
CPPFLAGS = -I. -I$(LIBFT_DIR) -MMD -MP
LDFLAGS = -lft -L$(LIBFT_DIR) -lm
LDFLAGS += -lmlx -Lminilibx-linux -lX11 -lXext
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

# ==============================================================================
# SOURCE FILES
# ==============================================================================

PARSER_FILES = check_file.c read_line.c parser.c get_line_type.c parse_color.c parser_testura.c parse_map.c normalize_map.c valid_line_map.c validate_map.c check_player.c check_inside.c check_borders.c flood_fill.c validate_rgb_format.c
MLX_FILES = mlx_init.c mlx_utils.c hooks.c
RENDER_FILES = put_pixel.c raycasting.c render.c draw_line.c
UTILS_FILES = count_lines.c free_cub.c copy_map.c debug.c ft_delim.c new_split.c
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
# For bonus, we use the files in the _bonus directory

BONUS_RENDER_FILES = $(BONUS_RENDER_DIR)/minimap.c

BONUS_PARSER = $(addprefix $(BONUS_PARSER_DIR)/, $(PARSER_FILES))
BONUS_MLX = $(addprefix $(BONUS_MLX_DIR)/, $(MLX_FILES))
BONUS_RENDER = $(addprefix $(BONUS_RENDER_DIR)/, $(RENDER_FILES)) $(BONUS_RENDER_FILES)
BONUS_UTILS = $(addprefix $(BONUS_UTILS_DIR)/, $(UTILS_FILES))
BONUS_PLAYER = $(addprefix $(BONUS_PLAYER_DIR)/, $(PLAYER_FILES))
BONUS_UI = $(BONUS_UI_DIR)/loading.c $(BONUS_UI_DIR)/menu.c

BONUS_SRC_FILES = main.c $(BONUS_PARSER) $(BONUS_MLX) $(BONUS_RENDER) $(BONUS_UTILS) $(BONUS_PLAYER) $(BONUS_UI)
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
	$(CC) $(CFLAGS) -I$(BONUS_DIR) -I$(BONUS_DIR)/$(BONUS_INCLUDES_DIR) -I$(LIBFT_DIR) -I. -MMD -MP -c $< -o $@

# Create build folders
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BONUS_BUILD_DIR):
	@mkdir -p $(BONUS_BUILD_DIR)

# Link final executable
$(NAME): $(LIBFT) $(MINILIBX) $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJ) $(LDFLAGS) -o $@

# Bonus target
bonus: $(LIBFT) $(MINILIBX) $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(BONUS_OBJ) $(LDFLAGS) -o $(BONUS_NAME)

# NORM
n norm:
	norminette

# Compile libft
$(LIBFT):
	make -C $(LIBFT_DIR)

# Compile minilibx
$(MINILIBX):
	make -C $(MINILIBX_DIR)

# ==============================================================================
# CLEAN RULES
# ==============================================================================

clean:
	$(RM) $(BUILD_DIR)
	$(RM) $(BONUS_BUILD_DIR)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MINILIBX_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MINILIBX_DIR)

re: fclean all

.PHONY: all bonus clean fclean re n norm
