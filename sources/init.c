/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:25:13 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/06 08:22:52 by jedusser         ###   ########.fr       */
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

void find_play_pos(t_map *map, t_player *player)
{
    int y;
    int x;

    y = 0;
    while (y < map->map_height)
    {
        x = 0;
        while (x < map->map_length)
        {
            if (map->map[y][x] == 'N')
            {
                player->player_pos_x = x;
                player->player_px_pos_x = (x * TILE_SIZE) + (TILE_SIZE / 2); 
                player->player_pos_y = y;
                player->player_px_pos_y = (y * TILE_SIZE) + (TILE_SIZE / 2); 
                player->direction = "N"; 
                player->angle = M_PI / 2;
                break;
            }
            x++;
        }
        y++;
    }
    // print no player found ?? this wil be done by parsing ?
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

int initialize_graphics(t_mlx_data *mlx_data, t_map *map, t_img_data *img)
{
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

int init_game(t_game *game)
{

    game->map = calloc(1, sizeof(t_map));  
    if (!game->map)
        return (-1);

    if (initialize_map(game->map) == -1)
        return (-1);
    
    game->player = calloc(1, sizeof(t_player));
    if (!game->player)
        return (-1);

    find_play_pos(game->map, game->player);

    game->mlx_data = calloc(1, sizeof(t_mlx_data));  
    if (!game->mlx_data)
        return (-1);

    game->img = calloc(1, sizeof(t_img_data));
    if (!game->img)
        return (-1);

    if (init_env(game->mlx_data, 1920, 1080, "Window") == -1)
        return (-1);

    if (initialize_graphics(game->mlx_data, game->map, game->img) == -1)
        return (-1);

    return (0);
}