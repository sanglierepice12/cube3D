/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:42:26 by jedusser          #+#    #+#             */
/*   Updated: 2024/12/20 16:26:43 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void	exit_parsing(t_game *game)
{
	ft_puterr("Line is invalid\n");
	free_list(game->list);
	exit_prog(game);
}

void	first_line(int fd, t_list **list, t_game *game)
{
	char	*line;

	line = NULL;
	while (777)
	{
		line = get_next_line(fd);
		if (!line)
			return (ft_puterr("Nothing in the file ...\n"), exit_prog(game));
		get_rgb(line, game);
		get_textures(line, game->map->tex, game);
		calculate_matter(line, game);
		if ((line + parse_ws(line))[0] == '1' && game->map->count == 6)
			break ;
		if (!is_line_ok(line))
			exit_prog(game);
		free(line);
	}
	is_matter_ok(game, line);
	if (!is_line_m_ok(line) || have_double_ext(game->map->tex))
		return (free(line), exit_parsing(game));
	*list = ft_new_node(line);
	free(line);
	line = NULL;
}

static int	open_map(char *file, t_game *game)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_puterr("Error occurred while opening the document...\n");
		exit_prog(game);
	}
	return (fd);
}

static bool	check_ext(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4)
		return (ft_puterr("Wrong extension.\n"), false);
	if (ft_strncmp(file + (len - 4), ".cub", 4))
		return (ft_puterr("Wrong extension, it's not a .cub.\n"), false);
	return (true);
}

void	init_parse(t_game *game, char *file)
{
	int	fd;

	if (!check_ext(file))
		exit_prog(game);
	fd = open_map(file, game);
	fill_map_to_list(game, &game->list, fd);
	close(fd);
	fill_list_to_map(game, &game->list);
	free_list(game->list);
	if (!is_really_one(game->map->map[game->map->height + 1]))
	{
		ft_puterr("Line is not a wall\n");
		exit_prog(game);
	}
	if (game->map->count != 7)
	{
		ft_puterr("No player position\n");
		exit_prog(game);
	}
}
