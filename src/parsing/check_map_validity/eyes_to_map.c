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

int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	def_playr_angle(t_player *player)
{
	player->px_pos_x = (player->pos_x * TILE_SIZE) + (TILE_SIZE * 0.5);
	player->px_pos_y = (player->pos_y * TILE_SIZE) + (TILE_SIZE * 0.5);
	if (player->direction == 'N')
		player->angle = (3 * M_PI) * 0.5;
	else if (player->direction == 'S')
		player->angle = M_PI / 2;
	else if (player->direction == 'W')
		player->angle = M_PI;
	else if (player->direction == 'E')
		player->angle = 0;
}

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
			game->player.pos_x = (int)i;
			game->player.pos_y = (int)len;
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
	def_playr_angle(&game->player);
}
