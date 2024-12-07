/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 11:10:56 by jedusser          #+#    #+#             */
/*   Updated: 2024/12/07 10:56:59 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

bool	wall_hit(t_map *map, t_ray *ray)
{
	return (map->map[(int)(ray->ray_y / TILE_SIZE)][(int)(ray->ray_x
			/ TILE_SIZE)] == '1' ||
			map->map[(int)(ray->ray_y / TILE_SIZE)][(int)(ray->ray_x
					/ TILE_SIZE)] == ' ');
	// raycaster->ray_y / TILE_SIZE transfrom logic for cartesian
}

bool	key_active(t_game *game)
{
	return (game->end || game->player.move_down || game->player.move_up || \
	game->player.move_left || game->player.move_right || \
	game->player.rotate_left || game->player.rotate_right);
}

