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

void	fill_playerpos(char *line, t_game *game, size_t len)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			game->player.player_pos_x = (int)i;
			game->player.player_pos_y = (int)len;
			game->player.direction = line[i];
		}
		i++;
	}
}

void	eye_tomap(char **map, t_game *game)
{
	(void)game;
	(void)map;
}