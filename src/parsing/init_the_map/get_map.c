/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:42:26 by jedusser          #+#    #+#             */
/*   Updated: 2024/11/13 13:03:35 by gsuter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

static void	first_line(const int fd, char *line, t_list **list, t_game *game)
{
	while (777)
	{
		line = get_next_line(fd);
		if (!line)
			simple_exit("Nothing in the file ...", 1);
		if (!ft_comp_str(line, "\n") || !is_line_full_spaces(line) /*|| fill_in_list(line, game->map->texture)*/)
			break ;
		free(line);
	}
	line = rm_bs_wp(line);
	if (!line)
	{
		printf("Error malloc\n");
		exit_prog(game);
	}
	if (!is_line_ok(game->map, line))
	{
		free(line);
		simple_exit("Something wrong in the file ...", 1);
	}
	*list = ft_new_node(line);
	free(line);
	line = NULL;
}

static void	fill_tap_to_map(t_game *game, t_list **list, int fd)
{
	char	*line;

	line = NULL;
	first_line(fd, line, list, game);
	while (452)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_comp_str(line, "\n") || is_line_full_spaces(line))
		{
			free(line);
			continue ;
		}
		line = rm_bs_wp(line);
		if (!line)
			simple_exit("Error malloc", 1);
		if (!is_line_ok(game->map, line))
			exit_parse(game);
		if (fill_in_list(line, game->map->texture))
			ft_lst_add_back(list, ft_new_node(line));
		free(line);
	}
}

static int	open_map(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		simple_exit("Error occurred while opening the document...", 1);
	return (fd);
}

static void	check_ext(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4)
		simple_exit("Error: Wrong extension.", 1);
	if (ft_strncmp(file + (len - 4), ".cub", 4))
		simple_exit("Error: Wrong extension, it's not a .cub.", 1);
}

void	get_map(t_game *game, char *file)
{
	int	fd;

	check_ext(file);
	fd = open_map(file);
	fill_tap_to_map(game, &game->list, fd);
	close(fd);
	fill_list_to_map(game);
	free_list(game->list);
}
