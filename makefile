# ==============================================================================
# CONFIGURATION
# ==============================================================================

NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -Iminilibx-linux
CFLAGS += -O3
CFLAGS += -g
CPPFLAGS = -I. -I$(LIBFT_DIR) -MMD -MP
LDFLAGS = -lft -L$(LIBFT_DIR)
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
ASSETS_DIR  = assets
INIT_MLX_DIR  = init_mlx
PARSER_DIR  = parser
PLAYER_DIR  = player
RENDER_DIR  = render
UTILS_DIR = utils

# ==============================================================================
# SOURCE FILES
# ==============================================================================

ASSETS_FILES = 
INIT_MLX_FILES = 
PARSER_FILES = check_file.c read_line.c parser.c get_line_type.c parse_color.c parser_testura.c parse_map.c normalize_map.c valid_line_map.c validate_map.c check_player.c check_inside.c check_borders.c
UTILS_FILES = count_lines.c free_all.c copy_map.c debug.c
# ==============================================================================
# SOURCE PATHS AND OBJECTS
# ==============================================================================

# Add prefix to the files
ASSETS = $(addprefix $(ASSETS_DIR)/, $(ASSETS_FILES))
PARSER = $(addprefix $(PARSER_DIR)/, $(PARSER_FILES))
UTILS = $(addprefix $(UTILS_DIR)/, $(UTILS_FILES))

# All source files
SRC = main.c $(INIT_MLX) $(PARSER) $(UTILS)

# Add prefix to save objects and dependency files in build folder
OBJ = $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))
DEP = $(addprefix $(BUILD_DIR)/, $(SRC:.c=.d))

# ==============================================================================
# BUILD RULES
# ==============================================================================

# Default target
all: $(NAME)

# Include dependency files
-include $(DEP)

# Function that creates individual rule for each file
define compile_rule
$(BUILD_DIR)/$(1:.c=.o): $(1) | $(BUILD_DIR)
	@mkdir -p $$(dir $$@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $$< -o $$@
endef

# Generate a rule for each source file
$(foreach src,$(SRC),$(eval $(call compile_rule,$(src))))

# Create build folder
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Link final executable
$(NAME): $(LIBFT) $(MINILIBX) $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJ) $(LDFLAGS) -o $@


# Compile without custom prompt and command not found handle
raw: fclean
	$(MAKE) all

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
	make clean -C $(LIBFT_DIR)
	make clean -C $(MINILIBX_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MINILIBX_DIR)

re: fclean all

.PHONY: all clean fclean re n norm 