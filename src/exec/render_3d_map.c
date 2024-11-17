/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:39:11 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/17 11:21:58 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void clear_image(t_img_data *img, int ceiling_color, int floor_color)
{
    int *pixel_data = (int *)img->addr;
    int half_height = GAME_HEIGHT / 2;

    ft_memset(pixel_data, ceiling_color, half_height * GAME_WIDTH * sizeof(int));
    ft_memset(&pixel_data[half_height * GAME_WIDTH], floor_color, half_height * GAME_WIDTH * sizeof(int));
}



void draw_3d_column(t_game *game)
{
    int y_start;
    int y_end;
    int y;
    
    y_start = game->projection->wall_start;
    y_end = game->projection->wall_end;
    if (game->raycaster->ray_index >= 0 && game->raycaster->ray_index < GAME_WIDTH)
    {
        y = y_start;
        while (y <= y_end)
        {
            if (y >= 0 && y < GAME_HEIGHT)
                my_mlx_pixel_put(game->game_img, game->raycaster->ray_index, y, YELLOW);
            y++;
        }
    }
}
void ray_caster(t_game *game, t_player *player, t_raycaster *raycaster, t_proj *projection)
{
    float step_x;
    float step_y;
    
    projection->distance_to_wall = DISTANCE(raycaster->ray_x, raycaster->ray_y, player->player_px_pos_x, player->player_px_pos_y);
    projection->wall_height = (int)(TILE_SIZE * DISTANCE_TO_PLANE / projection->distance_to_wall);
    projection->wall_start = SCREEN_CENTER_Y - (projection->wall_height / 2);
    projection->wall_end = SCREEN_CENTER_Y + (projection->wall_height / 2);
    step_x = cos(raycaster->ray_angle);
    step_y = -sin(raycaster->ray_angle);
    while (game->map->map[(int)(raycaster->ray_y / TILE_SIZE)][(int)(raycaster->ray_x / TILE_SIZE)] != '1')
    {
        raycaster->ray_x += step_x;
        raycaster->ray_y += step_y;
    }
    draw_3d_column(game);
}



void render_3d_map(t_game *game, t_player *player, t_raycaster *raycaster, t_proj *projection)
{
    float ray_cos;
    float ray_sin;
    
    clear_image(game->game_img, BLACK, LIGHT_BLUE);
    raycaster->ray_index = 0;
    while (raycaster->ray_index < GAME_WIDTH)
    {
        raycaster->ray_angle = player->angle - FOV_HALF + (raycaster->ray_index * RAY_ANGLE_DELTA);
        ray_cos = cos(raycaster->ray_angle);
        ray_sin = sin(raycaster->ray_angle);
        raycaster->ray_x = player->player_px_pos_x;
        raycaster->ray_y = player->player_px_pos_y;
        while (game->map->map[(int)(raycaster->ray_y / TILE_SIZE)][(int)(raycaster->ray_x / TILE_SIZE)] != '1')
        {
            raycaster->ray_x += ray_cos;
            raycaster->ray_y += ray_sin;
        }
        ray_caster(game, player, raycaster, projection);
        raycaster->ray_index++;
    }
}
