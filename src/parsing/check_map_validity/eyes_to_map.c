/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eyes_to_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:05:21 by gsuter            #+#    #+#             */
/*   Updated: 2024/11/27 18:05:21 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

bool	ft_strchr(const char *s, const char c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (true);
		i++;
	}
	return (false);
}

void	fill_playerpos(char *line, t_game *game, size_t len)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr("NSEW", line[i]))
		{
			game->player.player_pos_x = (int)i;
			game->player.player_pos_y = (int)len;
			game->player.direction = line[i];
			game->map->count++;
			if (game->map->count > 7)
			{
				printf("Error, double player position\n");
				free(line);
				free_list(game->list);
				exit_prog(game);
			}
		}
		i++;
	}
}
