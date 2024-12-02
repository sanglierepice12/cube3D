/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 05:22:20 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/27 15:39:29 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


/*
    * initialisation de la structure
    * check les arguments du prog
    * faire tout le parsing de la map + recuperer les bonnes info et set la struct
    *
    * initialiser la fenetre
    * initialiser les hooks (tel touche fait tel chose)
    * initialiser la boucle du jeu
*/

int main(int arc, char **argv)
{
	t_game		*game;

	if (arc < 2)
		return (printf("Please insert a map..."));
	init_struct(&game);
	init_parse(game, argv[1]);

	printf("pos x = %d\n", game->player.player_pos_x);
	printf("pos y = %d\n", game->player.player_pos_y);
	printf("direction = %c\n", game->player.direction);
/*	int i = 0;
	while (game->map->map[i])
		printf("%s\n", game->map->map[i++]);
	printf("%s\n", game->map->texture->no);
	printf("%s\n", game->map->texture->so);
	printf("%s\n", game->map->texture->ea);
	printf("%s\n", game->map->texture->we);*/
	/*printf("floor r = %d \n", game->map->floor->r);
	printf("floor g = %d \n", game->map->floor->g);
	printf("floor b = %d \n", game->map->floor->b);
	printf("ceiling r = %d \n", game->map->ceiling->r);
	printf("ceiling g = %d \n", game->map->ceiling->g);
	printf("ceiling b = %d \n", game->map->ceiling->b);*/


	/*init_game(game);
	hook_management(game);
	mlx_loop_hook(game->mlx_data.mlx_ptr, &draw_and_display_map, game);
	draw_and_display_map(game);
	mlx_loop(game->mlx_data.mlx_ptr);*/
	exit_prog(game);
	printf("\nend\n");
	return (0);
}
