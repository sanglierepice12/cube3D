/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_suit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:00:47 by gsuter            #+#    #+#             */
/*   Updated: 2025/01/08 11:13:19 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3D.h"

void	is_map_ok(char *line, t_game *game, size_t *i)
{
	if (is_full_of_one(line))
	{
		is_fst_line_ok(line, ft_strlen(line), game);
		game->map->map[(*i)++] = ft_dup(line);
	}
	else
	{
		is_game_line_ok(game, line, game->map->map[(*i) - 1]);
		game->map->map[(*i)++] = ft_dup(line);
	}
}

static void	free_rgb_stuff(t_game *game, char *temp, char *line)
{
	ft_puterr("Nothing in rgb\n");
	free(temp);
	free(line);
	exit_prog(game);
}

void	fill_rgb(char *temp, t_game *game, t_ergb type, char *line)
{
	char	**tempax;
	char	*tempinou;

	tempinou = rm_space_rgb(temp);
	if (!tempinou)
	{
		free(temp);
		exit_prog(game);
	}
	tempax = ft_split(tempinou, ',');
	if (!tempax)
	{
		ft_puterr("Malloc\n");
		free(temp);
		free(line);
		return (free(tempinou), exit_prog(game));
	}
	free(tempinou);
	if (!tempax[2])
		return (free_tab(tempax), free_rgb_stuff(game, temp, line));
	fill_rgb_struct(game, tempax, type);
	free(temp);
	free_tab(tempax);
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
		// if(game->map->width > 500)
		// {
		// 	ft_puterr("We don't handle map this big !\n");
		// 	exit_prog(game);
		// }
		temp = temp->next;
		free(line);
	}
}
