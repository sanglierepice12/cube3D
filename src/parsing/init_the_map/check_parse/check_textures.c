/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglier <sanglier@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:30:49 by sanglier          #+#    #+#             */
/*   Updated: 2024/11/20 16:30:49 by sanglier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3D.h"

bool	rgb_is_good(char *line)
{
	char	**temp;
	int		i;

	i = -1;
	temp = ft_split(line, ',');
	if (!temp)
		return (false);
	while (++i, temp[i])
	{
		if (ft_atoi(temp[i]) > 255 || ft_atoi(temp[i]) < 0)
			return (false);
	}
	free_tab(temp);
	return (true);
}

static bool	parse_comma(char *line)
{
	ssize_t	i;
	int		count;

	i = -1;
	count = 0;
	while (++i, line[i])
	{
		if (line[i] == ',')
			count++;
	}
	if (count != 2)
		return (false);
	return (true);
}

bool	check_rgb(char *line)
{
	size_t	i;

	i = parse_ws(line);
	if (!parse_comma(line + parse_ws(line)))
		return (false);
	if (ft_strlen(line + i) > 11)
		return (false);
	if (!rgb_is_good(line + i))
		return (false);
	return (true);
}

bool	check_texture(char	*line)
{
	int	fd;

	//printf("$%s$\n", line);
	if (!line)
		return (false);
	fd = open(line, O_RDONLY);
	if (fd == -1)
	{
		printf("no textures...\n");
		return (false);
	}
	close(fd);
	return (true);
}
