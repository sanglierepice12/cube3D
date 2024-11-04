# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/30 12:35:35 by jedusser          #+#    #+#              #
#    Updated: 2024/11/04 09:32:39 by jedusser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mlxtests
SRC = sources/main.c sources/get_map.c sources/draw_tools.c sources/hooks.c sources/init.c sources/mini_map.c
GNL_SRC = get_next_line/get_next_line_utils.c get_next_line/get_next_line.c

OBJ_DIR = obj/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o) $(GNL_SRC:%.c=%.o) 

CC = cc
CFLAGS = -Wextra -Wall -Werror -Ilibft -Iminilibx-linux -g3

all: mlx  libft $(NAME)

mlx:
	make -C ./minilibx-linux


$(NAME): $(OBJ) 
	$(CC) $(OBJ)  -Lminilibx-linux -lmlx -lXext -lX11 -lm -o $(NAME)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(OBJ_DIR)
	make clean -C ./minilibx-linux

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re mlx libft