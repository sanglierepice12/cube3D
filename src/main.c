/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 05:22:20 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/13 09:38:12 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


void clean_up(t_game *game)
{
    if (game->map)
    {
        free_tab(game->map->map);
        free(game->map);
    }
    if (game->map_img && game->mlx_data)
    {
        mlx_destroy_image(game->mlx_data->mlx_ptr, game->map_img->img_ptr);
        mlx_destroy_image(game->mlx_data->mlx_ptr, game->game_img->img_ptr);

    }
    if (game->mlx_data)
    {
        mlx_destroy_window(game->mlx_data->mlx_ptr, game->mlx_data->map_win_ptr);
        mlx_destroy_window(game->mlx_data->mlx_ptr, game->mlx_data->game_win_ptr);
        free(game->mlx_data);
    }
    if (game->player)
        free(game->player);
    if (game->map_img)
    {
        free(game->map_img);
        free(game->game_img);

    }
}

void	print_lst(t_list **list)
{
	t_list	*temp;
	temp = *list;
	while (temp->next)
	{
		printf("%s$\n", temp->value);
		temp = temp->next;
	}
	printf("%s", temp->value);
}

int main(int arc, char **argv)
{
	t_game	game;

	if (arc < 2)
		return (printf("Please insert a map..."));
	get_map(&game, argv[1]);
	print_lst(&game.list);
	free_list(game.list);
	printf("\nend\n");
	/*if (init_game(&game) == -1)
	{
		clean_up(&game);
		return (1);
	}
	draw_and_display_map(&game);
	mlx_loop(game.mlx_data->mlx_ptr);
	clean_up(&game);*/
	return (0);
}



