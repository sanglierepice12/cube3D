/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 05:22:20 by jedusser          #+#    #+#             */
/*   Updated: 2024/12/12 12:55:33 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#include <stdio.h>


/*
    * initialisation de la structure
    * check les arguments du prog
    * faire tout le parsing de la map + recuperer les bonnes info et set la struct
    *
    * initialiser la fenetre
    * initialiser les hooks (tel touche fait tel chose)
    * initialiser la boucle du jeu
*/


int	draw_and_display_map(t_game *game)
{
	static int	i;

	if (!i)
	{
		all_draws(game);
		if (game->map_img.img_ptr)
			mlx_put_image_to_window(game->mlx_data.mlx_ptr,
					game->mlx_data.game_win_ptr, game->map_img.img_ptr,
					GAME_WIDTH / 4, GAME_HEIGHT);
		if (game->game_img.img_ptr)
			mlx_put_image_to_window(game->mlx_data.mlx_ptr,
					game->mlx_data.game_win_ptr, game->game_img.img_ptr, 0, 0);
		i = 1;
	}
	if (key_active(game))
	{
		
		handle_keypress(game);
		if (game->end)
			return (0);
		all_draws(game);
		mlx_put_image_to_window(game->mlx_data.mlx_ptr,
				game->mlx_data.game_win_ptr, game->map_img.img_ptr, GAME_WIDTH
				/ 4, GAME_HEIGHT);
		mlx_put_image_to_window(game->mlx_data.mlx_ptr,
				game->mlx_data.game_win_ptr, game->game_img.img_ptr, 0, 0);
	}
	return (0);
}
void	all_draws(t_game *game)
{
	draw_mini_map(game);
	fill_tile_with_player(&game->player, &game->map_img,
			game->player.pos_x, game->player.pos_y, BLACK, GREEN);
	draw_map_rays(game, &game->player, &game->ray);
	render_3d_map(game, &game->player, &game->ray, &game->proj);
}

int rgb_to_hex(int r, int g, int b)
{
    return (r << 16) | (g << 8) | b;
}


int main(int arc, char **argv)
{
	t_game		*game;

	if (arc < 2)
		return (printf("Please insert a map..."));
	init_struct(&game);
	init_parse(game, argv[1]);
	game->map->ceiling_color = rgb_to_hex(game->map->ceiling->r, game->map->ceiling->g, game->map->ceiling->b);
	game->map->floor_color = rgb_to_hex(game->map->floor->r, game->map->floor->g, game->map->floor->b);


	init_game(game);
	
	hook_management(game);
	mlx_loop_hook(game->mlx_data.mlx_ptr, &draw_and_display_map, game);
	draw_and_display_map(game);
	mlx_loop(game->mlx_data.mlx_ptr);
	exit_prog(game);
	return (0);
}
