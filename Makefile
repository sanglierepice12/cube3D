# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/30 12:35:35 by jedusser          #+#    #+#              #
#    Updated: 2024/11/11 08:07:29 by jedusser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
SRC = sources/main.c sources/get_map.c sources/draw_tools.c sources/hooks.c sources/init.c sources/mini_map.c
GNL_SRC = get_next_line/get_next_line_utils.c get_next_line/get_next_line.c

OBJ_DIR = obj/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o) $(GNL_SRC:%.c=%.o) 

CC = cc
CFLAGS = -Wextra -Wall -Werror -Ilibft -Iminilibx-linux -g3

MINILIBX_URL = https://cdn.intra.42.fr/document/document/23121/minilibx-linux.tgz
MINILIBX_DIR = minilibx-linux
MINILIBX_TAR = minilibx-linux.tgz

all: $(MINILIBX_DIR) libft $(NAME)

$(MINILIBX_DIR):
	@if [ ! -d "$(MINILIBX_DIR)" ]; then \
		echo "Downloading MiniLibX..."; \
		curl -o $(MINILIBX_TAR) $(MINILIBX_URL); \
		tar -xzf $(MINILIBX_TAR); \
		rm -f $(MINILIBX_TAR); \
	fi
	make -C $(MINILIBX_DIR)

$(NAME): $(OBJ)
	@echo "Building $(NAME)"
	$(CC) $(OBJ)  -L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm -o $(NAME)

$(OBJ_DIR)%.o: %.c
	@echo "Compiling $< to $@"
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(OBJ_DIR)
	make clean -C $(MINILIBX_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re $(MINILIBX_DIR) libft
