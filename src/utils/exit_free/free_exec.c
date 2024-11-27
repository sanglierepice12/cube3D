/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:20:49 by gsuter            #+#    #+#             */
/*   Updated: 2024/11/27 14:20:49 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

int	clean_up(t_game *game)
{
	if (game->map_img.img_ptr)
	{
		mlx_destroy_image(game->mlx_data.mlx_ptr, game->map_img.img_ptr);
		game->map_img.img_ptr = NULL;  // Ajout d'une sécurité pour éviter les doubles libérations
	}

	if (game->game_img.img_ptr)
	{
		mlx_destroy_image(game->mlx_data.mlx_ptr, game->game_img.img_ptr);
		game->game_img.img_ptr = NULL;  // Ajout d'une sécurité pour éviter les doubles libérations
	}
	/*if (&(game->map_img) && &(game->mlx_data))
		mlx_destroy_image(game->mlx_data.mlx_ptr, game->map_img.img_ptr);
	if (&(game->game_img) && &(game->mlx_data))
		mlx_destroy_image(game->mlx_data.mlx_ptr, game->game_img.img_ptr);*/
	if (game->mlx_data.mlx_ptr)
	{
		mlx_destroy_window(game->mlx_data.mlx_ptr, game->mlx_data.game_win_ptr);
		mlx_destroy_display(game->mlx_data.mlx_ptr);
		free(game->mlx_data.mlx_ptr);
		game->mlx_data.mlx_ptr = NULL;  // Sécurisation
	}
		/*if (&(game->mlx_data))
		{
			mlx_destroy_window(game->mlx_data.mlx_ptr, game->mlx_data.game_win_ptr);
			mlx_destroy_display(game->mlx_data.mlx_ptr);
			free(game->mlx_data.mlx_ptr);
		}*/
	printf("Clean-up completed.\n");
	return (0);
}