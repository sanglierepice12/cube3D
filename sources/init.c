/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:25:13 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/04 15:58:50 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int init_env(t_mlx_data *mlx_data, int width, int height, char *title)
{
    mlx_data->mlx_ptr = mlx_init();
    if (!mlx_data->mlx_ptr)
        return (-1);

    mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, width, height, title);
    if (!mlx_data->win_ptr)
    {
        free(mlx_data->mlx_ptr);
        return (-1);
    }
    return (0);
}

int initialize_map(t_map *map)
{
    map->map_height = 8;
    map->map_length = 20;

    map->map = calloc(map->map_height + 1, sizeof(char *));
    if (!map->map)
        return (-1);

    if (fill_tab(map) == -1)
    {
        free(map->map);
        return (-1);
    }
    return (0);
}

int initialize_graphics(t_mlx_data *mlx_data, t_map *map, t_data *img)
{
    mlx_data->mlx_ptr = mlx_init();
    if (!mlx_data->mlx_ptr)
        return (-1);

    mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, 1920, 1080, "Window");
    if (!mlx_data->win_ptr)
        return (-1);

    img->img_ptr = mlx_new_image(mlx_data->mlx_ptr, map->map_length * TILE_SIZE, map->map_height * TILE_SIZE);
    if (!img->img_ptr)
        return (-1);

    img->addr = mlx_get_data_addr(img->img_ptr, &img->bits_per_pixel, &img->line_length, &img->endian);
    if (!img->addr)
    {
        mlx_destroy_image(mlx_data->mlx_ptr, img->img_ptr);
        return (-1);
    }

    return (0);
}

