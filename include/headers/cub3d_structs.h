/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglier <sanglier@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:18:12 by sanglier          #+#    #+#             */
/*   Updated: 2024/11/12 16:43:03 by sanglier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_STRUCTS_H
# define CUBE3D_STRUCTS_H

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

# endif