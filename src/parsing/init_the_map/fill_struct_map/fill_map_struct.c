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

void	fill_rgb(char *line, t_game *game, t_ergb type)
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
		game->map->ceiling_color = rgb_to_hex(game->map->ceiling->r, \
								game->map->ceiling->g, game->map->ceiling->b);
	}
	if (type == FLO)
	{
		game->map->floor->r = ft_atoi(temp[0]);
		game->map->floor->g = ft_atoi(temp[1]);
		game->map->floor->b = ft_atoi(temp[2]);
		game->map->floor_color = rgb_to_hex(game->map->floor->r, \
								game->map->floor->g, game->map->floor->b);
	}
	free(line);
	free_tab(temp);
}

void	fill_tex(char *line, t_tex *tex, t_txt type)
{
	if (type == NO)
	{
		tex->no = ft_dup(line);
		if (tex->no == NULL)
			return (printf("texture no is null\n"), free(line));
	}
	if (type == SO)
	{
		tex->so = ft_dup(line);
		if (tex->so == NULL)
			return (printf("texture no is null\n"), free(line));
	}
	if (type == WE)
	{
		tex->we = ft_dup(line);
		if (tex->we == NULL)
			return (printf("texture no is null\n"), free(line));
	}
	if (type == EA)
	{
		tex->ea = ft_dup(line);
		if (tex->ea == NULL)
			return (printf("texture no is null\n"), free(line));
	}
	free(line);
}

static char	**heap_map(size_t len, t_game *game)
{
	char	**map;

	map = ft_calloc(sizeof(char *), len + 1);
	if (!map)
		return (NULL);
	game->map->height = (int)get_list_len(game->list);
	return (map);
}

void	fill_list_to_map(t_game *game, t_list **list)
{
	t_list	*temp;
	char	*line;
	size_t	i;

	game->map->map = heap_map(get_list_len(*list), game);
	temp = *list;
	if (!temp)
		return (printf("Error malloc\n"), exit_prog(game));
	i = 0;
	get_len_line(game);
	while (temp)
	{
		line = copy_map_line(temp->value, game->map->width);
		if (!line)
			return (free_list(*list), exit_prog(game));
		if (!temp->next || i == 0)
			wall_is_good(game, line, 0, NULL);
		else
			wall_is_good(game, line, 1, temp->prev->value);
		game->map->map[i++] = ft_dup(line);
		fill_playerpos(line, game, i);
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
