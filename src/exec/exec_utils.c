/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 11:10:56 by jedusser          #+#    #+#             */
/*   Updated: 2024/12/20 14:49:24 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

bool	wall_hit(t_map *map, t_ray *ray)
{
	int	map_x;
	int	map_y;
	map_x = (int)floor(ray->px_x / TILE_SIZE);
	map_y = (int)floor(ray->px_y / TILE_SIZE);
	return (map->map[map_y][map_x] == '1' || map->map[map_y][map_x] == ' ' || map->map[map_y][map_x] == '#');
}

int	get_map_coord(double px_x)
{
	return (px_x / TILE_SIZE);
}

void	def_wall_orientation(t_proj *proj, t_ray *ray)
{
	if (ray->hit_side == VERTICAL)
	{
		if (ray->ray_dir_x > 0)
			proj->wall_orientation = EAST;
		else
			proj->wall_orientation = WEST;
	}
	else if (ray->hit_side == HORIZONTAL)
	{
		if (ray->ray_dir_y > 0)
			proj->wall_orientation = SOUTH;
		else
			proj->wall_orientation = NORTH;
	}
}

void	def_hit_side(t_ray *ray, int prev_map_x, int prev_map_y)
{
	int	ray_map_x;
	int	ray_map_y;

	ray_map_x = get_map_coord(ray->px_x);
	ray_map_y = get_map_coord(ray->px_y);
	if (ray_map_x != prev_map_x)
		ray->hit_side = VERTICAL;
	if (ray_map_y != prev_map_y)
		ray->hit_side = HORIZONTAL;
}
