/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:20:49 by gsuter            #+#    #+#             */
/*   Updated: 2024/12/20 15:49:13 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void	clean_textures(t_mlx_data *mlx_data, t_tex *tex)
{
	if (tex->tex1.img_ptr)
	{
		mlx_destroy_image(mlx_data->mlx_ptr, tex->tex1.img_ptr);
		tex->tex1.img_ptr = NULL;
	}
	if (tex->tex2.img_ptr)
	{
		mlx_destroy_image(mlx_data->mlx_ptr, tex->tex2.img_ptr);
		tex->tex2.img_ptr = NULL;
	}
	if (tex->tex3.img_ptr)
	{
		mlx_destroy_image(mlx_data->mlx_ptr, tex->tex3.img_ptr);
		tex->tex3.img_ptr = NULL;
	}
	if (tex->tex4.img_ptr)
	{
		mlx_destroy_image(mlx_data->mlx_ptr, tex->tex4.img_ptr);
		tex->tex4.img_ptr = NULL;
	}
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
		if (game->mlx_data.game_win_ptr)
		{
			mlx_destroy_window(game->mlx_data.mlx_ptr, \
				game->mlx_data.game_win_ptr);
			game->mlx_data.game_win_ptr = NULL;
		}
		mlx_destroy_display(game->mlx_data.mlx_ptr);
		free(game->mlx_data.mlx_ptr);
		game->mlx_data.mlx_ptr = NULL;
	}
	return (0);
}
