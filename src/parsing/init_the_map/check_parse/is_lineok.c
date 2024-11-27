/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_lineok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:30:47 by gsuter            #+#    #+#             */
/*   Updated: 2024/11/27 15:30:47 by gsuter           ###   ########.fr       */
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

bool	is_line_m_ok(char *line)
{
	size_t	i;

	i = parse_ws(line);
	while (line[i])
	{
		if (line[i + 1] && (line[i] == 32 || (line[i] > 8 && line[i] < 14)))
			line[i] = '0';
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S'\
			&& line[i] != 'W' && line[i] != 'E' && line[i] != '\n')
		{
			free(line);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	is_line_ok(char	*line)
{
	size_t	i;

	if (ft_comp_str(line, "\n") || is_line_full_spaces(line))
		return (true);
	i = parse_ws(line);
	if (line[i] == 'N' && line[i + 1] == 'O')
		return (true);
	if (line[i] == 'S' && line[i + 1] == 'O')
		return (true);
	if (line[i] == 'W' && line[i + 1] == 'E')
		return (true);
	if (line[i] == 'E' && line[i + 1] == 'A')
		return (true);
	if (line[i] == 'F')
		return (true);
	if (line[i] == 'C')
		return (true);
	printf("Line is invalid: '%s'\n", line);
	free(line);
	return (false);
}
