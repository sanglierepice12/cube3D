/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglier <sanglier@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:56:00 by sanglier          #+#    #+#             */
/*   Updated: 2024/12/19 12:56:00 by sanglier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3D.h"

char *rm_space_rgb(char *line)
{
	char	*dup;
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (line[i++])
	{
		if (is_ws(line[i]))
			continue;
		k++;
	}
	dup = ft_calloc(sizeof(char), k + 1);
	if (!dup)
		return (NULL);
	i = 0;
	k = 0;
	while (line[i])
	{
		if (is_ws(line[i]))
		{
			i++;
			continue;
		}
		dup[k++] = line[i++];
	}
	return (dup);
}