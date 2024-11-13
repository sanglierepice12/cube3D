/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 05:12:08 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/13 12:05:39 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"



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

// int get_pixel_color(void *img, int x, int y)
// {
//     char    *data;
//     int     bpp;
//     int     size_line;
//     int     endian;
//     int     color;

//     data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
    
//     color = *(int *)(data + (y * size_line + x * (bpp / 8)));

//     return (color);
// }


void clear_image(t_img_data *img)
{
    int x;
    int y;

    y = 0;
    while (y < GAME_HEIGHT)
    {
        x = 0;
        while ( x < GAME_WIDTH )
        {
            my_mlx_pixel_put(img, x, y, BLACK);  // Background color
            x++;
        }
        y++;
    }
}

void draw_3d_ray(t_game *game, t_player *player, t_raycaster *raycaster, t_proj *projection)
{
  
    int y;
    
    
    projection->distance_to_wall = sqrt(pow(raycaster->ray_x - player->player_px_pos_x, 2) + pow(raycaster->ray_y - player->player_px_pos_y, 2));     //--> record distance to wall : 
    projection->wall_height = (int)(TILE_SIZE * DISTANCE_TO_PLANE / projection->distance_to_wall);
    projection->wall_start = (GAME_HEIGHT / 2) - (projection->wall_height / 2);
    projection->wall_end = (GAME_HEIGHT / 2) + (projection->wall_height / 2);
    y = projection->wall_start;
    
    while (y <= projection->wall_end)
    {
        if (raycaster->ray_index >= 0 && raycaster->ray_index < GAME_WIDTH && y >= 0 && y < GAME_HEIGHT)
            my_mlx_pixel_put(game->game_img, raycaster->ray_index, y, YELLOW);
        y++;
    }
}

void ray_caster(t_game *game, t_player *player, t_raycaster *raycaster, t_proj *projection)
{
    clear_image(game->game_img);    
    raycaster->ray_index = 0;
    while (raycaster->ray_index < RAY_COUNT)
    {
        raycaster->ray_angle = player->angle - (FOV_ANGLE / 2) + (raycaster->ray_index * (FOV_ANGLE / (RAY_COUNT - 1)));
        raycaster->ray_x = player->player_px_pos_x;
        raycaster->ray_y = player->player_px_pos_y;
        while (game->map->map[(int)(raycaster->ray_y / TILE_SIZE)][(int)(raycaster->ray_x / TILE_SIZE)] != '1')
        {
            if (raycaster->ray_index == (RAY_COUNT / 2))
                my_mlx_pixel_put(game->map_img, (int)raycaster->ray_x, (int)raycaster->ray_y, GREEN);
            else
                my_mlx_pixel_put(game->map_img, (int)raycaster->ray_x, (int)raycaster->ray_y, PINK);
            raycaster->ray_x += cos(raycaster->ray_angle);
            raycaster->ray_y -= sin(raycaster->ray_angle);
        }
        draw_3d_ray(game, player, raycaster, projection);
        raycaster->ray_index++;
    }
} // here i draw rays on minimap, and also, render each single ray on the 3d screen;

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
            x++;
        }
        y++;
    }
    ray_caster(game, game->player, game->raycaster, game->projection);
    fill_tile_with_player(game->map_img, game->player->player_pos_x, game->player->player_pos_y, BLACK, GREEN);
}

void draw_and_display_map(t_game *game) 
{
    draw_mini_map(game);
    mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->map_win_ptr, game->map_img->img_ptr, 0, 0);
    mlx_put_image_to_window(game->mlx_data->mlx_ptr, game->mlx_data->game_win_ptr, game->game_img->img_ptr, 0, 0);
    mlx_hook(game->mlx_data->map_win_ptr, 2, 1L<<0, handle_keypress, game); 
    mlx_hook(game->mlx_data->game_win_ptr, 2, 1L<<0, handle_keypress, game); 
}