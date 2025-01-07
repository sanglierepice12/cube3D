/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:24:44 by gsuter            #+#    #+#             */
/*   Updated: 2024/11/13 13:24:44 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	parse_ws(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = -1;
	while (++i, line[i])
	{
		if (line[i] == 32 || (line[i] >= '\t' && line[i] <= '\r'))
			continue ;
		break ;
	}
	return (i);
}

bool	parse_comma(char *line)
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

int	ft_comp_str(const char *src, const char *str)
{
	size_t	i;

	if (!str || !src)
		return (0);
	if (ft_strlen(src) != ft_strlen(str))
		return (0);
	i = 0;
	while (src[i])
	{
		if (src[i] == str[i])
			i++;
		else
			return (0);
	}
	if (src[i] || str[i])
		return (0);
	return (1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}
