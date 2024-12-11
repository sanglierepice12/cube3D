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
#include <math.h>

void render_3d_column(t_game *game,t_proj *projection, t_ray *ray)
{
    int y;
    float texture_x;
    float texture_y;
    float texture_y_pos;
    float step_size;
    unsigned int pixel_color;
    float ray_dir_x;
    float ray_dir_y; 

    ray_dir_x = cos(ray->ray_angle);  
    ray_dir_y = sin(ray->ray_angle);  
    def_wall_texture(projection, game->map);
    printf("raypxx %f\n", ray->px_x);
    if (ray->hit_side == HORIZONTAL)
        texture_x = fmodf(ray->px_x, TILE_SIZE);  
    else
        texture_x = fmodf(ray->px_y, TILE_SIZE);
    texture_x = (texture_x * projection->tex.width) / TILE_SIZE;
    step_size = (float)projection->tex.height / game->proj.wall_height;
    texture_y_pos = 0.0f;
    if (game->proj.wall_start < 0)
    {
        texture_y_pos = -game->proj.wall_start * step_size;
        game->proj.wall_start = 0;
    }
    if (ray->hit_side == VERTICAL && ray_dir_x < 0)
            texture_x = projection->tex.width - texture_x - 1;
    else if (ray->hit_side == HORIZONTAL && ray_dir_y > 0)
            texture_x = projection->tex.width - texture_x - 1;
    y = game->proj.wall_start;
    while (y <= game->proj.wall_end && y < GAME_HEIGHT)
    {
        texture_y = (int)texture_y_pos % projection->tex.height;
        pixel_color = get_pixel_color(&projection->tex, texture_x, texture_y);
        my_mlx_pixel_put(&game->game_img, ray->ray_index, y, pixel_color);
        texture_y_pos += step_size; 
        y++;
    }
}



void update_proj_data(t_proj *proj, t_player *player, t_ray *ray)
{
	float	angle_diff;

	proj->distance_to_wall = DISTANCE_TO_WALL(ray->px_x, ray->px_y,
			player->player_px_pos_x, player->player_px_pos_y);
	angle_diff = ray->ray_angle - player->angle;
	proj->correct_distance = proj->distance_to_wall * cos(angle_diff);
	proj->wall_height = ((TILE_SIZE * DISTANCE_TO_PLANE) / proj->correct_distance);
	proj->wall_start = SCREEN_CENTER_Y - (proj->wall_height * 0.5);
	proj->wall_end = SCREEN_CENTER_Y + (proj->wall_height * 0.5);
} 

void def_hit_side(t_ray *ray, int prev_map_x, int prev_map_y)
{
    int ray_map_x;
    int ray_map_y;
    
    ray_map_x = MAP_COORD_X(ray->px_x);
    ray_map_y = MAP_COORD_Y(ray->px_y);
    if (ray_map_x != prev_map_x || ray_map_y != prev_map_y)
    {
        if (ray_map_x != prev_map_x)
        {
            printf("VERTICAL\n");
            ray->hit_side = VERTICAL;
        }
        if (ray_map_y != prev_map_y)
        {
            printf("HORIZONTAL\n");
            ray->hit_side = HORIZONTAL;
        }
    }
}

void cast_ray(t_game *game, t_ray *ray, t_player *player, t_proj *proj)
{
    float ray_dir_x;
    float ray_dir_y;
    int prev_map_x;
    int prev_map_y;

    ray_dir_x = cos(ray->ray_angle);
    ray_dir_y = sin(ray->ray_angle);
    while (!wall_hit(game->map, ray))
    {
        prev_map_x = MAP_COORD_X(ray->px_x); // previous position before hit
        prev_map_y = MAP_COORD_Y(ray->px_y); // previous position before hit
        ray->px_x += ray_dir_x * 0.08;
        if (wall_hit(game->map, ray))
            break;
        ray->px_y += ray_dir_y * 0.08;
    }
    def_hit_side(ray, prev_map_x, prev_map_y);
    update_proj_data(proj, player, ray);
    def_wall_orientation(proj, ray, ray_dir_x, ray_dir_y);
}

void	render_3d_map(t_game *game, t_player *player, t_ray *ray,
		t_proj *proj)
{
	ray->ray_index = 0;
	clear_screen(&game->game_img, game->map->ceiling_color, game->map->floor_color);
	while (ray->ray_index < GAME_WIDTH)
	{
		ray->px_x = player->player_px_pos_x;
		ray->px_y = player->player_px_pos_y;
		ray->ray_angle = (player->angle - FOV_HALF) + (ray->ray_index * RAY_ANGLE_DELTA);
		cast_ray(game, ray, player, proj);
		render_3d_column(game, proj, ray);
		ray->ray_index++;
	}
}
