/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_suit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:00:47 by gsuter            #+#    #+#             */
/*   Updated: 2024/12/20 16:05:12 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3D.h"

char	*copy_map_line(char *str, ssize_t width)
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
	dest = ft_calloc(sizeof(char), width + 1);
	if (!dest)
		return (NULL);
	y = -1;
	while (y++, y != i + 1)
		dest[y] = str[y];
	return (dest);
}

void	get_len_line(t_game *game)
{
	t_list	*temp;
	char	*line;

	temp = game->list;
	while (temp)
	{
		line = rm_bs_wp(temp->value);
		if (!line)
		{
			free_list(game->list);
			exit_prog(game);
		}
		if (game->map->width < (int) ft_strlen(line))
			game->map->width = (int) ft_strlen(line);
		temp = temp->next;
		free(line);
	}
}
