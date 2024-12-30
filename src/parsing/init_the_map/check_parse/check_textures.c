/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:30:49 by sanglier          #+#    #+#             */
/*   Updated: 2024/12/20 16:28:54 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3D.h"

static bool	wall_follow(const char *line, size_t i)
{
	while (line[i--])
	{
		if (line[i] == '#')
			continue ;
		if (line[i] != '1')
			return (false);
	}
	/*while (line[i++])
	{
		if (line[i] == '1' && !line[i + 1])
			return (true);
		if (line[i] == '#' && line[i + 1] == '#')
			continue ;
		if (line[i] != '1')
			break ;
	}
	 return (false);
	 */
	return (true);
}

static bool	is_closed(const char *prev, const char *line, size_t len)
{
	while (len--, line[len] == '1')
	{
		if (prev[len] == '#')
			continue ;
		if (prev[len] == '1')
			return (true);
		return (false);
	}
	if (prev[len] != '1')
		return (false);
	return (true);
}

bool	is_full_of_one(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i++] == '1')
			continue;
		if (line[i] == '#')
			return (true);
		return (false);
	}
	return (true);
}

void	wall_is_good(t_game *game, char *line, bool flag, char *prev)
{
	size_t	len;
	char	*temp;

	len = ft_strlen(line);
	if (flag && (!ft_comp_str(line, "\n") || !is_line_full_spaces(line)))
	{
		temp = copy_map_line(prev, game->map->width);
		if (!temp)
			force_exit(line, game);
		while (len--, line[len])
		{
			if (line[len] == '#')
				continue ;
			if (line[len] != '1')
				break ;
			if (temp[len] == '#' && !is_closed(temp, line, len + 1))
				break ;
			if (temp[len] == '0' && temp[len + 1] != '1')
				break ;
			return (free(temp));
		}
		free(temp);
	}
	if (!flag && wall_follow(line, len))
		return ;
	force_exit(line, game);
}

bool	rgb_is_good(char *line)
{
	char	**temp;
	char	*tempinou;
	int		i;

	i = -1;
	tempinou = rm_space_rgb(line);
	if (!tempinou)
		return (false);
	if (ft_strlen(tempinou) > 11)
		return (false);
	temp = ft_split(tempinou, ',');
	if (!temp)
		return (free(tempinou), false);
	free(tempinou);
	while (++i, temp[i])
	{
		if (ft_atoi(temp[i]) > 255 || ft_atoi(temp[i]) < 0)
			return (free_tab(temp), ft_puterr("rgb out of range\n"), false);
	}
	free_tab(temp);
	return (true);
}

bool	check_rgb(char *line)
{
	size_t	i;

	i = parse_ws(line);
	if (!parse_comma(line + parse_ws(line)))
		return (false);
	if (!rgb_is_good(line + i))
		return (false);
	return (true);
}

bool	check_texture(char	*line)
{
	int	fd;

	if (!line)
		return (false);
	if (!ft_comp_str(".xpm", line + ft_strlen(line) - 4))
	{
		ft_puterr("It's texture is not an xpm...\n");
		return (false);
	}
	fd = open(line, O_RDONLY);
	if (fd == -1)
	{
		ft_puterr("No textures...\n");
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}
