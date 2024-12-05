/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:18:12 by sanglier          #+#    #+#             */
/*   Updated: 2024/12/05 15:31:53 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/*################ STRUCTURES #####################*/

typedef struct s_img_data	t_img_data;
typedef struct s_mlx_data	t_mlx_data;
typedef struct s_map		t_map;
typedef struct s_player		t_player;
typedef struct s_raycaster	t_raycaster;
typedef struct s_proj		t_proj;
typedef struct s_game		t_game;
typedef struct s_list		t_list;
typedef struct s_texture	t_texture;
typedef struct s_rgb		t_rgb;

struct						s_img_data
{
	void					*img_ptr;
	char					*addr;
	int width;
	int height;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
};

struct						s_mlx_data
{
	void					*mlx_ptr;
	void					*game_win_ptr;
};

struct						s_player
{
	double					player_pos_x;
	double					player_pos_y;
	double					player_px_pos_x;
	double					player_px_pos_y;
	bool					move_up;
	bool					move_down;
	bool					move_left;
	bool					move_right;
	bool					rotate_left;
	bool					rotate_right;
	float					angle;
	float					distance;
	char					*direction;
};

struct						s_raycaster
{
	float					ray_angle;
	double					ray_x;
	double					ray_y;
	float					ray_index;
	float					wall_orientation;
	int						hit_side;
};

struct						s_proj
{
	float					distance_to_wall;
	float					last_distance_to_wall;
	float					wall_height;
	float					wall_start;
	float					wall_end;
	int						wall_color;
	float					correct_distance;
	t_img_data				texture;
};

/*####PARSE####*/

struct						s_map
{
	int						count;
	char					**map;
	int						map_height;
	int						map_width;
	t_texture				*texture;
	t_rgb					*ceiling;
	t_rgb					*floor;
};

struct						s_texture
{
	char					*no;
	char					*so;
	char					*we;
	char					*ea;
	t_img_data				texture1;
	t_img_data				texture2;
	t_img_data				texture3;
	t_img_data				texture4;
};

struct						s_rgb
{
	int						r;
	int						g;
	int						b;
};

struct						s_list
{
	char					*value;
	struct s_list			*next;
	struct s_list			*prev;
};

struct						s_game
{
	t_map					*map;
	t_list					*list;
	t_mlx_data				mlx_data;
	t_player				player;
	t_img_data				map_img;
	t_img_data				game_img;
	t_raycaster				raycaster;
	t_proj					projection;
	bool					end;
};

typedef enum s_txt
{
	NO,
	SO,
	WE,
	EA
}							e_txt;

typedef enum s_rgbs
{
	CEI,
	FLO
}							e_rgb;

#endif