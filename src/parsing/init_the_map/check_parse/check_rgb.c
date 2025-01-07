/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglier <sanglier@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:56:00 by sanglier          #+#    #+#             */
/*   Updated: 2024/12/19 12:56:00 by sanglier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3D.h"

void	wallend(char *line, t_list *temp, t_game *game, int *count)
{
	if (is_full_of_one(line))
	{
		if (temp->next && is_full_of(temp->next->value, '\n'))
		{
			(*count)++;
			game->map->height = (int)ft_str_double_len(game->map->map);
		}
	}
	if (is_full_of(line, '#') && *count == 0)
		force_exit(line, game);
}

char	*rm_space_rgb(char *line)
{
	char	*dup;
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (line[i++])
	{
		if (is_ws(line[i]))
			continue ;
		k++;
	}
	dup = ft_calloc(sizeof(char), k + 1);
	if (!dup)
		return (NULL);
	i = 0;
	k = 0;
	while (line[i++])
	{
		if (is_ws(line[i]))
			continue ;
		dup[k++] = line[i];
	}
	return (dup);
}
