/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:56:00 by sanglier          #+#    #+#             */
/*   Updated: 2025/01/08 11:45:28 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3D.h"

void	check_first_line(t_game *game, t_list *list)
{
	game->map->map = heap_map(get_list_len(list));
	if (!game->map->map)
		return (ft_puterr("Malloc\n"), free_list(list), exit_prog(game));
}

bool	is_really_one(const char *line)
{
	size_t	i;

	i = 0;
	if (line[i] != '1')
		return (0);
	while (line[i++])
	{
		if (line[i] == '#' || !line[i])
			break ;
		if (line[i] != '1')
			return (false);
	}
	return (true);
}

void	wallend(char *line, t_list *temp, t_game *game, int *count)
{
	if (is_really_one(line))
	{
		if (!temp->next || (temp->next && is_full_of(temp->next->value, '\n')))
		{
			(*count)++;
			game->map->height = (int)ft_str_double_len(game->map->map + 1);
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
