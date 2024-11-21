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

void	get_map(t_game *game, char *file);
bool	is_line_full_spaces(char *line);
bool	is_line_ok(t_map *map, char *line);
int		parse_ws(char *line);
bool	fill_in_list(char *temp);

/*******CHECK_TEXTURES******/
bool	check_texture(char	*line);
bool	check_rgb(char *line);

/*******CHECK_MAP******/
void	fill_list_to_map(t_game *game);


#endif