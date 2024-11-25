/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:39:11 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/25 11:07:14 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#define DARK_GREEN 0x006400
#define DARK_RED 0x8B0000
#define DARK_BLUE 0x00008B
#define DARK_YELLOW 0xFFD700

void clear_screen(t_img_data *img, int ceiling_color, int floor_color)
{
    int *pixel_data = (int *)img->addr;
    int half_height = SCREEN_CENTER_Y;

    ft_memset(pixel_data, ceiling_color, half_height * GAME_WIDTH * sizeof(int));
    ft_memset(&pixel_data[half_height * GAME_WIDTH], floor_color, half_height * GAME_WIDTH * sizeof(int));
}

void draw_3d_column(t_game *game)
{
    int y_start = game->projection.wall_start;
    int y_end = game->projection.wall_end;
    int y;

    if (game->raycaster.ray_index >= 0 && game->raycaster.ray_index < GAME_WIDTH)
    {
        y = y_start;
        while (y <= y_end)
        {
            if (y >= 0 && y < GAME_HEIGHT)
            {
                my_mlx_pixel_put(&game->game_img, game->raycaster.ray_index, y, LIGHT_BLUE);
            }
            y++;
        }
    }
}
//to design directional wall : use var to say if it's horizontal or vertical line of the minimap that is encoutnered.

void cast_ray(t_game *game,  t_raycaster *raycaster, t_player *player, t_proj *projection)
{
    float ray_cos;
    float ray_sin;
	
	ray_cos = cos(raycaster->ray_angle);
	ray_sin = sin(raycaster->ray_angle);
    raycaster->ray_x = player->player_px_pos_x;
    raycaster->ray_y = player->player_px_pos_y;
    while (check_bounds(&game->map, raycaster))
    {
        raycaster->ray_x += ray_cos; 
        raycaster->ray_y += ray_sin;
			
    }
    projection->distance_to_wall = DISTANCE(raycaster->ray_x, raycaster->ray_y, player->player_px_pos_x, player->player_px_pos_y) ;//* cos(projection->last_distance_to_wall);
	//printf("ray : %d\n is : %f distant to wall", raycaster->ray_index, projection->distance_to_wall);
	// store the last ray distace to wall
	// if ray_anfle = 90 degrees
    // projection->last_distance_to_wall = projection->last_distance_to_wall;
    projection->wall_height = (int)(TILE_SIZE * DISTANCE_TO_PLANE / projection->distance_to_wall);
    projection->wall_start = SCREEN_CENTER_Y - (projection->wall_height * 0.5);
    projection->wall_end = SCREEN_CENTER_Y + (projection->wall_height * 0.5);
}

int check_bounds(t_map *map, t_raycaster *raycaster)
{
    return (map->map[(int)(raycaster->ray_y / TILE_SIZE)][(int)(raycaster->ray_x / TILE_SIZE)] != '1' &&
	map->map[(int)(raycaster->ray_y / TILE_SIZE)][(int)(raycaster->ray_x / TILE_SIZE)] != ' ' );
	// raycaster->ray_y / TILE_SIZE transfrom logic for cartesian
}

void render_3d_map(t_game *game, t_player *player, t_raycaster *raycaster, t_proj *projection)
{
    raycaster->ray_index = 0;
    clear_screen(&game->game_img, BLACK, LIGHT_BLUE);
    while (raycaster->ray_index < GAME_WIDTH)
    {
        raycaster->ray_angle = player->angle - FOV_HALF + (raycaster->ray_index * RAY_ANGLE_DELTA);
        cast_ray(game, raycaster, player, projection);
        draw_3d_column(game);
        raycaster->ray_index++;
    }
}
