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

void	fill_rgb(char *line, t_game *game, e_rgb type)
{
	char	**temp;

	temp = ft_split(line, ',');
	if (!temp)
		return (printf("Error malloc\n"), free(line), exit_prog(game));
	if (!temp[2])
		return (printf("Error nothing in rgb\n"), free(line), exit_prog(game));
	if (type == CEI)
	{
		game->map->ceiling->r = ft_atoi(temp[0]);
		game->map->ceiling->g = ft_atoi(temp[1]);
		game->map->ceiling->b = ft_atoi(temp[2]);
	}
	if (type == FLO)
	{
		game->map->floor->r = ft_atoi(temp[0]);
		game->map->floor->g = ft_atoi(temp[1]);
		game->map->floor->b = ft_atoi(temp[2]);
	}
	free(line);
	free_tab(temp);
}

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
	char	*line;
	size_t	i;

	game->map->map = heap_map(get_list_len(*list));
	game->map->height = (int)get_list_len(*list);
	temp = *list;
	if (!temp)
		return (printf("Error malloc\n"), exit_prog(game));
	i = 0;
	game->map->width = 0;
	while (temp)
	{
		line = rm_bs_wp(temp->value);
		if (!temp->next || i == 0)
			wall_is_good(game, line, 0);
		else
			wall_is_good(game, line, 1);
		game->map->map[i++] = ft_dup(line);
		fill_playerpos(line, game, i);
		if (game->map->width < (int) ft_strlen(line))
			game->map->width = (int)ft_strlen(line);
		temp = temp->next;
		free(line);
	}
}

void	fill_map_to_list(t_game *game, t_list **list, int fd)
{
	char	*line;

	first_line(fd, list, game);
	line = NULL;
	while (777)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_comp_str(line, "\n") || is_line_full_spaces(line))
		{
			free(line);
			continue ;
		}
		if (!is_line_m_ok(line))
		{
			free_list(game->list);
			exit_prog(game);
		}
		ft_lst_add_back(list, ft_new_node(line));
		free(line);
	}
}