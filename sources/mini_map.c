/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 05:12:08 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/04 16:15:56 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"


void draw_player(t_data *img, int start_x, int start_y, int color)
{
    int x;
    int y;

    y = 0;
    while (y < PLAYER_SIZE)
    {
        x = 0;
        while (x < PLAYER_SIZE)
        {
            my_mlx_pixel_put(img, start_x + x, start_y + y, color);
            x++;
        }
        y++;
    }
}

int draw_tile(t_data *img, int start_x, int start_y, int color)
{
    int x;
    int y;

    y = 0;
    while(y < TILE_SIZE)
    {
        x = 0;
        while (x < TILE_SIZE)
        {
            my_mlx_pixel_put(img, start_x + x, start_y + y, color);
            x++;
        }
        y++;
    }
    return (0);
}

void fill_tile_with_player(t_data *img, int tile_x, int tile_y, int floor_color, int player_color)
{
    int tile_start_x;
    int tile_start_y;
    int player_start_x;
    int player_start_y;
    
    tile_start_x = tile_x * TILE_SIZE;
    tile_start_y = tile_y * TILE_SIZE;

    draw_tile(img, tile_start_x, tile_start_y, floor_color);

    player_start_x = tile_start_x + (TILE_SIZE - PLAYER_SIZE) / 2;
    player_start_y = tile_start_y + (TILE_SIZE - PLAYER_SIZE) / 2;

    draw_player(img, player_start_x, player_start_y, player_color);
}

void draw_mini_map(t_game *game)
{
    int x;
    int y;

    y = 0;
    while (game->map->map[y])
	{
		x = 0; 
        while (game->map->map[y][x])
		{
            if (game->map->map[y][x] == '1')
                draw_tile(game->img, x * TILE_SIZE, y * TILE_SIZE, 0x0000FF); // blue
			if (game->map->map[y][x] == '0'|| game->map->map[y][x] == 'N' )
                draw_tile(game->img, x * TILE_SIZE, y * TILE_SIZE, 0xFFFFFF); //red
			//if (map->map[y][x] == 'N')
			//8 and 6 will be play pos x and ply pos y;
            fill_tile_with_player(game->img, game->player->player_pos_x, game->player->player_pos_y, 0xFFFFFFF, 0x00FF000);
            x++;
        }
        y++;
    }
}

void draw_and_display_map(t_game *game)
{
    draw_mini_map(game);
    mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->win_ptr, game->img->img_ptr, 0, 0);
    mlx_hook(game->mlx_data->win_ptr, 2, 1L<<0, handle_keypress, game); 
}