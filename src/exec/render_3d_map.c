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

void clear_screen(t_img_data *img, int ceiling_color, int floor_color)
{
    int *pixel_data = (int *)img->addr;
    int half_height = SCREEN_CENTER_Y;

    ft_memset(pixel_data, ceiling_color, half_height * GAME_WIDTH * sizeof(int));
    ft_memset(&pixel_data[half_height * GAME_WIDTH], floor_color, half_height * GAME_WIDTH * sizeof(int));
}

void draw_3d_column(t_game *game)
{
    int wall_color;
    float y_start = game->projection.wall_start;
    float y_end = game->projection.wall_end;
    int y;

    if (game->raycaster.wall_orientation == NORTH)
        wall_color = LIGHT_BLUE;
    else if (game->raycaster.wall_orientation == SOUTH)
        wall_color = RED;
    else if (game->raycaster.wall_orientation == EAST)
        wall_color = PINK;
    else if (game->raycaster.wall_orientation == WEST)
        wall_color = GREEN;
    else
        wall_color = WHITE;
    if (game->raycaster.ray_index >= 0 && game->raycaster.ray_index < GAME_WIDTH)
    {
        y = y_start;
        while (y <= y_end)
        {
            if (y >= 0 && y < GAME_HEIGHT)
                my_mlx_pixel_put(&game->game_img, game->raycaster.ray_index, y, wall_color);
            y++;
        }
    }
}

void cast_ray(t_game *game, t_raycaster *raycaster, t_player *player, t_proj *projection)
{
    float angle_diff;
    float ray_dir_x;
    float ray_dir_y;
    
    ray_dir_x = cos(raycaster->ray_angle);
    ray_dir_y = sin(raycaster->ray_angle);

    raycaster->ray_x = player->player_px_pos_x;
    raycaster->ray_y = player->player_px_pos_y;

    int grid_x, grid_y;
    int hit_side = 0; // 0 = horizontal, 1 = vertical

    while (!wall_hit(game->map, raycaster))
    {
        grid_x = (int)(raycaster->ray_x / TILE_SIZE);
        grid_y = (int)(raycaster->ray_y / TILE_SIZE);
        raycaster->ray_x += ray_dir_x * 0.08;
        raycaster->ray_y += ray_dir_y * 0.08;
        if ((int)(raycaster->ray_x / TILE_SIZE) != grid_x)
            hit_side = 1; //vertical
        else if ((int)(raycaster->ray_y / TILE_SIZE) != grid_y)
            hit_side = 0; // horizontal
    }

    if (hit_side == 1)
    {
        if (ray_dir_x > 0)
            raycaster->wall_orientation = EAST; 
        else
            raycaster->wall_orientation = WEST;
    }
    else 
    {
        if (ray_dir_y > 0)
            raycaster->wall_orientation = SOUTH;
        else
            raycaster->wall_orientation = NORTH;
    }
    projection->distance_to_wall = DISTANCE(raycaster->ray_x, raycaster->ray_y,
                                            player->player_px_pos_x, player->player_px_pos_y);
    angle_diff = raycaster->ray_angle - player->angle;
    projection->correct_distance = projection->distance_to_wall * cos(angle_diff);
    projection->wall_height = (TILE_SIZE * DISTANCE_TO_PLANE / projection->correct_distance);
    projection->wall_start = SCREEN_CENTER_Y - (projection->wall_height * 0.5);
    projection->wall_end = SCREEN_CENTER_Y + (projection->wall_height * 0.5);
}

bool wall_hit_3d(t_map *map, t_raycaster *raycaster)
{
       return (map->map[(int)(raycaster->ray_y / TILE_SIZE)][(int)(raycaster->ray_x / TILE_SIZE)] == '1' ||
	map->map[(int)(raycaster->ray_y / TILE_SIZE)][(int)(raycaster->ray_x / TILE_SIZE)] == ' ' );
	// raycaster->ray_y / TILE_SIZE transfrom logic for cartesian

}



bool wall_hit(t_map *map, t_raycaster *raycaster)
{
       return (map->map[(int)(raycaster->ray_y / TILE_SIZE)][(int)(raycaster->ray_x / TILE_SIZE)] == '1' ||
	map->map[(int)(raycaster->ray_y / TILE_SIZE)][(int)(raycaster->ray_x / TILE_SIZE)] == ' ' );
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
