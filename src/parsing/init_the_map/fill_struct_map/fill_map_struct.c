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

void	fill_tex(char *line, t_texture *texture, e_txt type)
{
	if (type == NO)
	{
		texture->no = ft_dup(line);
		if (texture->no == NULL)
			return (printf("texture no is null\n"), free(line));
	}
	if (type == SO)
	{
		texture->so = ft_dup(line);
		if (texture->so == NULL)
			return (printf("texture no is null\n"), free(line));
	}
	if (type == WE)
	{
		texture->we = ft_dup(line);
		if (texture->we == NULL)
			return (printf("texture no is null\n"), free(line));
	}
	if (type == EA)
	{
		texture->ea = ft_dup(line);
		if (texture->ea == NULL)
			return (printf("texture no is null\n"), free(line));
	}
	free(line);
}

void	fill_rgb(char *line, t_map *map, e_rgb type)
{
	char	**temp;

	temp = ft_split(line, ',');
	if (!temp)
		return ;
	printf("%s", temp[0]);
	if (type == CEI)
	{
		map->ceiling->r = ft_atoi(temp[0]);
		map->ceiling->g = ft_atoi(temp[1]);
		map->ceiling->b = ft_atoi(temp[2]);
	}
	if (type == FLO)
	{
		map->floor->r = ft_atoi(temp[0]);
		map->floor->g = ft_atoi(temp[1]);
		map->floor->b = ft_atoi(temp[2]);
	}
	free(line);
	free_tab(temp);
}

char	**heap_map(size_t len)
{
	char	**map;
	map = ft_calloc(sizeof(char *), len + 1);
	if (!map)
		return (NULL);
	return (map);
}

void	fill_list_to_map(t_game *game, t_list **list)
{
	t_list	*temp;
	char	*dest;
	size_t	i;

	game->map->map = heap_map(get_list_len(*list));
	game->map->map_height = (int)get_list_len(*list);
	temp = *list;
	if (!temp)
		return (printf("Error malloc\n"), exit_prog(game));
	i = 0;
	game->map->map_width = 0;
	while (temp)
	{
		dest = rm_bs_wp(temp->value);
		game->map->map[i++] = ft_dup(dest);
		if (game->map->map_width < (int) ft_strlen(dest))
			game->map->map_width = (int)ft_strlen(dest);
		temp = temp->next;
		free(dest);
	}
}
