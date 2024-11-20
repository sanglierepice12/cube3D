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

int	parse_ws(char *line)
{
	int	i;

	i = -1;
	while (++i, line[i])
	{
		if (line[i] == 32 || (line[i] > 8 && line[i] < 14))
			continue ;
		break ;
	}
	return (i);
}

static bool	is_valid_char(char	*temp)
{
	printf("%c", temp[0]);
	if (temp[0] == 'N' && temp[1] == 'O' && check_texture(temp + parse_ws(temp + 2) + 2))
		return (true);
	if (temp[0] == 'S' && temp[1] == 'O' && check_texture(temp + parse_ws(temp + 2) + 2))
		return (true);
	if (temp[0] == 'W' && temp[1] == 'E' && check_texture(temp + parse_ws(temp + 2) + 2))
		return (true);
	if (temp[0] == 'E' && temp[1] == 'A' && check_texture(temp + parse_ws(temp + 2) + 2))
		return (true);
	if (temp[0] == 'F' && check_rgb(temp + parse_ws(temp + 1) + 1))
		return (true);
	if (temp[0] == 'C' && check_rgb(temp + parse_ws(temp + 1) + 1))
		return (true);
	if (temp[0] == '1')
		return (true);
	return (false);
}

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

bool	is_line_ok(char *line)
{
	if (!is_valid_char(line))
		return (false);
	return (true);
}
