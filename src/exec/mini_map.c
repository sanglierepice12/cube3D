/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 05:12:08 by jedusser          #+#    #+#             */
/*   Updated: 2024/12/19 11:26:52 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	draw_player(t_img_data *img, int start_x, int start_y, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < PLAYER_SIZE)
	{
		x = 0;
		while (x < PLAYER_SIZE)
		{
			my_mlx_pixel_put(img, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

int	draw_tile(t_img_data *img, int start_x, int start_y, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			if (x < BORDER_SIZE || x >= TILE_SIZE - BORDER_SIZE
				|| y < BORDER_SIZE || y >= TILE_SIZE - BORDER_SIZE)
				my_mlx_pixel_put(img, start_x + x, start_y + y, BLACK);
			else
				my_mlx_pixel_put(img, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
	return (0);
}

void	fill_tile_with_player(t_player *player, t_img_data *img, int tile_x,
		int tile_y)
{
	int	tile_start_x;
	int	tile_start_y;
	int	player_start_x;
	int	player_start_y;

	tile_start_x = tile_x * TILE_SIZE;
	tile_start_y = tile_y * TILE_SIZE;
	player_start_x = player->px_pos_x - (PLAYER_SIZE * 0.5);
	player_start_y = player->px_pos_y - (PLAYER_SIZE * 0.5);
	draw_tile(img, tile_start_x, tile_start_y, BLACK);
	draw_player(img, player_start_x, player_start_y, GREEN);
}

void	draw_map_rays(t_game *game, t_player *player, t_ray *ray)
{
	ray->ray_index = 0;
	while (ray->ray_index < GAME_WIDTH)
	{
		ray->px_y = player->px_pos_y;
		ray->px_x = player->px_pos_x;
		ray->ray_angle = player->angle + (fov_angle() * 2) - (ray->ray_index
				* (fov_angle() / (GAME_WIDTH - 1)));
		while (!wall_hit(game->map, ray))
		{
			my_mlx_pixel_put(&game->map_img, (int)ray->px_x, (int)ray->px_y, \
																		PINK);
			ray->px_x += sin(ray->ray_angle);
			if (wall_hit(game->map, ray))
				break ;
			ray->px_y -= cos(ray->ray_angle);
		}
		ray->ray_index++;
	}
}

void	draw_mini_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map->map[y])
	{
		x = 0;
		while (game->map->map[y][x])
		{
			if (game->map->map[y][x] == '1')
				draw_tile(&game->map_img, x * TILE_SIZE, y * TILE_SIZE, BLUE);
			if (game->map->map[y][x] == '0'
				|| game->map->map[y][x] == game->player.direction)
				draw_tile(&game->map_img, x * TILE_SIZE, y * TILE_SIZE, BLACK);
			x++;
		}
		y++;
	}
}
