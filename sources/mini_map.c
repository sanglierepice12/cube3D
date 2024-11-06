/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 05:12:08 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/06 09:01:53 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"


void draw_player(t_img_data *img, int start_x, int start_y, int color)
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

int draw_tile(t_img_data *img, int start_x, int start_y, int color)
{
    int x;
    int y;

    y = 0;
    while(y < TILE_SIZE)
    {
        x = 0;
        while (x < TILE_SIZE)
        {
            if (x < BORDER_SIZE || x >= TILE_SIZE - BORDER_SIZE || y < BORDER_SIZE || y >= TILE_SIZE - BORDER_SIZE)
                my_mlx_pixel_put(img, start_x + x, start_y + y, BLACK);
            else 
                my_mlx_pixel_put(img, start_x + x, start_y + y, color);
            x++;
        }
        y++;
    }
    return (0);
}

void fill_tile_with_player(t_img_data *img, int tile_x, int tile_y, int floor_color, int player_color)
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
// void trace_ray(t_game *game, t_player *player)
// {
//     double ray_x;
//     double ray_y;
//     double ray_angle;

//     ray_x = player->player_px_pos_x;
//     ray_y = player->player_px_pos_y;
//     ray_angle = player->angle;
//     printf("%s\n", player->direction);
//     printf("%f\n", ray_x);
//     while (game->map->map[(int)(ray_y / TILE_SIZE)][(int)(ray_x / TILE_SIZE)] != '1')
//     {
//         my_mlx_pixel_put(game->img, (int)ray_x, (int)ray_y, BLACK);
//         ray_x += cos(ray_angle) * STEP_SIZE;
//         ray_y -= sin(ray_angle) * STEP_SIZE;
//     }
// }

//  multiple  rays to be traced i a ranged of a 60 degres fov
void trace_rays(t_game *game, t_player *player)
{
    double ray_angle;
    double ray_x;
    double ray_y;
    int ray_index;

    ray_index = 0;
    while (ray_index < RAY_COUNT)
    {
        ray_angle = player->angle - (FOV_ANGLE / 2) + (ray_index * (FOV_ANGLE / (RAY_COUNT - 1)));
        ray_x = player->player_px_pos_x;
        ray_y = player->player_px_pos_y;
        while (game->map->map[(int)(ray_y / TILE_SIZE)][(int)(ray_x / TILE_SIZE)] != '1')
        {
            my_mlx_pixel_put(game->img, (int)ray_x, (int)ray_y, BLACK);
            ray_x += cos(ray_angle) * STEP_SIZE;
            ray_y -= sin(ray_angle) * STEP_SIZE;
        }
       // printf("hit !!! a wall at %f, %f \n", ray_index, ray_x, ray_y);
    
        ray_index++;
    }
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
                draw_tile(game->img, x * TILE_SIZE, y * TILE_SIZE, BLUE);
			if (game->map->map[y][x] == '0'|| game->map->map[y][x] == 'N' )
                draw_tile(game->img, x * TILE_SIZE, y * TILE_SIZE, WHITE);
            //--> center of playr check :
            my_mlx_pixel_put(game->img, game->player->player_px_pos_x, game->player->player_px_pos_y, BLACK);
            x++;
        }
        y++;
    }
    fill_tile_with_player(game->img, game->player->player_pos_x, game->player->player_pos_y, WHITE, GREEN);
    trace_rays(game, game->player);
}

void draw_and_display_map(t_game *game)
{
    draw_mini_map(game);
    mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->win_ptr, game->img->img_ptr, 0, 0);
    mlx_hook(game->mlx_data->win_ptr, 2, 1L<<0, handle_keypress, game); 
}