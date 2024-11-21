/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:26:46 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/21 16:03:25 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void	handle_rotation(t_player *player)
{
	if (player->rotate_left)
		player->angle -= ROTATION_SPEED;
	else if (player->rotate_right)
		player->angle += ROTATION_SPEED;
	player->angle = fmod(player->angle, 2 * M_PI);
	if (player->angle < 0)
		player->angle += 2 * M_PI;
	// if (player->angle > 2 * M_PI)
	// 	player->angle = 0;
}

void update_position(t_game *game, float *new_x, float *new_y)
{
	if (game->player->move_up)
	{
		*new_x += MOVE_SPEED * cos(game->player->angle);
		*new_y += MOVE_SPEED * sin(game->player->angle);
	}
	else if (game->player->move_down)
	{
		*new_x -= MOVE_SPEED * cos(game->player->angle);
		*new_y -= MOVE_SPEED * sin(game->player->angle);
	}
	else if (game->player->move_left)
	{
		*new_x -= MOVE_SPEED * cos(game->player->angle + M_PI * 0.5);
		*new_y -= MOVE_SPEED * sin(game->player->angle + M_PI * 0.5);
	}
	else if (game->player->move_right)
	{
		*new_x += MOVE_SPEED * cos(game->player->angle + M_PI * 0.5);
		*new_y += MOVE_SPEED * sin(game->player->angle + M_PI * 0.5);
	}
}

void	handle_move(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->player->player_px_pos_x;
	new_y = game->player->player_px_pos_y;
	
	update_position(game, &new_x, &new_y);
	
	if (game->map->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] != '1')
	{
		game->player->player_px_pos_x = new_x;
		game->player->player_px_pos_y = new_y;
	}
	
}

int	handle_keypress(t_game *game)
{
	// if (keycode == ESC_KEY) // Exit the game
	// {
	// 	clean_up(game);
	// 	exit(0);
	// }
	if (game->player->rotate_left || game->player->rotate_right)
		handle_rotation(game->player);
		
	else if (game->player->move_down || game->player->move_up)
		handle_move(game);
		
	if (game->player->move_left || game->player->move_right)
		handle_move(game);
		
	// draw_and_display_map(game);
	// mlx_put_image_to_window(game->mlx_data->mlx_ptr,
	// 		game->mlx_data->game_win_ptr, game->game_img->img_ptr, 0, 0);
	return (0);
}
