# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sravonin <sravonin@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 18:45:39 by sravonin          #+#    #+#              #
#    Updated: 2025/01/27 14:12:58 by sravonin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

OBJ_DIR = ./obj/
SRC_DIR = ./src/
INC_DIR = ./include/
LIBFT = ./libft/
MLX = ./minilibx-linux/

SRCS = main.c mlx_utils.c mlx_line.c vector_utils.c dda.c

SRC_FILES = $(addprefix $(SRC_DIR), $(SRCS))
OBJ = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

IFLAGS = -I$(INC_DIR) -I$(LIBFT) -I$(MLX)
LFLAGS = -L$(LIBFT) -lft -L$(MLX) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@echo "\033[1;32mBuilding $@\033[0m\n"
	@$(MAKE) -C $(LIBFT) --no-print-directory
	@if [ ! -f $(MLX)/libmlx.a ]; then $(MAKE) -C $(MLX) --no-print-directory; fi
	@$(CC) -o $@ $(OBJ) $(LFLAGS) $(CFLAGS)
	@echo "\033[1;32mDone ✅\033[0m\n"

$(OBJ_DIR):
	@echo "\033[1;34mCreating $(OBJ_DIR)\033[0m\n"
	@mkdir -p $(OBJ_DIR)
	@echo "\033[1;34mDone ✅\033[0m\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo "\033[1;33mCompiling $<\033[0m\n"
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@echo "\033[1;33mDone ✅\033[0m\n"

clean:
	@echo "\033[1;31mCleaning object files...\033[0m"
	@$(MAKE) -C $(LIBFT) clean --no-print-directory
	@$(RM) -r $(OBJ_DIR)
	@echo "\033[1;31mDone ✅\033[0m\n"

fclean: clean
	@echo "\033[1;31mFull clean, removing binaries...\033[0m"
	@$(MAKE) -C $(LIBFT) fclean --no-print-directory
	@$(RM) -f $(NAME)
	@echo "\033[1;31mDone ✅\033[0m\n"

re: fclean all

.PHONY: all clean fclean re $(OBJ_DIR)
