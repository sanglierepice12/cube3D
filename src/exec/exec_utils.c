/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 11:10:56 by jedusser          #+#    #+#             */
/*   Updated: 2024/12/10 13:02:22 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

bool wall_hit(t_map *map, t_ray *ray)
{
    int map_x = (int)floor(ray->px_x / TILE_SIZE);
    int map_y = (int)floor(ray->px_y / TILE_SIZE);

    // Check for wall ('1') or empty space (' ')
    return (map->map[map_y][map_x] == '1' || map->map[map_y][map_x] == ' ');
}


bool	key_active(t_game *game)
{
	return (game->end || game->player.move_down || game->player.move_up || \
	game->player.move_left || game->player.move_right || \
	game->player.rotate_left || game->player.rotate_right);
}

