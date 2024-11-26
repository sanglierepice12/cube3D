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

void	init_struct(t_game **game);
void	get_map(t_game *game, char *file);
bool	is_line_full_spaces(char *line);
int		parse_ws(char *line);
void	fill_tex(char *line, t_texture *texture, e_txt type);
void	fill_rgb(char *line, t_map *map, e_rgb type);
void	fill_list_to_map(t_game *game, t_list **list);
bool	is_line_ok(char	*temp);
bool	is_line_m_ok(char *line);

/*******CHECK_TEXTURES******/
bool	check_texture(char	*line);
bool	check_rgb(char *line);

/*******CHECK_MAP******/
void	fill_list_to_map(t_game *game, t_list **list);


#endif