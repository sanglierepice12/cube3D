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
		return (free(str), NULL);
	y = -1;
	while (y++, y != i + 1)
		dest[y] = str[y];
	dest[y] = '\0';
	free(str);
	return (dest);
}
/*
char *rm_bs_wp(char *str)
{
	char	*dest;
	size_t	i;
	size_t	len;

	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	if (str[len] == '\n')
		len++;
	dest = ft_calloc(len + 1, sizeof(char));
	if (!dest)
		exit_prog("Error: Calloc rm_bs and wp [gnl]", 1);
	i = 0;
	while (i < len && str[i] != '\n')
	{
		dest[i] = str[i];
		i++;
	}
	i = len - 1;
	while (is_ws(dest[i]))
	{
		dest[i] = '\0';
		i--;
	}
	free(str);
	return (dest);
}
*/
