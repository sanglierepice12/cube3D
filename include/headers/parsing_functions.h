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

/*******CHECK_TEXTURES******/
bool	check_texture(char	*line);
bool	check_rgb(char *line);

/****IS_LINE_SOMETHING***/
bool	is_line_full_spaces(char *line);
bool	is_line_ok(char	*temp);
bool	is_line_m_ok(char *line);
void	wall_is_good(t_game *game, char *line, bool flag, char *prev);
void	is_matter_ok(t_game *game, char *line);
void	calculate_matter(char *line, t_game *game);

/*****GET_MAP_TEXTURE_RGB*****/
void	first_line(int fd, t_list **list, t_game *game);
void	fill_map_to_list(t_game *game, t_list **list, int fd);
void	get_rgb(char *line, t_game *game);
void	get_textures(char *line, t_tex *texture, t_game *game);
void	fill_tex(char *line, t_tex *texture, t_txt type);
void	fill_rgb(char *line, t_game *game, t_ergb type);
void	fill_list_to_map(t_game *game, t_list **list);
void	fill_playerpos(char *line, t_game *game, size_t len);
int		rgb_to_hex(int r, int g, int b);
void	get_len_line(t_game *game);
char	*copy_map_line(char *str, ssize_t width);

#endif