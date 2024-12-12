/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:27:51 by jedusser          #+#    #+#             */
/*   Updated: 2024/12/12 12:39:04 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clear_screen(t_img_data *img, int ceiling_color, int floor_color)
{
	int	*pixel_data;
	int	total_pixels;
	int	i;

	pixel_data = (int *)img->addr;
	total_pixels = GAME_WIDTH * GAME_HEIGHT;
	i = 0;
	while (i < total_pixels)
	{
		if (i < GAME_WIDTH * screen_center_y())
			pixel_data[i] = ceiling_color;
		else
			pixel_data[i] = floor_color;
		i++;
	}
}

unsigned int	get_pixel_color(t_img_data *tex, int x, int y)
{
	int				offset;
	unsigned int	color;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	offset = (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	color = *(unsigned int *)(tex->addr + offset);
	return (color);
}

void	def_wall_color(t_proj *proj)
{
	if (proj->wall_orientation == NORTH)
		proj->wall_color = LIGHT_BLUE;
	else if (proj->wall_orientation == SOUTH)
		proj->wall_color = RED;
	else if (proj->wall_orientation == EAST)
		proj->wall_color = PINK;
	else if (proj->wall_orientation == WEST)
		proj->wall_color = GREEN;
}

void	def_wall_texture(t_proj *proj, t_map *map)
{
	if (proj->wall_orientation == NORTH)
		proj->tex = map->tex->tex1;
	else if (proj->wall_orientation == SOUTH)
		proj->tex = map->tex->tex2;
	else if (proj->wall_orientation == EAST)
		proj->tex = map->tex->tex3;
	else if (proj->wall_orientation == WEST)
		proj->tex = map->tex->tex4;
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
