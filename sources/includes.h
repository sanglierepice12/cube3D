/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:48:09 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/12 11:29:05 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
#define INCLUDES_H

/*################ INCLUDES #####################*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

/*################### COLORS #######################*/

#define BLUE  0x0000FF
#define WHITE 0xFFFFFFF
#define GREEN 0x00FF000
#define BLACK 0x0000000
#define PINK  0X0FFC0CB
#define RED  0XFF0000
#define YELLOW  0xFFFF00

/*################ SIZE MACROS #####################*/

#define TILE_SIZE 64
#define PLAYER_SIZE 16
#define BORDER_SIZE 0.5
//#define STEP_SIZE 10
#define ROTATION_SPEED 0.1
#define FOV_ANGLE (M_PI / 3)
#define RAY_COUNT 320
#define GAME_WIDTH 1920
#define GAME_HEIGHT 780
#define DISTANCE_TO_PLANE ((GAME_WIDTH * 0.5) / tan(FOV_ANGLE * 0.5))
//#define DISTANCE_TO_PLANE GAME_WIDTH / (2 * tan(FOV_ANGLE / 2))



/*################ STRUCTURES #####################*/


typedef struct	s_img_data t_img_data;
typedef struct	s_mlx_data t_mlx_data;
typedef	struct	s_map t_map;
typedef struct s_player t_player;
typedef struct s_game t_game;

struct	s_img_data
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
	void	*map_win_ptr;
	void	*game_win_ptr;
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
	int	player_px_pos_x;
	int	player_px_pos_y;
	double	angle;
	double distance;
	char *direction;
};

struct s_game
{
    t_mlx_data *mlx_data;
    t_map      *map;
    t_player   *player;
    t_img_data     *map_img;
    t_img_data     *game_img;
};


/*################ FUNCTIONS #####################*/

/*=================draw_tools.c===================*/

void		my_mlx_pixel_put(t_img_data *data, int x, int y, int color);

/*==================get_map.c=====================*/

void		free_tab(char **tab);
int			fill_tab(t_map *map);

/*===================hooks.c======================*/

int			handle_keypress(int keycode, t_game *game);

/*=====================init.c=====================*/

int			init_env(t_mlx_data *mlx_data, t_map *map);
int			initialize_map(t_map *map);
int initialize_graphics(t_mlx_data *mlx_data, t_map *map, t_img_data *map_img, t_img_data *game_img);
void		find_play_pos(t_map *map, t_player *player);
int			init_game(t_game *game);


/*==================mini_map.c====================*/

void		draw_mini_map(t_game *game);
void		draw_and_display_map(t_game *game);

/*====================main.c======================*/

void		clean_up(t_game *game);

#endif