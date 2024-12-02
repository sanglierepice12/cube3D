/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 11:10:56 by jedusser          #+#    #+#             */
/*   Updated: 2024/12/02 10:14:12 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

bool	wall_hit(t_map *map, t_raycaster *raycaster)
{
	return (map->map[(int)(raycaster->ray_y / TILE_SIZE)][(int)(raycaster->ray_x
			/ TILE_SIZE)] == '1' ||
			map->map[(int)(raycaster->ray_y / TILE_SIZE)][(int)(raycaster->ray_x
					/ TILE_SIZE)] == ' ');
	// raycaster->ray_y / TILE_SIZE transfrom logic for cartesian
}

bool	key_active(t_game *game)
{
	return (game->end || game->player.move_down || game->player.move_up || \
	game->player.move_left || game->player.move_right || \
	game->player.rotate_left || game->player.rotate_right);
}

void	def_hit_side(t_raycaster *raycaster, float ray_dir_x, float ray_dir_y)
{
	if (raycaster->hit_side == 1)
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
}
