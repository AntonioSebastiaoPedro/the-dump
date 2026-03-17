# ==============================================================================
# CONFIGURATION
# ==============================================================================

NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -g
CPPFLAGS = -I. -I$(LIBFT_DIR) -MMD -MP
LDFLAGS = -lft -L$(LIBFT_DIR)
LDFLAGS += -lreadline
RM = rm -rf

# ==============================================================================
# LIBFT
# ==============================================================================
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

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
PARSER_FILES = 
# ==============================================================================
# SOURCE PATHS AND OBJECTS
# ==============================================================================

# Add prefix to the files
ASSETS = $(addprefix $(ASSETS_DIR)/, $(ASSETS_FILES))
INIT_MLX = 


# All source files
SRC = main.c $(INIT_MLX)

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
$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJ) $(LDFLAGS) -o $@

# Compile with banner
banner: fclean
	$(MAKE) all SHOW_BANNER=true

# Compile without custom prompt and command not found handle
raw: fclean
	$(MAKE) all CUSTOM_PROMPT=false COMMAND_NOT_FOUND_HANDLE=false

# NORM
n norm:
	norminette

# Compile libft
$(LIBFT):
	make -C $(LIBFT_DIR)

# ==============================================================================
# CLEAN RULES
# ==============================================================================

clean:
	$(RM) $(BUILD_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re banner n norm raw