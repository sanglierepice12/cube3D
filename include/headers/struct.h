/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:18:12 by sanglier          #+#    #+#             */
/*   Updated: 2025/01/08 08:58:31 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/*################ STRUCTURES #####################*/

typedef struct s_img_data		t_img_data;
typedef struct s_mlx_data		t_mlx_data;
typedef struct s_map			t_map;
typedef struct s_player			t_player;
typedef struct s_ray			t_ray;
typedef struct s_proj			t_proj;
typedef struct s_game			t_game;
typedef struct s_list			t_list;
typedef struct s_tex			t_tex;
typedef struct s_rgb			t_rgb;

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
	double					pos_x;
	double					pos_y;
	double					px_pos_x;
	double					px_pos_y;

	bool					move_up;
	bool					move_down;
	bool					move_left;
	bool					move_right;
	bool					rotate_left;
	bool					rotate_right;

	double					angle;

	char					direction;
};

struct						s_ray
{
	double					px_x;
	double					px_y;
	double					ray_dir_x;
	double					ray_dir_y;
	double					ray_angle;
	double					ray_index;
	bool					hit_side;
};

struct						s_proj
{
	double					distance_to_wall;
	double					wall_height;
	double					wall_start;
	double					wall_end;
	double					wall_orientation;

	double					correct_distance;
	t_img_data				tex;
	float					tex_px_x;
	float					tex_px_y;
};

/*####PARSE####*/

struct	s_map
{
	int						count;
	int						matt[6];
	char					**map;
	int						height;
	int						width;
	int						ceiling_color;
	int						floor_color;
	t_rgb					*ceiling;
	t_rgb					*floor;
	t_tex					*tex;
};

struct						s_tex
{
	char					*no;
	char					*so;
	char					*we;
	char					*ea;
	t_img_data				tex1;
	t_img_data				tex2;
	t_img_data				tex3;
	t_img_data				tex4;
};

struct	s_rgb
{
	int	r;
	int	g;
	int	b;
};

struct	s_list
{
	char			*value;
	struct s_list	*next;
	struct s_list	*prev;
};

struct s_game
{
	t_map			*map;
	t_list			*list;
	t_mlx_data		mlx_data;
	t_player		player;
	t_img_data		game_img;
	t_ray			ray;
	t_proj			proj;
	bool			end;
};

typedef enum s_txt
{
	NO,
	SO,
	WE,
	EA,
	C,
	F
}	t_txt;

typedef enum s_rgbs
{
	CEI,
	FLO
}	t_ergb;

#endif