/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 05:22:20 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/04 16:15:32 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void clean_up(t_game *game)
{
    if (game->map)
    {
        free_tab(game->map->map);
        free(game->map);
    }
    if (game->img && game->mlx_data)
        mlx_destroy_image(game->mlx_data->mlx_ptr, game->img->img_ptr);
    if (game->mlx_data)
    {
        mlx_destroy_window(game->mlx_data->mlx_ptr, game->mlx_data->win_ptr);
        free(game->mlx_data);
    }
    if (game->player)
        free(game->player);
    if (game->img)
        free(game->img);
}

int init_game(t_game *game)
{
    game->player = calloc(1, sizeof(t_player));
    if (!game->player)
        return (-1);

    game->player->player_pos_x = 10;
    game->player->player_pos_y = 5; // provided later by parsing 

    game->map = calloc(1, sizeof(t_map));  
    if (!game->map)
        return (-1);

    if (initialize_map(game->map) == -1)
        return (-1);

    game->mlx_data = calloc(1, sizeof(t_mlx_data));  
    if (!game->mlx_data)
        return (-1);

    game->img = calloc(1, sizeof(t_data));
    if (!game->img)
        return (-1);

    if (init_env(game->mlx_data, 1920, 1080, "Window") == -1)
        return (-1);

    if (initialize_graphics(game->mlx_data, game->map, game->img) == -1)
        return (-1);

    return (0);
}

int main(void)
{
    t_game game;
    if (init_game(&game) == -1)
    {
        clean_up(&game);
        return (1);
    }
    draw_and_display_map(&game);
    mlx_loop(game.mlx_data->mlx_ptr);
    clean_up(&game);
    return (0);
}



