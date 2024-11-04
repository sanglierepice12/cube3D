/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:46 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/04 15:59:12 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int handle_keypress(int keycode, t_game *game)
{
    int new_x;
    int new_y;
    
    if (keycode == ESC_KEY)
    {
        clean_up(game);
        exit(0);
    }
    new_x = game->player->player_pos_x;
    new_y = game->player->player_pos_y;
    
    if (keycode == UP_KEY)
        new_y--;
    else if (keycode == DOWN_KEY)
        new_y++;
    else if (keycode == LEFT_KEY)
        new_x--;
    else if (keycode == RIGHT_KEY)
        new_x++;
    if (new_y >= 0 && new_y < game->map->map_height &&
        new_x >= 0 && new_x < game->map->map_length &&
        game->map->map[new_y][new_x] != '1')
    {
        game->player->player_pos_x = new_x;
        game->player->player_pos_y = new_y;
    }
    draw_mini_map(game);
    mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->win_ptr, game->img->img_ptr, 0, 0);
    return 0;
}