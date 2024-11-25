/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_managment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:14:18 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/25 11:17:06 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#include "../minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx_int.h"

int close_win(int keycode, t_game *game)
{
    (void)keycode;
    mlx_loop_end(game->mlx_data.mlx_ptr);
    return (0);
}


int key_up(int keycode, t_game *game)
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

int key_down(int keycode, t_game *game)
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

void    hook_management(t_game *game)
{
    mlx_hook(game->mlx_data.game_win_ptr, DestroyNotify, StructureNotifyMask, \
                                                        clean_up, game);
    mlx_hook(game->mlx_data.game_win_ptr, KeyPress, KeyPressMask, key_down, game);
    mlx_hook(game->mlx_data.game_win_ptr, KeyRelease, KeyReleaseMask, key_up, game);
    return ;
}