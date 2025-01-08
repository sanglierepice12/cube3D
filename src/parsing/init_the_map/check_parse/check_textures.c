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

bool	is_closed(const char *prev, const char *line, size_t len)
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
		if (line[i] == '1')
			i++;
		else
			break ;
	}
	if (line[i] == '\0' || (line[i] == '\n' && i != 0) || line[i] == '#')
		return (true);
	else
		return (false);
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
		return (free(tempinou), false);
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

bool	check_rgb(char *temp, char *line, t_game *game)
{
	size_t	i;

	i = parse_ws(temp);
	if (!parse_comma(temp + parse_ws(temp)) || !rgb_is_good(temp + i))
	{
		ft_puterr("wrong struct of rgb\n");
		free(line);
		free(temp);
		exit_prog(game);
		return (false);
	}
	return (true);
}

bool	check_texture(char	*temp, char *line, t_game *game)
{
	int	fd;

	if (!temp)
		return (false);
	if (!ft_comp_str(".xpm", temp + ft_strlen(temp) - 4))
	{
		ft_puterr("It's texture is not an xpm...\n");
		return (false);
	}
	fd = open(temp, O_RDONLY);
	if (fd == -1)
	{
		ft_puterr("No textures...\n");
		close(fd);
		free(temp);
		free(line);
		exit_prog(game);
	}
	close(fd);
	return (true);
}
