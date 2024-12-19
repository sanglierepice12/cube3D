/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:08:54 by jedusser          #+#    #+#             */
/*   Updated: 2024/12/19 12:50:31 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

double	dist_to_plane(void)
{
	return ((GAME_WIDTH * 0.5f / tan(fov_half())));
}

double	fov_angle(void)
{
	return (M_PI * 0.3f);
}

double	fov_half(void)
{
	return ((M_PI * 0.3f) * 0.5f);
}

double	ray_angle_delta(void)
{
	return (fov_angle() / GAME_WIDTH);
}

double	dist_to_wall(t_ray *ray, t_player *player)
{
	return (sqrtf((powf(player->px_pos_x - ray->px_x, 2) \
				+ powf(player->px_pos_y - ray->px_y, 2))));
}
