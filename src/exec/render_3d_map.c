/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:39:11 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/14 14:18:38 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

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

void draw_3d_column(t_game *game)
{
    int y;
       
    y = game->projection->wall_start;
    while (y <= game->projection->wall_end)
    {
        if (game->raycaster->ray_index >= 0 && game->raycaster->ray_index < GAME_WIDTH && y >= 0 && y < GAME_HEIGHT)
            my_mlx_pixel_put(game->game_img, game->raycaster->ray_index, y, YELLOW);
        y++;
    } 
}
void ray_caster(t_game *game, t_player *player, t_raycaster *raycaster, t_proj *projection)
{
    //this is the proper raycaster function;
    projection->distance_to_wall = sqrt(pow(raycaster->ray_x - player->player_px_pos_x, 2) + pow(raycaster->ray_y - player->player_px_pos_y, 2));     //--> record distance to wall : 
    projection->wall_height = (int)(TILE_SIZE * DISTANCE_TO_PLANE / projection->distance_to_wall);
    projection->wall_start = (GAME_HEIGHT / 2) - (projection->wall_height / 2);
    projection->wall_end = (GAME_HEIGHT / 2) + (projection->wall_height / 2);
    draw_3d_column(game);
}


void render_3d_map(t_game *game, t_player *player, t_raycaster *raycaster, t_proj *projection)
{
    clear_image(game->game_img);   
    raycaster->ray_index = 0;
    while (raycaster->ray_index < GAME_WIDTH)
    {
        raycaster->ray_angle = player->angle - (FOV_ANGLE / 2) + (raycaster->ray_index * (FOV_ANGLE / (GAME_WIDTH - 1)));
        raycaster->ray_x = player->player_px_pos_x;
        raycaster->ray_y = player->player_px_pos_y;
        while (game->map->map[(int)(raycaster->ray_y / TILE_SIZE)][(int)(raycaster->ray_x / TILE_SIZE)] != '1')
        {
            raycaster->ray_x += cos(raycaster->ray_angle);
            raycaster->ray_y -= sin(raycaster->ray_angle);
        }
        ray_caster(game, player, raycaster, projection);
        raycaster->ray_index++;
    }
}