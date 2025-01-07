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

void	is_map_ok(char *line, t_game *game, size_t *i, t_list *temp)
{
	if (is_full_of_one(line))
	{
		is_fst_line_ok(line, ft_strlen(line), game);
		game->map->map[(*i)++] = ft_dup(line);
	}
	else
	{
		is_game_line_ok(game, line, temp->prev->value);
		game->map->map[(*i)++] = ft_dup(line);
	}
}

void	fill_rgb(char *line, t_game *game, t_ergb type)
{
	char	**temp;
	char	*tempinou;

	tempinou = rm_space_rgb(line);
	if (!tempinou)
	{
		free(line);
		exit_prog(game);
	}
	temp = ft_split(tempinou, ',');
	if (!temp)
	{
		ft_puterr("Malloc\n");
		free(line);
		return (free(tempinou), exit_prog(game));
	}
	free(tempinou);
	if (!temp[2])
		return (ft_puterr("Nothing in rgb\n"), free(line), exit_prog(game));
	fill_rgb_struct(game, temp, type);
	free(line);
	free_tab(temp);
}

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
		while (i >= 0 && (str[i] && is_ws(str[i])))
			i--;
	}
	dest = ft_calloc(sizeof(char), width);
	if (!dest)
		return (NULL);
	y = -1;
	while (y++, y != i + 1)
		dest[y] = str[y];
	while (y < width - 1)
		dest[y++] = '#';
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
