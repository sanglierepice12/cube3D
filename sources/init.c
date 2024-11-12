/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:25:13 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/12 11:46:11 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int init_env(t_mlx_data *mlx_data, t_map *map)
{
    mlx_data->mlx_ptr = mlx_init();
    if (!mlx_data->mlx_ptr)
        return (-1);

    mlx_data->map_win_ptr = mlx_new_window(mlx_data->mlx_ptr, (map->map_length * TILE_SIZE) - TILE_SIZE, map->map_height * TILE_SIZE, "Minimap");
    if (!mlx_data->map_win_ptr)
    {
        free(mlx_data->mlx_ptr);
        return (-1);
    }
    mlx_data->game_win_ptr = mlx_new_window(mlx_data->mlx_ptr, GAME_WIDTH, GAME_HEIGHT, "Cub3d");
    if (!mlx_data->game_win_ptr)
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
                // these two lines go together; MPI/2 is angle based on direction N;
                
                // player->direction = "N"; 
                // player->angle = M_PI / 2;
                // player->direction = "S"; 
                // player->angle = M_PI * 2;
                // player->direction = "W"; 
                // player->angle = M_PI / 2;
                player->direction = "E"; 
                player->angle = M_PI * 2;
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

int initialize_graphics(t_mlx_data *mlx_data, t_map *map, t_img_data *map_img, t_img_data *game_img)
{
    map_img->img_ptr = mlx_new_image(mlx_data->mlx_ptr, map->map_length * TILE_SIZE, map->map_height * TILE_SIZE);
    if (!map_img->img_ptr)
        return (-1);
        
    game_img->img_ptr = mlx_new_image(mlx_data->mlx_ptr, GAME_WIDTH, GAME_HEIGHT);
    if (!game_img->img_ptr)
        return (-1);

    map_img->addr = mlx_get_data_addr(map_img->img_ptr, &map_img->bits_per_pixel, &map_img->line_length, &map_img->endian);
    if (!map_img->addr)
    {
        mlx_destroy_image(mlx_data->mlx_ptr, map_img->img_ptr);
        return (-1);
    }
    game_img->addr = mlx_get_data_addr(game_img->img_ptr, &game_img->bits_per_pixel, &game_img->line_length, &game_img->endian);
    if (!game_img->addr)
    {
        mlx_destroy_image(mlx_data->mlx_ptr, game_img->img_ptr);
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
    
    // game->player = calloc(1, sizeof(t_player));
    // if (!game->player)
    //     return (-1); --> see for dynamic allocation after;

    find_play_pos(game->map, game->player);

    game->mlx_data = calloc(1, sizeof(t_mlx_data));  
    if (!game->mlx_data)
        return (-1);

    game->map_img = calloc(1, sizeof(t_img_data));
    if (!game->map_img)
        return (-1);
        
    game->game_img = calloc(1, sizeof(t_img_data));
    if (!game->game_img)
        return (-1);

    if (init_env(game->mlx_data, game->map) == -1)
        return (-1);

    if (initialize_graphics(game->mlx_data, game->map, game->map_img, game->game_img) == -1)
        return (-1);

    return (0);
}