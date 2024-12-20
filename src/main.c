/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 05:22:20 by jedusser          #+#    #+#             */
/*   Updated: 2024/12/20 15:46:17 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	init(t_game **game, char **argv)
{
	init_struct(game);
	init_parse(*game, argv[1]);
	init_game(*game);
}

static void	launch_game(t_game *game)
{
	hook_management(game);
	mlx_loop_hook(game->mlx_data.mlx_ptr, &draw_and_display_map, game);
	draw_and_display_map(game);
	mlx_loop(game->mlx_data.mlx_ptr);
}

int	main(int arc, char **argv)
{
	t_game		*game;

	if (arc < 2)
		return (ft_puterr("Please insert a map..."));
	init(&game, argv);
	launch_game(game);
	exit_prog(game);
	return (0);
}
