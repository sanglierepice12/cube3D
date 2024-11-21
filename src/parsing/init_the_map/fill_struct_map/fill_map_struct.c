/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_to_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglier <sanglier@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:52:22 by sanglier          #+#    #+#             */
/*   Updated: 2024/11/21 14:52:22 by sanglier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3D.h"

static void	print_lst(t_list **list)
{
	t_list	*temp;
	temp = *list;
	while (temp->next)
	{
		printf("%s$\n", temp->value);
		temp = temp->next;
	}
	printf("%s", temp->value);
}

char	**heap_map(size_t len)
{
	char	**map;
	map = ft_calloc(sizeof(char *), len + 1);
	if (!map)
		return (NULL);
	return (map);
}

void	fill_file(t_map *map, t_list **list)
{
	t_list	*temp;
	size_t	i;

	map->map = heap_map(get_list_len(*list));
	temp = *list;
	if (!temp)
		return ;
	i = 0;
	while (temp)
	{
		map->map[i] = ft_dup(temp->value);
		temp = temp->next;
	}
}

void	fill_list_to_map(t_game *game)
{
	fill_file(game->map, &game->list);
//	print_lst(&game->list);
	//fill_file(game->map, &game->list);
}