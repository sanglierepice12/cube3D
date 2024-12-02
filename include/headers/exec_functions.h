/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:18:19 by sanglier          #+#    #+#             */
/*   Updated: 2024/12/02 10:08:36 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_FUNCTIONS_H
# define EXEC_FUNCTIONS_H

/*################ FUNCTIONS #####################*/

/*===================hooks.c======================*/

void	handle_rotation(t_player *player);
void	update_position(t_game *game, float *new_x, float *new_y);
void	handle_move(t_game *game);
int		handle_keypress(t_game *game);

/*==============hooks_managment.c=================*/

void	hook_management(t_game *game);
int		close_win(int keycode, t_game *game);
int		key_up(int keycode, t_game *game);
int		key_down(int keycode, t_game *game);

/*==================draws_utils.c====================*/

void	clear_screen(t_img_data *img, int ceiling_color, int floor_color);
void	def_wall_color(t_raycaster *raycaster, t_proj *projection);
void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color);

/*==================exec_utils.c====================*/

bool	key_active(t_game *game);
void	def_hit_side(t_raycaster *raycaster, float ray_dir_x, float ray_dir_y);
bool	wall_hit(t_map *map, t_raycaster *raycaster);

/*=====================init.c=====================*/

int		init_env(t_mlx_data *mlx_data, t_map *map);
int		initialize_graphics(t_mlx_data *mlx_data, t_map *map,
			t_img_data *map_img, t_img_data *game_img);
void	find_play_pos(t_map *map, t_player *player);
void	init_game(t_game *game);

/*==================mini_map.c====================*/

void	draw_player(t_img_data *img, int start_x, int start_y, int color);
int		draw_tile(t_img_data *img, int start_x, int start_y, int color);
void	fill_tile_with_player(t_player *player, t_img_data *img, int tile_x,
			int tile_y, int floor_color, int player_color);
void	draw_map_rays(t_game *game, t_player *player, t_raycaster *raycaster);
void	draw_mini_map(t_game *game);

/*==================render_3d_map.c====================*/

void	cast_ray(t_game *game, t_raycaster *raycaster, t_player *player,
			t_proj *projection);
void	draw_3d_column(t_game *game);
void	render_3d_map(t_game *game, t_player *player, t_raycaster *raycaster,
			t_proj *projection);

/*====================main.c======================*/

void	all_draws(t_game *game);
int		draw_and_display_map(t_game *game);

int		clean_up(t_game *game);

#endif