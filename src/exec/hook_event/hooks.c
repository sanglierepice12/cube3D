/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:46 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/20 13:48:04 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void handle_rotation(int keycode, t_player *player)
{
    if (keycode == LEFT_KEY)
        player->angle -= ROTATION_SPEED;
    else if (keycode == RIGHT_KEY)
        player->angle += ROTATION_SPEED;
    player->angle = fmod(player->angle, 2 * M_PI);
	printf("player angle : %f\n", player->angle);

    if (player->angle < 0)
        player->angle += 2 * M_PI;
}

int	handle_keypress(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player->player_pos_x;
	new_y = game->player->player_pos_y;
	if (keycode == ESC_KEY)
	{
		clean_up(game);
		exit(0);
	}
	if (keycode == W_KEY )
	{
			new_y--;
	}
	else if (keycode == S_KEY)
		new_y++;
	else if (keycode == A_KEY)
		new_x--;
	else if (keycode == D_KEY)
		new_x++;
	if (new_y >= 0 && new_y < game->map->map_height &&
		new_x >= 0 && new_x < game->map->map_length &&
		game->map->map[new_y][new_x] != '1')
	{
		game->player->player_pos_x = new_x;
		game->player->player_pos_y = new_y;
		game->player->player_px_pos_x = new_x * TILE_SIZE + TILE_SIZE * 0.5; // cos (x)
		game->player->player_px_pos_y = new_y * TILE_SIZE + TILE_SIZE * 0.5; // sin(y)
	}
	handle_rotation(keycode, game->player);
	draw_and_display_map(game);
	mlx_put_image_to_window(game->mlx_data->mlx_ptr,
			game->mlx_data->game_win_ptr, game->game_img->img_ptr, 0, 0);
	mlx_put_image_to_window(game->mlx_data->mlx_ptr,
							game->mlx_data->game_win_ptr,
							game->game_img->img_ptr, 0, 0);
	return (0);
}
