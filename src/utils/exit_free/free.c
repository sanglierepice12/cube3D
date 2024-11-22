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

	if (!tab)
		return ;
	y = 0;
	while (tab[y])
	{
		free(tab[y]);
		y++;
	}
	free(tab);
	tab = NULL;
}

void	free_rgb(t_rgb *rgb)
{
	if (!rgb)
		return ;
	ft_bzero(rgb, sizeof(*rgb));
	free(rgb);
}

void	free_texture(t_texture *texture)
{
	if (!texture)
		return ;
	free(texture->ea);
	free(texture->no);
	free(texture->so);
	free(texture->we);
	free(texture);
}

void	free_s_map(t_map *map)
{
	if (!map)
		return ;
	free_tab(map->map);
	free_texture(map->texture);
	free_rgb(map->ceiling);
	free_rgb(map->floor);
	free(map);
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
