/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_managment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:14:18 by jedusser          #+#    #+#             */
/*   Updated: 2024/12/18 15:32:47 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

bool	key_active(t_game *game)
{
	return (game->end || game->player.move_down || game->player.move_up \
					|| game->player.move_left || game->player.move_right \
					|| game->player.rotate_left || game->player.rotate_right);
}

int	key_up(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		game->player.move_up = 0;
	if (keycode == A_KEY)
		game->player.move_left = 0;
	if (keycode == S_KEY)
		game->player.move_down = 0;
	if (keycode == D_KEY)
		game->player.move_right = 0;
	if (keycode == LEFT_KEY)
		game->player.rotate_left = 0;
	if (keycode == RIGHT_KEY)
		game->player.rotate_right = 0;
	if (keycode == ESC_KEY)
		game->end = 0;
	return (0);
}

int	key_down(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		game->player.move_up = 1;
	if (keycode == A_KEY)
		game->player.move_left = 1;
	if (keycode == S_KEY)
		game->player.move_down = 1;
	if (keycode == D_KEY)
		game->player.move_right = 1;
	if (keycode == LEFT_KEY)
		game->player.rotate_left = 1;
	if (keycode == RIGHT_KEY)
		game->player.rotate_right = 1;
	if (keycode == ESC_KEY)
		game->end = 1;
	return (0);
}

int	close_triggered(t_game *game)
{
	exit_prog(game);
	exit(0);
	return (0);
}

void	hook_management(t_game *game)
{
	mlx_hook(game->mlx_data.game_win_ptr, DestroyNotify, \
			StructureNotifyMask, close_triggered, game);
	mlx_hook(game->mlx_data.game_win_ptr, KeyPress, \
			KeyPressMask, key_down, game);
	mlx_hook(game->mlx_data.game_win_ptr, KeyRelease, \
	KeyReleaseMask, key_up, game);
	return ;
}
