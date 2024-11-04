/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:48:09 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/04 16:12:43 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
#define INCLUDES_H

/*################ INCLUDES #####################*/

#include <stdio.h>
#include <stdlib.h>
#include "../minilibx-linux/mlx.h"
#include "../get_next_line/get_next_line.h"

/*################ KEY MACROS #####################*/
 
#define UP_KEY        65362
#define DOWN_KEY      65364
#define LEFT_KEY      65361
#define RIGHT_KEY     65363
#define W_KEY         119
#define A_KEY         97
#define S_KEY         115
#define D_KEY         100
#define ESC_KEY       65307


/*################ SIZE MACROS #####################*/

#define TILE_SIZE 32
#define PLAYER_SIZE 16


/*################ STRUCTURES #####################*/


typedef struct	s_data t_data;
typedef struct	s_mlx_data t_mlx_data;
typedef	struct	s_map t_map;
typedef struct s_player t_player;
typedef struct s_game t_game;

struct	s_data
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

struct	s_mlx_data
{
	void	*mlx_ptr;
	void	*win_ptr;
};

struct	s_map
{
	char					**map;
	int					map_height;
	int					map_length;
};

struct s_player
{
	int	player_pos_x;
	int	player_pos_y;
};

struct s_game
{
    t_mlx_data *mlx_data;
    t_map      *map;
    t_player   *player;
    t_data     *img;
};


/*################ FUNCTIONS #####################*/

/*=================draw_tools.c===================*/

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

/*==================get_map.c=====================*/

void		free_tab(char **tab);
int			fill_tab(t_map *map);

/*===================hooks.c======================*/

int			handle_keypress(int keycode, t_game *game);

/*=====================init.c=====================*/

int			init_env(t_mlx_data *mlx_data, int width, int height, char *title);
int			initialize_map(t_map *map);
int			initialize_graphics(t_mlx_data *mlx_data, t_map *map, t_data *img);


/*==================mini_map.c====================*/

void		draw_mini_map(t_game *game);
void		draw_and_display_map(t_game *game);

/*====================main.c======================*/

void		clean_up(t_game *game);

#endif