/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:36:49 by gsuter            #+#    #+#             */
/*   Updated: 2024/11/13 15:36:49 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3D.h"

bool	is_line_full_spaces(char *line)
{
	ssize_t	i;

	i = -1;
	while (i++, line[i])
	{
		if (line[i] == 32 || (line[i] > 8 && line[i] < 14))
			continue ;
		return (false);
	}
	return (true);
}

static void	fill_tex(char *line, t_texture *texture, e_txt type)
{
	//printf("$%s$\n", line);
	if (type == NO)
	{
		texture->no = ft_dup(line);
		if (texture->no == NULL)
			printf("texture no is null\n");
	}
	if (type == SO)
	{
		texture->so = ft_dup(line);
		if (texture->so == NULL)
			printf("texture no is null\n");
	}
	if (type == WE)
	{
		texture->we = ft_dup(line);
		if (texture->we == NULL)
			printf("texture no is null\n");
	}
	if (type == EA)
	{
		texture->ea = ft_dup(line);
		if (texture->ea == NULL)
			printf("texture no is null\n");
	}
}

bool	fill_in_list(char *temp, t_texture *texture)
{
	size_t	i;
	size_t	y;

	i = parse_ws(temp);
	y = i + parse_ws(temp + i + 2) + 2;
	if (temp[i] == 'N' && temp[i + 1] == 'O')
		return (fill_tex(temp + y, texture, NO), false);
	if (temp[i] == 'S' && temp[i + 1] == 'O')
		return (fill_tex(temp + y, texture, SO), false);
	if (temp[i] == 'W' && temp[i + 1] == 'E')
		return (fill_tex(temp + y, texture, WE), false);
	if (temp[i] == 'E' && temp[i + 1] == 'A')
		return (fill_tex(temp + y, texture, EA), false);
	return (true);
}

bool	is_line_ok(t_map *map, char	*temp)
{
	size_t	i;
	size_t	y;

	i = parse_ws(temp);
	y = i + parse_ws(temp + i + 2) + 2;
	if (temp[i] == 'N' && temp[i + 1] == 'O' && check_texture(temp + y))
		return (map->count++, true);
	if (temp[i] == 'S' && temp[i + 1] == 'O' && check_texture(temp + y))
		return (map->count++, true);
	if (temp[i] == 'W' && temp[i + 1] == 'E' && check_texture(temp + y))
		return (map->count++, true);
	if (temp[i] == 'E' && temp[i + 1] == 'A' && check_texture(temp + y))
		return (map->count++, true);
	if (temp[i] == 'F' && check_rgb(temp + parse_ws(temp + 1) + 1))
		return (map->count++, true);
	if (temp[i] == 'C' && check_rgb(temp + parse_ws(temp + 1) + 1))
		return (map->count++, true);
	if (temp[i] == '1' && map->count == 6)
		return (true);
	printf("Line is invalid: '%s'\n", temp);
	free(temp);
	printf("Something wrong in the file ...");
	return (false);
}
