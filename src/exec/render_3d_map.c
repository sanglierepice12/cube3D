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

void render_3d_column(t_game *game, t_proj *projection)
{
    int y;
    int texture_x;
	int texture_y;
    float texture_y_pos;
    float step_size;
    unsigned int pixel_color;

    def_wall_texture(projection, game->map);
    if (game->ray.hit_side == 0)// horizontal
        texture_x = (int)game->ray.ray_x % (int)TILE_SIZE;
    else // vertical
        texture_x = (int)game->ray.ray_y % (int)TILE_SIZE;
    texture_x = (texture_x * projection->texture.width) / TILE_SIZE;
    step_size = (float)projection->texture.height / game->proj.wall_height;
    texture_y_pos = 0.0f;
    if (game->proj.wall_start < 0)
    {
        texture_y_pos = -game->proj.wall_start * step_size;
        game->proj.wall_start = 0;
    }
    y = game->proj.wall_start;
    while (y <= game->proj.wall_end && y < GAME_HEIGHT)
    {
        texture_y = (int)texture_y_pos % projection->texture.height;
        texture_y_pos += step_size;
        pixel_color = get_pixel_color(&projection->texture, texture_x, texture_y);
        my_mlx_pixel_put(&game->game_img, game->ray.ray_index, y, pixel_color);
        y++;
    }
}

// void	draw_3d_column(t_game *game)
// {
// 	float	y_start;
// 	float	y_end;
// 	int		y;

// 	y_start = game->projection.wall_start;
// 	y_end = game->projection.wall_end;
// 	def_wall_color(&game->ray, &game->projection);
// 	if (game->ray.ray_index >= 0
// 		&& game->ray.ray_index < GAME_WIDTH)
// 	{
// 		y = y_start;
// 		while (y <= y_end)
// 		{
// 			if (y >= 0 && y < GAME_HEIGHT)
// 				my_mlx_pixel_put(&game->game_img, game->ray.ray_index, y, game->projection.wall_color);
// 			y++;
// 		}
// 	}
// }
void update_proj_data(t_proj *proj, t_player *player, t_ray *ray)
{
	float	angle_diff;

	proj->distance_to_wall = DISTANCE(ray->ray_x, ray->ray_y,
			player->player_px_pos_x, player->player_px_pos_y);
	angle_diff = ray->ray_angle - player->angle;
	proj->correct_distance = proj->distance_to_wall * cosf(angle_diff);
	proj->wall_height = ((TILE_SIZE * DISTANCE_TO_PLANE) / proj->correct_distance);
	proj->wall_start = SCREEN_CENTER_Y - (proj->wall_height * 0.5);
	proj->wall_end = SCREEN_CENTER_Y + (proj->wall_height * 0.5);
} 

void def_hit_side(t_ray *ray, int grid_x, int grid_y)
{

		if ((int)(ray->ray_x / TILE_SIZE) != grid_x)
		{
			ray->hit_side = 1; //vertical
			printf("hit side = %d\n", ray->hit_side);
		}
		if ((int)(ray->ray_y / TILE_SIZE) != grid_y)
		{
			ray->hit_side = 0; // horizontal
			printf("hit side = %d\n", ray->hit_side);
		}
}

void	cast_ray(t_game *game, t_ray *ray, t_player *player,
		t_proj *proj)
{
	float	ray_dir_x;
	float	ray_dir_y;
	int		grid_x;
	int		grid_y;

	ray_dir_x = cos(ray->ray_angle);
	ray_dir_y = sin(ray->ray_angle);
	while (!wall_hit(game->map, ray))
	{
		grid_x = (int)(ray->ray_x / TILE_SIZE); //hit side at the end
		grid_y = (int)(ray->ray_y / TILE_SIZE); //hit side at the end
		ray->ray_x += ray_dir_x * 0.08;
		ray->ray_y += ray_dir_y * 0.08;
	}
	update_proj_data(proj, player, ray);
	def_hit_side(ray, grid_x, grid_y);
	def_wall_orientation(proj, ray, ray_dir_x, ray_dir_y);
}
void	render_3d_map(t_game *game, t_player *player, t_ray *ray,
		t_proj *proj)
{
	ray->ray_index = 0;
	clear_screen(&game->game_img, BLACK, LIGHT_BLUE);
	while (ray->ray_index < GAME_WIDTH)
	{
		ray->ray_x = player->player_px_pos_x;
		ray->ray_y = player->player_px_pos_y;
		ray->ray_angle = (player->angle - FOV_HALF) + (ray->ray_index * RAY_ANGLE_DELTA);
		cast_ray(game, ray, player, proj);
		render_3d_column(game, proj);
		ray->ray_index++;
	}
}
