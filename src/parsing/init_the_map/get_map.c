/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:42:26 by jedusser          #+#    #+#             */
/*   Updated: 2024/12/18 16:14:30 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

void	first_line(int fd, t_list **list, t_game *game)
{
	char	*line;

	line = NULL;
	while (777)
	{
		line = get_next_line(fd);
		if (!line)
			simple_exit("Nothing in the file ...", 1);
		get_textures(line, game->map->tex, game);
		get_rgb(line, game);
		if ((line + parse_ws(line))[0] == '1' && game->map->count == 6)
			break ;
		if (!is_line_ok(line))
			exit_prog(game);
		free(line);
	}
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
		printf("Error occurred while opening the document...");
		exit_prog(game);
	}
	return (fd);
}

static bool	check_ext(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4)
		return (printf ("Error: Wrong extension."), false);
	if (ft_strncmp(file + (len - 4), ".cub", 4))
		return (printf ("Error: Wrong extension, it's not a .cub."), false);
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
	if (game->map->count != 7)
	{
		printf("Error, no player position\n"); // !!!!! sortie erreur
		exit_prog(game);
	}
}
