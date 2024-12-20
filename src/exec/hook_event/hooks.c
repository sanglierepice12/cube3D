/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 08:32:40 by jedusser          #+#    #+#             */
/*   Updated: 2024/12/20 15:50:03 by jedusser         ###   ########.fr       */
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
	if (player->angle > 2 * M_PI)
		player->angle = 0;
}

void	update_position(t_game *game, float *new_x, float *new_y)
{
	if (game->player.move_up)
	{
		*new_x += MOVE_SPEED * cosf(game->player.angle);
		*new_y += MOVE_SPEED * sinf(game->player.angle);
	}
	else if (game->player.move_down)
	{
		*new_x -= MOVE_SPEED * cosf(game->player.angle);
		*new_y -= MOVE_SPEED * sinf(game->player.angle);
	}
	else if (game->player.move_left)
	{
		*new_x -= MOVE_SPEED * cosf(game->player.angle + M_PI * 0.5);
		*new_y -= MOVE_SPEED * sinf(game->player.angle + M_PI * 0.5);
	}
	else if (game->player.move_right)
	{
		*new_x += MOVE_SPEED * cosf(game->player.angle + M_PI * 0.5);
		*new_y += MOVE_SPEED * sinf(game->player.angle + M_PI * 0.5);
	}
}

void	handle_move(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->player.px_pos_x;
	new_y = game->player.px_pos_y;
	update_position(game, &new_x, &new_y);
	if (game->map->map[(int)(game->player.px_pos_y / TILE_SIZE)] \
						[(int)(new_x / TILE_SIZE)] != '1')
		game->player.px_pos_x = new_x;
	if (game->map->map[(int)(new_y / TILE_SIZE)] \
						[(int)(game->player.px_pos_x / TILE_SIZE)] != '1')
		game->player.px_pos_y = new_y;
}

int	handle_keypress(t_game *game)
{
	if (game->end)
	{
		printf("Exiting game...\n");
		mlx_loop_end(game->mlx_data.mlx_ptr);
		return (0);
	}
	if (game->player.rotate_left || game->player.rotate_right)
		handle_rotation(&game->player);
	if (game->player.move_down || game->player.move_up || game->player.move_left
		|| game->player.move_right)
		handle_move(game);
	return (0);
}
