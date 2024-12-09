/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:18:12 by sanglier          #+#    #+#             */
/*   Updated: 2024/12/09 22:16:41 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/*################ STRUCTURES #####################*/

typedef struct s_img_data	t_img_data;
typedef struct s_mlx_data	t_mlx_data;
typedef struct s_map		t_map;
typedef struct s_player		t_player;
typedef struct s_ray		t_ray;
typedef struct s_proj		t_proj;
typedef struct s_game		t_game;
typedef struct s_list		t_list;
typedef struct s_texture	t_texture;
typedef struct s_rgb		t_rgb;

struct						s_img_data
{
	void					*img_ptr;
	char					*addr;
	int						width;
	int						height;
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
	
	char					direction;
	
	bool					move_up;
	bool					move_down;
	bool					move_left;
	bool					move_right;
	bool					rotate_left;
	bool					rotate_right;
	
	double					angle;
	double					distance;
};

struct						s_ray
{
	double					ray_angle;
	double					ray_x;
	double					ray_y;
	double					ray_index;
	int						hit_side;
};

struct						s_proj
{
	double					distance_to_wall;
	double					last_distance_to_wall;
	double					wall_height;
	double					wall_start;
	double					wall_end;
	double					wall_orientation;
	int						wall_color;
	double					correct_distance;
	t_img_data				texture;
};

/*####PARSE####*/

struct						s_map
{
	int						count;
	char					**map;
	int						height;
	int						width;
	int						ceiling_color;
	int						floor_color;
	t_rgb					*ceiling;
	t_rgb					*floor;
	t_texture				*texture;
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
	t_ray					ray;
	t_proj					proj;
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