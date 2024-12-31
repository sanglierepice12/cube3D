/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_the_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglier <sanglier@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:46:55 by sanglier          #+#    #+#             */
/*   Updated: 2024/12/31 13:46:55 by sanglier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void	is_fst_line_ok(char *line, size_t i, t_game *game)
{
	while (line[i--])
	{
		if (line[i] == '#')
			continue ;
		if (line[i] != '1')
			force_exit(line, game);
	}
}

void	is_game_line_ok(t_game *game, char *line, char *prev)
{
	size_t	len;
	char	*temp;

	len = ft_strlen(line);
	if (!ft_comp_str(line, "\n") || !is_line_full_spaces(line))
	{
		temp = copy_map_line(prev, game->map->width);
		if (!temp)
			force_exit(line, game);
		while (len--, line[len])
		{
			if (line[len] == '#')
				continue ;
			if (line[len] != '1')
				break ;
			if (temp[len] == '#' && !is_closed(temp, line, len + 1))
				break ;
			if (temp[len] == '0' && temp[len + 1] != '1')
				break ;
			return (free(temp));
		}
		free(temp);
	}
	force_exit(line, game);
}