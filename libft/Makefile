# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paulcard <paulcard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/10 12:29:40 by paulcard          #+#    #+#              #
#    Updated: 2025/09/05 11:25:17 by paulcard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#compiladores and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

#library
NAME = libft.a

#sources and files
SRCS = ft_atoi.c \
ft_bzero.c \
ft_calloc.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isspace.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_strchr.c \
ft_strdup.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_substr.c \
ft_tolower.c \
ft_toupper.c \
ft_strtrim.c \
ft_strmapi.c \
ft_itoa.c\
ft_striteri.c \
ft_split.c \
ft_putchar_fd.c\
ft_putstr_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_strcmp.c \
ft_strcpy.c \
Get_next_line/get_next_line.c

SRCS_BONUS = _bonus/ft_lstnew.c \
_bonus/ft_lstadd_front.c \
_bonus/ft_lstsize.c \
_bonus/ft_lstlast.c \
_bonus/ft_lstadd_back.c \
_bonus/ft_lstdelone.c \
_bonus/ft_lstclear.c \
_bonus/ft_lstiter.c

#lib.h
INCLUDE = libft.h

#objects and files
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

#create static library
$(NAME): $(OBJS) $(INCLUDE)
	$(AR) $(NAME) $(OBJS)

# Generic rule to compile object files and include headers
%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -I. -c $< -o $@

# compile bonus
bonus: $(INCLUDE) $(OBJS) $(OBJS_BONUS)
	$(AR) $(NAME) $(OBJS) $(OBJS_BONUS)
#clean a static library
clean:
	$(RM) $(OBJS) $(OBJS_BONUS)

.PHONY: all bonus clean fclean re

#clean objects files
fclean: clean
	$(RM) $(NAME)

#recompilar tudo do zero
re: fclean all
