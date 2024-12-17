/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:08:54 by jedusser          #+#    #+#             */
/*   Updated: 2024/12/17 08:33:05 by jedusser         ###   ########.fr       */
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
	return ((M_PI * 0.3f) * 0.5);
}

double	ray_angle_delta(void)
{
	return (fov_angle() / GAME_WIDTH);
}

int	screen_center_y(void)
{
	return (GAME_HEIGHT * 0.5);
}
