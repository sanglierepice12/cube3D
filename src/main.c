/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 05:22:20 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/26 10:43:57 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


int clean_up(t_game *game)
{
    if (&game->map)
        free_tab(game->map.map);
    if (&game->map_img && &game->mlx_data)
        mlx_destroy_image(game->mlx_data.mlx_ptr, game->map_img.img_ptr);
    if (&game->game_img && &game->mlx_data)
        mlx_destroy_image(game->mlx_data.mlx_ptr, game->game_img.img_ptr);
    if (&game->mlx_data)
    {
        mlx_destroy_window(game->mlx_data.mlx_ptr, game->mlx_data.game_win_ptr);
        mlx_destroy_display(game->mlx_data.mlx_ptr);
        free(game->mlx_data.mlx_ptr);
    }
    printf("Clean-up completed.\n");
    return (0);
}


/*
    * initialisation de la structure
    * check les arguments du prog
    * faire tout le parsing de la map + recuperer les bonnes info et set la struct
    * 
    * initialiser la fenetre
    * initialiser les hooks (tel touche fait tel chose)
    * initialiser la boucle du jeu
*/



int main(void)
{
    t_game  game;

    ft_memset(&game, 0, sizeof(t_game));
    if (init_game(&game) == -1)
    {
        clean_up(&game);
        return (1);
    }
    hook_management(&game);
    mlx_loop_hook(game.mlx_data.mlx_ptr, &draw_and_display_map, &game);
    draw_and_display_map(&game);
    mlx_loop(game.mlx_data.mlx_ptr);
    clean_up(&game);
    return (0);
}



