/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:57:20 by gsuter            #+#    #+#             */
/*   Updated: 2024/11/13 12:57:20 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_FUNCTIONS_H
# define PARSING_FUNCTIONS_H

/****INIT****/
void	init_struct(t_game **game);
void	init_parse(t_game *game, char *file);

/****UTILS****/
char	*rm_space_rgb(char *line);

/*******CHECK_TEXTURES******/
bool	check_texture(char	*temp, char *line, t_game *game);
bool	check_rgb(char *temp, char *line, t_game *game);

/****IS_LINE_SOMETHING***/
bool	is_line_full_spaces(char *line);
bool	is_line_ok(char	*temp);
bool	is_line_m_ok(char *line);
void	is_game_line_ok(t_game *game, char *line, char *prev);
void	is_matter_ok(t_game *game, char *line);
void	calculate_matter(char *line, t_game *game);
bool	is_full_of_one(char *line);
bool	is_closed(const char *prev, const char *line, size_t len);
void	is_fst_line_ok(char *line, size_t i, t_game *game);
void	is_map_ok(char *line, t_game *game, size_t *i);
bool	is_really_one(const char *line);
void	wallend(char *line, t_list *temp, t_game *game, int *count);
bool	have_double_ext(t_tex *tex);

/*****GET_MAP_TEXTURE_RGB*****/
void	first_line(int fd, t_list **list, t_game *game);
void	fill_map_to_list(t_game *game, t_list **list, int fd);
void	get_rgb(char *line, t_game *game);
void	get_textures(char *line, t_tex *texture, t_game *game);
void	fill_tex(char *line, t_tex *texture, t_txt type);
void	fill_rgb(char *temp, t_game *game, t_ergb type, char *line);
void	fill_list_to_map(t_game *game, t_list **list);
void	fill_playerpos(char *line, t_game *game, size_t len);
void	fill_rgb_struct(t_game *game, char **temp, t_ergb type);
int		rgb_to_hex(int r, int g, int b);
void	get_len_line(t_game *game);
char	*copy_map_line(char *str, ssize_t width);
void	check_first_line(t_game *game, t_list *list);

#endif