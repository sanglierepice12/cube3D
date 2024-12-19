/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:48:03 by gsuter            #+#    #+#             */
/*   Updated: 2024/12/19 12:50:39 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	draw_follow(t_game *game)
{
	if (key_active(game))
	{
		handle_keypress(game);
		if (game->end)
			return ;
		all_draws(game);
		mlx_put_image_to_window(game->mlx_data.mlx_ptr, \
			game->mlx_data.game_win_ptr, game->map_img.img_ptr, \
				GAME_WIDTH / 4, GAME_HEIGHT);
		mlx_put_image_to_window(game->mlx_data.mlx_ptr, \
			game->mlx_data.game_win_ptr, game->game_img.img_ptr, 0, 0);
	}
}

int	draw_and_display_map(t_game *game)
{
	static int	i;

	if (!i)
	{
		all_draws(game);
		if (game->map_img.img_ptr)
			mlx_put_image_to_window(game->mlx_data.mlx_ptr, \
				game->mlx_data.game_win_ptr, \
			game->map_img.img_ptr, GAME_WIDTH / 4, GAME_HEIGHT);
		if (game->game_img.img_ptr)
			mlx_put_image_to_window(game->mlx_data.mlx_ptr, \
				game->mlx_data.game_win_ptr, game->game_img.img_ptr, 0, 0);
		i = 1;
	}
	if (key_active(game))
		draw_follow(game);
	return (0);
}

void	all_draws(t_game *game)
{
	draw_mini_map(game);
	fill_tile_with_player(&game->player, &game->map_img, \
		(int)game->player.pos_x, (int)game->player.pos_y);
	draw_map_rays(game, &game->player, &game->ray);
	render_3d_map(game, &game->player, &game->ray, &game->proj);
}
