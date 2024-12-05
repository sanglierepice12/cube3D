/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:27:51 by jedusser          #+#    #+#             */
/*   Updated: 2024/12/05 14:20:48 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	def_wall_color(t_raycaster *raycaster, t_proj *projection)
{
	if (raycaster->wall_orientation == NORTH)
		projection->wall_color = LIGHT_BLUE;
	else if (raycaster->wall_orientation == SOUTH)
		projection->wall_color = RED;
	else if (raycaster->wall_orientation == EAST)
		projection->wall_color = PINK;
	else if (raycaster->wall_orientation == WEST)
		projection->wall_color = GREEN;
	else
		projection->wall_color = WHITE;
}

void	clear_screen(t_img_data *img, int ceiling_color, int floor_color)
{
	int	*pixel_data;
	int	half_height;

	pixel_data = (int *)img->addr;
	half_height = SCREEN_CENTER_Y;
	ft_memset(pixel_data, ceiling_color, half_height * GAME_WIDTH * sizeof(int));
	ft_memset(&pixel_data[half_height * (int)GAME_WIDTH], floor_color, half_height * GAME_WIDTH * sizeof(int));
}
