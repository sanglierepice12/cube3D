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

/*****GET_MAP_TEXTURE_RGB*****/
void	first_line(int fd, t_list **list, t_game *game);
void	fill_map_to_list(t_game *game, t_list **list, int fd);
void	get_rgb(char *line, t_game *game);
void	get_textures(char *line, t_texture *texture, t_game *game);
void	fill_tex(char *line, t_texture *texture, e_txt type);
void	fill_rgb(char *line, t_game *game, e_rgb type);
void	fill_list_to_map(t_game *game, t_list **list);
void	fill_playerpos(char *line, t_game *game);

/****MAP_VALIDITY****/
void	eye_tomap(char **map, t_game *game);

#endif