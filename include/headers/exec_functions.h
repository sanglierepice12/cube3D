/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_functions.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglier <sanglier@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:18:19 by sanglier          #+#    #+#             */
/*   Updated: 2024/11/12 16:44:41 by sanglier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_FUNCTIONS_H
# define EXEC_FUNCTIONS_H

/*################ FUNCTIONS #####################*/

/*=================draw_tools.c===================*/

void		my_mlx_pixel_put(t_img_data *data, int x, int y, int color);


/*===================hooks.c======================*/
void		hook_management(t_game *game);
int			handle_keypress(t_game *game);


/*=====================init.c=====================*/

int			init_env(t_mlx_data *mlx_data, t_map *map);
int			initialize_map(t_map *map);
int			initialize_graphics(t_mlx_data *mlx_data, t_map *map,
							   t_img_data *map_img, t_img_data *game_img);
void		find_play_pos(t_map *map, t_player *player);
void		init_game(t_game *game);

/*==================mini_map.c====================*/
void		ray_caster(t_player *player, t_raycaster *raycaster,\
				t_proj *projection);
void		all_draws(t_game *game);
void		draw_mini_map(t_game *game);
int			draw_and_display_map(t_game *game);
void		render_3d_map(t_game *game, t_player *player, t_raycaster *raycaster,
					  t_proj *projection);
int			check_bounds(t_map *map, t_raycaster *raycaster);
/*====================main.c======================*/
int			clean_up(t_game *game);


#endif