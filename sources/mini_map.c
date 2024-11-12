/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 05:12:08 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/12 12:24:54 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


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
            // if (x < BORDER_SIZE || x >= TILE_SIZE - BORDER_SIZE || y < BORDER_SIZE || y >= TILE_SIZE - BORDER_SIZE)
            //     my_mlx_pixel_put(img, start_x + x, start_y + y, BLACK);
            // else 
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

int get_pixel_color(void *img, int x, int y)
{
    char    *data;
    int     bpp;
    int     size_line;
    int     endian;
    int     color;

    data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
    
    color = *(int *)(data + (y * size_line + x * (bpp / 8)));

    return (color);
}


void trace_rays(t_game *game, t_player *player)
{
    double  ray_angle;
    double  ray_x;
    double ray_y;
    int ray_index;
    long distance_to_wall;
    int wall_height;
    int wall_start;
    int wall_end;
    int y;
    
    ray_index = 0;
    while (ray_index <  RAY_COUNT)
    {
        ray_angle = player->angle - (FOV_ANGLE / 2) + (ray_index * (FOV_ANGLE / (RAY_COUNT - 1)));
        ray_x = player->player_px_pos_x;
        ray_y = player->player_px_pos_y;
        while (game->map->map[(int)(ray_y / TILE_SIZE)][(int)(ray_x / TILE_SIZE)] != '1')
        {
            // printf("distance to wall 1 = %ld\n", distance_to_wall);
            if (ray_index == (RAY_COUNT / 2))
            {
                my_mlx_pixel_put(game->map_img, (int)ray_x, (int)ray_y, GREEN);
            }
            else
            {
                my_mlx_pixel_put(game->map_img, (int)ray_x, (int)ray_y, PINK);
            } 
            ray_x += cos(ray_angle);// * STEP_SIZE;
            ray_y -= sin(ray_angle);// * STEP_SIZE;
        }
        printf("ray nb[%d] hit wall at x->[%f, %f]<-y \n", ray_index, ray_x, ray_y);
        distance_to_wall = sqrt(pow(ray_x - player->player_px_pos_x, 2) + pow(ray_y - player->player_px_pos_y, 2));     //--> record distance to wall : 
        wall_height = (int)(TILE_SIZE * DISTANCE_TO_PLANE / distance_to_wall);
        wall_start = (GAME_HEIGHT / 2) - (wall_height / 2);
        wall_end = (GAME_HEIGHT / 2) + (wall_height / 2);
        y = wall_start;
        while (y <= wall_end)
        {
            if (ray_index >= 0 && ray_index < GAME_WIDTH && y >= 0 && y < GAME_HEIGHT)
                my_mlx_pixel_put(game->game_img, ray_index, y, YELLOW);
            y++;
        }
        printf("ray nb[%d is %ld distant to wall\n", ray_index, distance_to_wall);
        //my_mlx_pixel_put(game->map_img, ray_x, ray_y, YELLOW);
       // my_mlx_pixel_put(game->game_img, ray_x, ray_y, YELLOW);
        ray_index++;
    }
}


// in fact,heere  i can have distance to wall for each ray, but i need the player distance to wall to 
// (maybe only center ray will be enought first), THEN capture the rays lengths at positon, and draw from here, based on Window_width

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
                draw_tile(game->map_img, x * TILE_SIZE, y * TILE_SIZE, BLUE);
			if (game->map->map[y][x] == '0'|| game->map->map[y][x] == 'N' )
                draw_tile(game->map_img, x * TILE_SIZE, y * TILE_SIZE, BLACK);
            //--> center of playr check :
            my_mlx_pixel_put(game->map_img, game->player->player_px_pos_x, game->player->player_px_pos_y, BLACK);
            x++;
        }
        y++;
    }
    fill_tile_with_player(game->map_img, game->player->player_pos_x, game->player->player_pos_y, BLACK, GREEN);
    trace_rays(game, game->player);
}

void draw_and_display_map(t_game *game) // and game;
{
    draw_mini_map(game);
    mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->map_win_ptr, game->map_img->img_ptr, 0, 0);
    mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->game_win_ptr, game->game_img->img_ptr, 0, 0);
    mlx_hook(game->mlx_data->map_win_ptr, 2, 1L<<0, handle_keypress, game); 
    mlx_hook(game->mlx_data->game_win_ptr, 2, 1L<<0, handle_keypress, game); 
}