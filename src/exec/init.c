/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:25:13 by jedusser          #+#    #+#             */
/*   Updated: 2024/12/20 16:22:29 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	init_env(t_mlx_data *mlx_data, t_map *map)
{
	(void)map;
	mlx_data->mlx_ptr = mlx_init();
	if (!mlx_data->mlx_ptr)
		return (ft_puterr("MLX initialisation failed\n"), -1);
	mlx_data->game_win_ptr = mlx_new_window(mlx_data->mlx_ptr, GAME_WIDTH, \
							GAME_HEIGHT , "Cub3d");
	if (!mlx_data->game_win_ptr)
		return (ft_puterr("Window initialisation failed\n"), -1);
	return (0);
}

int	init_textures_one(t_mlx_data *mlx_data, t_tex *tex)
{
	tex->tex1.img_ptr = mlx_xpm_file_to_image(mlx_data->mlx_ptr, tex->no,
			&tex->tex1.width, &tex->tex1.height);
	if (!tex->tex1.img_ptr)
		return (clean_textures(mlx_data, tex), -1);
	tex->tex1.addr = mlx_get_data_addr(tex->tex1.img_ptr, \
										&tex->tex1.bits_per_pixel, \
										&tex->tex1.line_length, \
										&tex->tex1.endian);
	if (!tex->tex1.addr)
		return (clean_textures(mlx_data, tex), -1);
	tex->tex2.img_ptr = mlx_xpm_file_to_image(mlx_data->mlx_ptr, tex->so, \
												&tex->tex2.width, \
												&tex->tex2.height);
	if (!tex->tex2.img_ptr)
		return (clean_textures(mlx_data, tex), -1);
	tex->tex2.addr = mlx_get_data_addr(tex->tex2.img_ptr, \
											&tex->tex2.bits_per_pixel, \
											&tex->tex2.line_length, \
											&tex->tex2.endian);
	if (!tex->tex2.addr)
		return (clean_textures(mlx_data, tex), -1);
	return (0);
}

int	init_textures(t_mlx_data *mlx_data, t_tex *tex)
{
	if (init_textures_one(mlx_data, tex) == -1)
		return (clean_textures(mlx_data, tex), -1);
	tex->tex3.img_ptr = mlx_xpm_file_to_image(mlx_data->mlx_ptr, tex->ea,
			&tex->tex3.width, &tex->tex3.height);
	if (!tex->tex3.img_ptr)
		return (clean_textures(mlx_data, tex), -1);
	tex->tex3.addr = mlx_get_data_addr(tex->tex3.img_ptr, \
													&tex->tex3.bits_per_pixel, \
													&tex->tex3.line_length, \
													&tex->tex3.endian);
	if (!tex->tex3.addr)
		return (clean_textures(mlx_data, tex), -1);
	tex->tex4.img_ptr = mlx_xpm_file_to_image(mlx_data->mlx_ptr, tex->we,
			&tex->tex4.width, &tex->tex4.height);
	if (!tex->tex4.img_ptr)
		return (clean_textures(mlx_data, tex), -1);
	tex->tex4.addr = mlx_get_data_addr(tex->tex4.img_ptr, \
													&tex->tex4.bits_per_pixel, \
													&tex->tex4.line_length, \
													&tex->tex4.endian);
	if (!tex->tex4.addr)
		return (clean_textures(mlx_data, tex), -1);
	return (0);
}

int	initialize_graphics(t_mlx_data *mlx_data, t_map *map, t_img_data *map_img,
		t_img_data *game_img)
{
	if (init_textures(mlx_data, map->tex) == -1)
		return (ft_puterr("Texture initalisation failed\n"), -1);
	map_img->img_ptr = mlx_new_image(mlx_data->mlx_ptr, map->width * TILE_SIZE, \
						map->height * TILE_SIZE);
	if (!map_img->img_ptr)
		return (ft_puterr("Map image initalisation failed\n"), -1);
	map_img->addr = mlx_get_data_addr(map_img->img_ptr, \
												&map_img->bits_per_pixel, \
												&map_img->line_length, \
												&map_img->endian);
	if (!map_img->addr)
		return (ft_puterr("Failed to retrieve data from map image\n"), -1);
	game_img->img_ptr = mlx_new_image(mlx_data->mlx_ptr, GAME_WIDTH,
			GAME_HEIGHT);
	if (!game_img->img_ptr)
		return (ft_puterr("Game image initalisation failed\n"), -1);
	game_img->addr = mlx_get_data_addr(game_img->img_ptr, \
												&game_img->bits_per_pixel, \
												&game_img->line_length, \
												&game_img->endian);
	if (!game_img->addr)
		return (ft_puterr("Failed to retrieve data from game image\n"), -1);
	return (0);
}

void	init_game(t_game *game)
{
	//def_playr_angle(&game->player);
	if (init_env(&game->mlx_data, game->map) == -1)
		exit_prog(game);
	if (initialize_graphics(&game->mlx_data, game->map, &game->map_img,
			&game->game_img) == -1)
		exit_prog(game);
}
