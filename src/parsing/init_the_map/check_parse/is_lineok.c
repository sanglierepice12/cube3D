/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_lineok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:08:00 by gsuter            #+#    #+#             */
/*   Updated: 2024/12/20 16:27:15 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3D.h"

void	is_matter_ok(t_game *game, char *line)
{
	if (game->map->matt[F] != 1 || game->map->matt[C] != 1 || \
			game->map->matt[NO] != 1 || game->map->matt[SO] != 1 || \
			game->map->matt[WE] != 1 || game->map->matt[EA] != 1)
	{
		free(line);
		if (write(2, "Error\n matter wrong\n", 21) == -1)
			exit_prog(game);
		exit_prog(game);
	}
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

bool	is_line_m_ok(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i + 1] && is_ws(line[i]))
			line[i] = '1';
		if (!ft_strchr("10NSWE\n", line[i]))
			return (false);
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
	ft_puterr("Line is invalid\n");
	free(line);
	return (false);
}
