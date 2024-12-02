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

void	draw_3d_column(t_game *game)
{
	float	y_start;
	float	y_end;
	int		y;

	y_start = game->projection.wall_start;
	y_end = game->projection.wall_end;
	def_wall_color(&game->raycaster, &game->projection);
	if (game->raycaster.ray_index >= 0
		&& game->raycaster.ray_index < GAME_WIDTH)
	{
		y = y_start;
		while (y <= y_end)
		{
			if (y >= 0 && y < GAME_HEIGHT)
				my_mlx_pixel_put(&game->game_img, game->raycaster.ray_index, y, game->projection.wall_color);
			y++;
		}
	}
}

void	cast_ray(t_game *game, t_raycaster *raycaster, t_player *player,
		t_proj *projection)
{
	float	angle_diff;
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
			raycaster->hit_side = 1; //vertical
		else if ((int)(raycaster->ray_y / TILE_SIZE) != grid_y)
			raycaster->hit_side = 0; // horizontal
	}
	def_hit_side(raycaster, ray_dir_x, ray_dir_y);
	projection->distance_to_wall = DISTANCE(raycaster->ray_x, raycaster->ray_y,
			player->player_px_pos_x, player->player_px_pos_y);
	angle_diff = raycaster->ray_angle - player->angle;
	projection->correct_distance = projection->distance_to_wall
		* cos(angle_diff);
	projection->wall_height = (TILE_SIZE * DISTANCE_TO_PLANE
			/ projection->correct_distance);
	projection->wall_start = SCREEN_CENTER_Y - (projection->wall_height * 0.5);
	projection->wall_end = SCREEN_CENTER_Y + (projection->wall_height * 0.5);
}

void	render_3d_map(t_game *game, t_player *player, t_raycaster *raycaster,
		t_proj *projection)
{
	raycaster->ray_index = 0;
	clear_screen(&game->game_img, BLACK, LIGHT_BLUE);
	while (raycaster->ray_index < GAME_WIDTH)
	{
		raycaster->ray_angle = player->angle - FOV_HALF + (raycaster->ray_index
				* RAY_ANGLE_DELTA);
		cast_ray(game, raycaster, player, projection);
		draw_3d_column(game);
		raycaster->ray_index++;
	}
}
