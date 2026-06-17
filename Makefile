# ==============================================================================
# CONFIGURATION
# ==============================================================================

NAME = nova3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O3 -Iminilibx-linux -Iincludes -Ilibft -Ibass -I.
LDFLAGS = -Llibft -lft -Lminilibx-linux -lmlx -lX11 -lXext -lm -Lbass -lbass -Wl,-rpath=./bass -lpthread

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MINILIBX_DIR = minilibx-linux
MINILIBX = $(MINILIBX_DIR)/libmlx.a

BUILD_DIR = build

# Source files (automatic detection via wildcards)
SRC = main.c \
      $(wildcard parser/*.c) \
      $(wildcard init_mlx/*.c) \
      $(wildcard render/*.c) \
      $(wildcard utils/*.c) \
      $(wildcard player/*.c) \
      $(wildcard ui/*.c) \
      $(wildcard audio/*.c) \
      $(wildcard enemy/*.c) \
      $(wildcard level/*.c) \
      $(wildcard item/*.c)

OBJ = $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))
DEP = $(addprefix $(BUILD_DIR)/, $(SRC:.c=.d))

# ==============================================================================
# BUILD RULES
# ==============================================================================

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MINILIBX):
	@make -C $(MINILIBX_DIR)

-include $(DEP)

clean:
	@rm -rf $(BUILD_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MINILIBX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
