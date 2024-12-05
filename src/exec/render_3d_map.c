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

unsigned int    get_pixel_color(t_img_data *texture, int x, int y)
{
    int                offset;
    unsigned int    color;

    if (x < 0  || x >= texture->width|| y < 0 || y >= texture->height)
        return (0);
    offset = (y * texture->line_length + x * (texture->bits_per_pixel / 8));
    color = *(unsigned int*)(texture->addr + offset);
    return (color);
}

void draw_3d_column(t_game *game, t_proj *projection)
{
    int y;
    int texture_x;
    int texture_y;
    float texture_y_pos;
    float step;
    unsigned int color;

	def_wall_texture(&game->raycaster, projection, game->map);
	if (game->raycaster.hit_side == 0)
		texture_x = (int)game->raycaster.ray_x % (int)TILE_SIZE;
	else
		texture_x = (int)game->raycaster.ray_y % (int)TILE_SIZE;
    
    texture_x = (texture_x * projection->texture.width) / TILE_SIZE;
    step = (float)projection->texture.height / game->projection.wall_height;
    texture_y_pos = 0.0f;

    if (game->projection.wall_start < 0)
    {
        texture_y_pos = -game->projection.wall_start * step;
        game->projection.wall_start = 0;
    }

    y = game->projection.wall_start;
    while (y <= game->projection.wall_end && y < GAME_HEIGHT)
    {
        texture_y = (int)texture_y_pos & (projection->texture.height - 1);
        texture_y_pos += step;
        color = get_pixel_color(&projection->texture, texture_x, texture_y);
        my_mlx_pixel_put(&game->game_img, game->raycaster.ray_index, y, color);
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
// 	def_wall_color(&game->raycaster, &game->projection);
// 	if (game->raycaster.ray_index >= 0
// 		&& game->raycaster.ray_index < GAME_WIDTH)
// 	{
// 		y = y_start;
// 		while (y <= y_end)
// 		{
// 			if (y >= 0 && y < GAME_HEIGHT)
// 				my_mlx_pixel_put(&game->game_img, game->raycaster.ray_index, y, game->projection.wall_color);
// 			y++;
// 		}
// 	}
// }
void update_proj_data(t_proj *projection, t_player *player, t_raycaster *raycaster)
{
	float	angle_diff;

	projection->distance_to_wall = DISTANCE(raycaster->ray_x, raycaster->ray_y,
			player->player_px_pos_x, player->player_px_pos_y);
	angle_diff = raycaster->ray_angle - player->angle;
	projection->correct_distance = projection->distance_to_wall * cosf(angle_diff);
	projection->wall_height = ((TILE_SIZE * DISTANCE_TO_PLANE) / projection->correct_distance);
	projection->wall_start = SCREEN_CENTER_Y - (projection->wall_height * 0.5);
	projection->wall_end = SCREEN_CENTER_Y + (projection->wall_height * 0.5);
} 

void	cast_ray(t_game *game, t_raycaster *raycaster, t_player *player,
		t_proj *projection)
{
	float	ray_dir_x;
	float	ray_dir_y;
	int		grid_x;
	int		grid_y;

	ray_dir_x = cos(raycaster->ray_angle);
	ray_dir_y = sin(raycaster->ray_angle);
	raycaster->ray_x = player->player_px_pos_x;
	raycaster->ray_y = player->player_px_pos_y;
	while (!wall_hit(game->map, raycaster))
	{
		grid_x = (int)(raycaster->ray_x / TILE_SIZE);
		grid_y = (int)(raycaster->ray_y / TILE_SIZE);
		raycaster->ray_x += ray_dir_x * 0.08;
		raycaster->ray_y += ray_dir_y * 0.08;
		if ((int)(raycaster->ray_x / TILE_SIZE) != grid_x)
		{
			raycaster->hit_side = 1; //vertical
			printf("hit side = %d\n", raycaster->hit_side);
		}
		if ((int)(raycaster->ray_y / TILE_SIZE) != grid_y)
		{
			raycaster->hit_side = 0; // horizontal
			printf("hit side = %d\n", raycaster->hit_side);
		}
	}
	update_proj_data(projection, player, raycaster);
	def_hit_side(raycaster, ray_dir_x, ray_dir_y);
}

void	render_3d_map(t_game *game, t_player *player, t_raycaster *raycaster,
		t_proj *projection)
{
	raycaster->ray_index = 0;
	clear_screen(&game->game_img, BLACK, LIGHT_BLUE);
	while (raycaster->ray_index < GAME_WIDTH)
	{
		raycaster->ray_angle = (player->angle - FOV_HALF) + (raycaster->ray_index
				* RAY_ANGLE_DELTA);
		cast_ray(game, raycaster, player, projection);
		draw_3d_column(game, projection);
		raycaster->ray_index++;
	}
}
