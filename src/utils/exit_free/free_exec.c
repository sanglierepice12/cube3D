/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:20:49 by gsuter            #+#    #+#             */
/*   Updated: 2024/12/05 15:28:43 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void clean_textures(t_mlx_data *mlx_data, t_texture *textures)
{
		mlx_destroy_image(mlx_data->mlx_ptr, textures->texture1.img_ptr);
		mlx_destroy_image(mlx_data->mlx_ptr, textures->texture2.img_ptr);
		mlx_destroy_image(mlx_data->mlx_ptr, textures->texture3.img_ptr);
		mlx_destroy_image(mlx_data->mlx_ptr, textures->texture4.img_ptr);
}

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