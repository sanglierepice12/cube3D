/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:52:22 by sanglier          #+#    #+#             */
/*   Updated: 2024/12/20 16:36:42 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3D.h"

void	fill_rgb_struct(t_game *game, char **temp, t_ergb type)
{
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
}

void	fill_rgb(char *line, t_game *game, t_ergb type)
{
	char	**temp;
	char	*tempinou;

	tempinou = rm_space_rgb(line);
	if (!tempinou)
	{
		free(line);
		exit_prog(game);
	}
	temp = ft_split(tempinou, ',');
	if (!temp)
		return (ft_puterr("Malloc\n"), free(line), free(tempinou), exit_prog(game));
	free(tempinou);
	if (!temp[2])
		return (ft_puterr("Nothing in rgb\n"), free(line), exit_prog(game));
	fill_rgb_struct(game, temp, type);
	free(line);
	free_tab(temp);
}

void	fill_tex(char *line, t_tex *tex, t_txt type)
{
	if (type == NO)
	{
		if (!tex->no)
			tex->no = ft_dup(line);
		if (!tex->no)
			return (ft_puterr("texture no is null\n"), free(line));
	}
	if (type == SO)
	{
		if (!tex->so)
			tex->so = ft_dup(line);
		if (!tex->so)
			return (ft_puterr("texture no is null\n"), free(line));
	}
	if (type == WE)
	{
		if (!tex->we)
			tex->we = ft_dup(line);
		if (!tex->we)
			return (ft_puterr("texture no is null\n"), free(line));
	}
	if (type == EA)
	{
		if (!tex->ea)
			tex->ea = ft_dup(line);
		if (!tex->ea)
			return (ft_puterr("texture no is null\n"), free(line));
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
	if (!game->map->map)
		return (ft_puterr("Malloc\n"), free_list(*list), exit_prog(game));
	temp = *list;
	i = 0;
	get_len_line(game);
	while (temp)
	{
		line = copy_map_line(temp->value, game->map->width);
		if (!line)
			return (free_list(*list), exit_prog(game));
	/*	if (is_end_wall(line, temp->prev->value))
			break ;*/
		/*if (!temp->next || i == 0)
			wall_is_good(game, line, 0, NULL);*/
		if (line[0] == '\n')
			break ;
		if (is_full_of_one(line))
			wall_is_good(game, line, 0, NULL);
		else if (is_end_wall(temp->prev->value))
		{
			wall_is_good(game, temp->prev->value, 0, NULL);
			free(line);
			break ;
		}
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
	while (777)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!is_line_m_ok(line))
		{
			free_list(game->list);
			exit_prog(game);
		}
		ft_lst_add_back(list, ft_new_node(line));
		free(line);
	}
}
