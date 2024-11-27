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

void	fill_playerpos(char *line, t_game *game)
{
	(void)line;
	(void)game;
/*	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'N')
			game->player.player_pos_x =
	}*/
}

void	eye_tomap(char **map, t_game *game)
{
	printf("printf : %s", map[0]);
	exit_prog(game);
	fill_playerpos(map[0], game);
}