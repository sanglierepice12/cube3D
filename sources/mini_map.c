/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 05:12:08 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/11 11:01:10 by jedusser         ###   ########.fr       */
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

// void render_3d_view(t_game *game, t_player *player)
// {
//     double ray_angle;
//     double ray_x, ray_y;
//     int ray_index;
//     double distance_to_wall;
//     int wall_height;
//     int wall_start, wall_end;
    
//     ray_index = 0;
//     while (ray_index < RAY_COUNT)
//     {
//         ray_angle = player->angle - (FOV_ANGLE / 2) + (ray_index * (FOV_ANGLE / (RAY_COUNT - 1)));
//         ray_x = player->player_px_pos_x;
//         ray_y = player->player_px_pos_y;
        
//         // Cast ray until it hits a wall
//         while (game->map->map[(int)(ray_y / TILE_SIZE)][(int)(ray_x / TILE_SIZE)] != '1')
//         {
//             ray_x += cos(ray_angle);
//             ray_y -= sin(ray_angle);
//         }
        
//         // Calculate distance to wall
//         distance_to_wall = sqrt(pow(ray_x - player->player_px_pos_x, 2) + pow(ray_y - player->player_px_pos_y, 2));
        
//         // Project the wall height based on distance
//         wall_height = (int)(TILE_SIZE * DISTANCE_TO_PROJECTION_PLANE / distance_to_wall);
        
//         // Calculate where to start and end the wall slice on screen
//         wall_start = (SCREEN_HEIGHT / 2) - (wall_height / 2);
//         wall_end = (SCREEN_HEIGHT / 2) + (wall_height / 2);
        
//         // Draw the vertical wall slice on the screen
//         int y = wall_start;
//         while (y <= wall_end)
//         {
//             my_mlx_pixel_put(game->game_img, ray_index, y, WALL_COLOR);
//             y++;
//         }

//         ray_index++;
//     }
// }

//double distance_to_projection_plane = SCREEN_WIDTH / (2 * tan(FOV_ANGLE / 2));



void trace_rays(t_game *game, t_player *player)
{
    double ray_angle;
    double ray_x;
    double ray_y;
    int ray_index;


    ray_index = 0;
    while (ray_index < RAY_COUNT )
    {
        ray_angle = player->angle - (FOV_ANGLE / 2) + (ray_index * (FOV_ANGLE / (RAY_COUNT - 1)));
        ray_x = player->player_px_pos_x;
        ray_y = player->player_px_pos_y;
        while (game->map->map[(int)(ray_y / TILE_SIZE)][(int)(ray_x / TILE_SIZE)] != '1')
        {
            if (ray_index == (RAY_COUNT / 2))
            {
                my_mlx_pixel_put(game->map_img, (int)ray_x, (int)ray_y, GREEN);
                
            }
            else
                my_mlx_pixel_put(game->map_img, (int)ray_x, (int)ray_y, PINK);
            ray_x += cos(ray_angle); // * STEP_SIZE;
            ray_y -= sin(ray_angle); // * STEP_SIZE;
        }
        printf("hit wall at y->[%f, %f]<-x \n", ray_x, ray_y);
        //--> record distance to wall : 
        my_mlx_pixel_put(game->map_img, ray_x, ray_y, YELLOW);
        my_mlx_pixel_put(game->game_img, ray_x, ray_y, YELLOW);
    
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