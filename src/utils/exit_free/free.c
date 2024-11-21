/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:14:58 by gsuter            #+#    #+#             */
/*   Updated: 2024/11/13 14:14:58 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void	free_tab(char **tab)
{
	int	y;

	y = 0;
	while (tab[y])
	{
		free(tab[y]);
		y++;
	}
	free(tab);
}

void	free_texture(t_texture *texture)
{
	if (texture->ea)
		free(texture->ea);
	if (texture->no)
		free(texture->no);
	if (texture->so)
		free(texture->so);
	if (texture->we)
		free(texture->we);
}

void	free_s_map(t_map *map)
{
	if (map->map)
		free_tab(map->map);
}

void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}
