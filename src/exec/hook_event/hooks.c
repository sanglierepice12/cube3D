/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:46 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/21 13:22:34 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"


void	handle_rotation(int keycode, t_player *player)
{
	if (keycode == LEFT_KEY)
		player->angle -= ROTATION_SPEED;
	else if (keycode == RIGHT_KEY)
		player->angle += ROTATION_SPEED;
	player->angle = fmod(player->angle, 2 * M_PI);
	if (player->angle < 0)
		player->angle += 2 * M_PI;
	// if (player->angle > 2 * M_PI)
	// 	player->angle = 0;
}

void update_position(t_game *game, int keycode, float *new_x, float *new_y)
{
	if (keycode == W_KEY)
	{
		*new_x += MOVE_SPEED * cos((float)game->player->angle);
		*new_y += MOVE_SPEED * sin(game->player->angle);
	}
	else if (keycode == S_KEY)
	{
		*new_x -= MOVE_SPEED * cos(game->player->angle);
		*new_y -= MOVE_SPEED * sin(game->player->angle);
	}
	else if (keycode == A_KEY)
	{
		*new_x -= MOVE_SPEED * cos(game->player->angle + M_PI * 0.5);
		*new_y -= MOVE_SPEED * sin(game->player->angle + M_PI * 0.5);
	}
	else if (keycode == D_KEY)
	{
		*new_x += MOVE_SPEED * cos(game->player->angle + M_PI * 0.5);
		*new_y += MOVE_SPEED * sin(game->player->angle + M_PI * 0.5);
	}
}

void	handle_move(int keycode, t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->player->player_px_pos_x;
	new_y = game->player->player_px_pos_y;
	update_position(game, keycode, &new_x, &new_y);
	if (game->map->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] != '1')
	{
		game->player->player_px_pos_x = new_x;
		game->player->player_px_pos_y = new_y;
	}
	
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == ESC_KEY) // Exit the game
	{
		clean_up(game);
		exit(0);
	}
	handle_rotation(keycode, game->player);
	handle_move(keycode, game);
	draw_and_display_map(game);
	mlx_put_image_to_window(game->mlx_data->mlx_ptr,
			game->mlx_data->game_win_ptr, game->game_img->img_ptr, 0, 0);
	return (0);
}
