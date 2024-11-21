/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 05:22:20 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/21 15:41:13 by jedusser         ###   ########.fr       */
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
    if (game->player)
        free(game->player);
    if (game->raycaster)
        free(game->raycaster);
    if (game->projection)
        free(game->projection);
    if (game->map_img)
    {
        free(game->map_img);
        free(game->game_img);
    }
    if (game->mlx_data)
    {
        //mlx_destroy_window(game->mlx_data->mlx_ptr, game->mlx_data->map_win_ptr);
        mlx_destroy_window(game->mlx_data->mlx_ptr, game->mlx_data->game_win_ptr);
        mlx_destroy_display(game->mlx_data->mlx_ptr);
        free(game->mlx_data->mlx_ptr);
        free(game->mlx_data);
    }
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

void print_struct(t_game *game)
{
    printf("UP %d\n", game->player->move_up);
    printf("DOWN %d\n", game->player->move_down);
    printf("LEFT %d\n", game->player->move_left);
    printf("RIGHT %d\n", game->player->move_right);
    printf("ROT LEFT %d\n", game->player->rotate_left);
    printf("ROT RIGHT %d\n", game->player->rotate_right);
}

int main(void)
{
    t_game  game;

    // ft_memset(&game, 0, sizeof(t_game));
    if (init_game(&game) == -1)
    {
        clean_up(&game);
        return (1);
    }
    hook_management(&game);
    // mlx_key_hook(game.mlx_data->game_win_ptr, handle_keypress, &game);
    mlx_loop_hook(game.mlx_data->mlx_ptr, &draw_and_display_map, &game);
    draw_and_display_map(&game);
    mlx_loop(game.mlx_data->mlx_ptr);
    clean_up(&game);
    return (0);
}



