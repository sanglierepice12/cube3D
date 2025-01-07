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

static void	fill_tex_f(char *line, t_tex *tex, t_txt type)
{
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
	fill_tex_f(line, tex, type);
	free(line);
}

void	fill_list_to_map(t_game *game, t_list **list)
{
	t_list	*temp;
	char	*line;
	size_t	i;

	game->map->map = heap_map(get_list_len(*list));
	if (!game->map->map)
		return (ft_puterr("Malloc\n"), free_list(*list), exit_prog(game));
	temp = *list;
	i = 0;
	get_len_line(game);
	while ((int)i <= game->map->height && temp)
	{
		line = copy_map_line(temp->value, game->map->width + 1);
		if (!line)
			return (free_list(*list), exit_prog(game));
		is_map_ok(line, game, &i, temp);
		fill_playerpos(line, game, i);
		temp = temp->next;
		free(line);
	}
}

void	fill_map_to_list(t_game *game, t_list **list, int fd)
{
	char	*line;
	int		count;

	count = 0;
	first_line(fd, list, game);
	while (777)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_full_of_one(line))
		{
			count++;
			game->map->height = (int)get_list_len(*list);
		}
		if (!is_line_m_ok(line) || (ft_comp_str(line, "\n") && count == 1))
		{
			ft_puterr("Line is invalid: '%s'\n");
			free(line);
			free_list(game->list);
			exit_prog(game);
		}
		ft_lst_add_back(list, ft_new_node(line));
		free(line);
	}
}
