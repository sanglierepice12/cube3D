/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsuter <gsuter@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:11:19 by gsuter            #+#    #+#             */
/*   Updated: 2024/11/13 14:11:19 by gsuter           ###   ########.fr       */
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

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

bool	is_ws(char c)
{
	if (c == 32 || (c >= '\t' && c <= '\r'))
		return (true);
	return (false);
}

char	*rm_bs_wp(char *str)
{
	char	*dest;
	ssize_t	i;
	ssize_t	y;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
	{
		while (str[i] && is_ws(str[i]))
			i--;
	}
	dest = ft_calloc(sizeof(char), i + 2);
	if (!dest)
		return (NULL);
	y = -1;
	while (y++, y != i + 1)
		dest[y] = str[y];
	dest[y] = '\0';
	return (dest);
}

char	*ft_dup(const char *s)
{
	size_t	i;
	char	*new;

	if (!s)
		return (NULL);
	new = ft_calloc(sizeof(char), ft_strlen(s) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}