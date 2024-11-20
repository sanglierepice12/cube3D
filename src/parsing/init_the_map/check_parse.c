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

#include "../../../include/cub3D.h"

int	parse_whitespace(char *line)
{
	ssize_t	i;

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
	int		i;

	i = parse_whitespace(temp);
	if ((temp + i)[0] == 'N' && (temp + i)[1] == 'O')
		return (true);
	if ((temp + i)[0] == 'S' && (temp + i)[1] == 'O')
		return (true);
	if ((temp + i)[0] == 'W' && (temp + i)[1] == 'E')
		return (true);
	if ((temp + i)[0] == 'E' && (temp + i)[1] == 'A')
		return (true);
	if ((temp + i)[0] == 'F')
		return (true);
		/*return (check_rgb());*/
	if ((temp + i)[0] == 'C')
		return (true);
		/*return (check_rgb());*/
	if ((temp + i)[0] == '1')
		return (true);
		/*return (check_rgb());*/
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

bool	is_line_ok(char *temp)
{
	if (!is_valid_char(temp))
		return (false);
	return (true);
}
