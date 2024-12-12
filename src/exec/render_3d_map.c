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



void	render_3d_column(t_game *game,  t_proj *proj, t_ray *ray)
{
	int				y;
	float			tex_x;
	float			tex_y;
	float			tex_y_pos;
	float			step_size;
	unsigned int	pixel_color;

	def_wall_texture(proj, game->map);
	step_size = (float)proj->tex.height / proj->wall_height;

	if (ray->hit_side == HORIZONTAL)
		tex_x = fmodf(ray->px_x, TILE_SIZE);
	else
		tex_x = fmodf(ray->px_y, TILE_SIZE);

	tex_x = (tex_x * proj->tex.width) / TILE_SIZE;

	if (ray->hit_side == VERTICAL && ray->ray_dir_x < 0)
		tex_x = proj->tex.width - tex_x - 1;
	else if (ray->hit_side == HORIZONTAL && ray->ray_dir_y > 0)
		tex_x = proj->tex.width - tex_x - 1;

	if (proj->wall_start < 0)
	{
		tex_y_pos = -proj->wall_start * step_size;
		proj->wall_start = 0;
	}
	tex_y_pos = 0.0f;
	y = proj->wall_start;
	while (y <= proj->wall_end && y < GAME_HEIGHT)
	{
		tex_y = (int)tex_y_pos % proj->tex.height;
		pixel_color = get_pixel_color(&proj->tex, tex_x, tex_y);
		my_mlx_pixel_put(&game->game_img, ray->ray_index, y, pixel_color);
		tex_y_pos += step_size;
		y++;
	}
}

double	dist_to_wall(t_ray *ray, t_player *player)
{
	return (sqrtf((powf(player->px_pos_x - ray->px_x, 2) + powf(player->px_pos_y
					- ray->px_y, 2))));
}

void	update_proj_data(t_proj *proj, t_player *player, t_ray *ray)
{
	float	angle_diff;

	angle_diff = ray->ray_angle - player->angle;
	proj->distance_to_wall = dist_to_wall(ray, player);
	proj->correct_distance = proj->distance_to_wall * cosf(angle_diff);
	proj->wall_height = ((TILE_SIZE * dist_to_plane())
			/ proj->correct_distance);
	proj->wall_start = screen_center_y() - proj->wall_height * 0.5;
	proj->wall_end = screen_center_y() + proj->wall_height * 0.5;
}

void	cast_ray(t_game *game, t_ray *ray, t_player *player, t_proj *proj)
{
	float	step_size;
	int		prev_map_x;
	int		prev_map_y;

	ray->ray_dir_x = cos(ray->ray_angle);
	ray->ray_dir_y = sin(ray->ray_angle);
	step_size = fmaxf(0.01f, proj->distance_to_wall / GAME_WIDTH);
	while (!wall_hit(game->map, ray))
	{
		prev_map_x = get_map_coord(ray->px_x);
		prev_map_y = get_map_coord(ray->px_y);
		ray->px_x += ray->ray_dir_x * step_size;
		if (wall_hit(game->map, ray))
			break ;
		ray->px_y += ray->ray_dir_y * step_size;
	}
	def_hit_side(ray, prev_map_x, prev_map_y);
	update_proj_data(proj, player, ray);
	def_wall_orientation(proj, ray);
}

void	render_3d_map(t_game *game, t_player *player, t_ray *ray, t_proj *proj)
{
	ray->ray_index = 0;
	clear_screen(&game->game_img, game->map->ceiling_color,
			game->map->floor_color);
	while (ray->ray_index < GAME_WIDTH)
	{
		ray->px_x = player->px_pos_x;
		ray->px_y = player->px_pos_y;
		ray->ray_angle = (player->angle - fov_half()) \
						+ (ray->ray_index * ray_angle_delta());
		cast_ray(game, ray, player, proj);
		render_3d_column(game, proj, ray);
		ray->ray_index++;
	}
}
