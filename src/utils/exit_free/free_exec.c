/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:20:49 by gsuter            #+#    #+#             */
/*   Updated: 2024/11/27 15:24:40 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"



int	clean_up(t_game *game)
{
	if (game->map_img.img_ptr)
	{
		mlx_destroy_image(game->mlx_data.mlx_ptr, game->map_img.img_ptr);
		game->map_img.img_ptr = NULL;
	}
	if (game->game_img.img_ptr)
	{
		mlx_destroy_image(game->mlx_data.mlx_ptr, game->game_img.img_ptr);
		game->game_img.img_ptr = NULL;
	}
	if (game->mlx_data.mlx_ptr)
	{
		mlx_destroy_window(game->mlx_data.mlx_ptr, game->mlx_data.game_win_ptr);
		mlx_destroy_display(game->mlx_data.mlx_ptr);
		free(game->mlx_data.mlx_ptr);
		game->mlx_data.mlx_ptr = NULL;
	}
	printf("Clean-up completed.\n");
	return (0);
}