/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:27:51 by jedusser          #+#    #+#             */
/*   Updated: 2024/12/07 12:02:18 by jedusser         ###   ########.fr       */
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
	int	half_height;

	pixel_data = (int *)img->addr;
	half_height = SCREEN_CENTER_Y;
	ft_memset(pixel_data, ceiling_color, half_height * GAME_WIDTH * sizeof(int));
	ft_memset(&pixel_data[half_height * (int)GAME_WIDTH], floor_color, half_height * GAME_WIDTH * sizeof(int));
}

unsigned int    get_pixel_color(t_img_data *texture, int x, int y)
{
    int                offset;
    unsigned int    color;

    if (x < 0  || x >= texture->width|| y < 0 || y >= texture->height)
        return (0);
    offset = (y * texture->line_length + x * (texture->bits_per_pixel / 8));
    color = *(unsigned int*)(texture->addr + offset);
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
		proj->texture = map->texture->texture1;
	else if (proj->wall_orientation == SOUTH)
		proj->texture = map->texture->texture2;
	else if (proj->wall_orientation == EAST)
		proj->texture = map->texture->texture3;
	else if (proj->wall_orientation == WEST)
		proj->texture = map->texture->texture4;
}

void	def_wall_orientation(t_proj *proj, t_ray *raycaster, float ray_dir_x, float ray_dir_y)
{
	if (raycaster->hit_side == 1)
	{
		if (ray_dir_x > 0)
			proj->wall_orientation = EAST;
		else
			proj->wall_orientation = WEST;
	}
	else
	{
		if (ray_dir_y > 0)
			proj->wall_orientation = SOUTH;
		else
			proj->wall_orientation = NORTH;
	}
}
