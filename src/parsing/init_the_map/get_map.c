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

static void	first_line(int fd, char *line, t_list **list)
{
	line = get_next_line(fd);
	if (!line)
		ft_exit("Nothing in the file ...", 1);
	check_line(line);
	*list = ft_new_node(line);
	free(line);
}

static void	fill_tap_to_map(t_list **list, int fd)
{
	char	*line;

	line = NULL;
	first_line(fd, line, list);
	while (452)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		check_line(line);
		if (ft_comp_str(line, "\n"))
		{
			free(line);
			continue;
		}
		ft_lst_add_back(list, ft_new_node(line));
		free(line);
	}
}

static int	open_map(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_exit("Error occurred while opening the document...", 1);
	return (fd);
}

static void	check_ext(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4)
		ft_exit("Error: Wrong extension. [fill]", 1);
	if (ft_strncmp(file + (len - 4), ".cub", 4))
		ft_exit("Error: Wrong extension. [fill]", 1);
}

void	get_map(t_game *game, char *file)
{
	int	fd;

	check_ext(file);
	fd = open_map(file);
	fill_tap_to_map(&game->list, fd);
	close(fd);
}
