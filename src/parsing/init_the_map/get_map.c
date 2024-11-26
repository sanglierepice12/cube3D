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

/*static void	print_lst(t_list **list)
{
	t_list	*temp;
	temp = *list;
	while (temp->next)
	{
		printf("[%s]", temp->value);
		temp = temp->next;
	}
	printf("[%s]", temp->value);
}*/

/*static void	get_rgb(char *line, t_game *game)
{
	size_t	i;
	size_t	y;
	char	*temp;

	if (ft_comp_str(line, "\n") || is_line_full_spaces(line))
		return ;
	if (game->map->count > 6)
	{
		printf("Error too much information\n");
		exit_prog(game);
	}
	i = parse_ws(line);
	y = i + parse_ws(line + i + 1) + 1;
	temp = rm_bs_wp(line + y);
	//printf("%s\n", temp);
	if (line[i] == 'F' && check_rgb(temp))
		return (fill_rgb(temp, game->map, FLO), game->map->count++, (void)0);
	if (line[i] == 'C' && check_rgb(line + parse_ws(temp)))
		return (fill_rgb(temp, game->map, CEI), game->map->count++, (void)0);
	free(temp);
	if (!is_line_ok(line, game->map))
		return(printf("Error, line is invalid : %s\n", line), exit_prog(game));
}*/

static void	get_textures(char *line, t_texture *texture, t_game *game)
{
	size_t	i;
	size_t	y;
	char	*temp;

	if (ft_comp_str(line, "\n") || is_line_full_spaces(line))
		return ;
	if (game->map->count > 6)
	{
		printf("Error too much information\n");
		exit_prog(game);
	}
	i = parse_ws(line);
	y = i + parse_ws(line + i + 2) + 2;
	temp = rm_bs_wp(line + y);
	if (!temp)
		return (free(line),	exit_prog(game));
	if (line[i] == 'N' && line[i + 1] == 'O' && check_texture(temp))
		return (fill_tex(temp, texture, NO), game->map->count++, (void)0);
	if (line[i] == 'S' && line[i + 1] == 'O' && check_texture(temp))
		return (fill_tex(temp, texture, SO), game->map->count++, (void)0);
	if (line[i] == 'W' && line[i + 1] == 'E' && check_texture(temp))
		return (fill_tex(temp, texture, WE), game->map->count++, (void)0);
	if (line[i] == 'E' && line[i + 1] == 'A' && check_texture(temp))
		return (fill_tex(temp, texture, EA), game->map->count++, (void)0);
	free(temp);
}

static void	first_line(const int fd, t_list **list, t_game *game)
{
	char	*line;

	line = NULL;
	while (777)
	{
		line = get_next_line(fd);
		if (!line)
			simple_exit("Nothing in the file ...", 1);
		get_textures(line, game->map->texture, game);
		if ((line + parse_ws(line))[0] == '1' && game->map->count == 4)
			break ;
		if (!is_line_ok(line))
			exit_prog(game);
	//get_rgb(line, game);
		free(line);
	}
	*list = ft_new_node(line);
	free(line);
	line = NULL;
}

static void	fill_tap_to_map(t_game *game, t_list **list, int fd)
{
	char	*line;

	first_line(fd, list, game);
	line = NULL;
	while (777)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_comp_str(line, "\n") || is_line_full_spaces(line))
		{
			free(line);
			continue ;
		}
		if (!is_line_m_ok(line))
		{
			free_list(game->list);
			exit_prog(game);
		}
		ft_lst_add_back(list, ft_new_node(line));
		free(line);
	}
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


void	get_map(t_game *game, char *file)
{
	int	fd;

	if (!check_ext(file))
		exit_prog(game);
	fd = open_map(file, game);
	fill_tap_to_map(game, &game->list, fd);
	close(fd);
	fill_list_to_map(game, &game->list);
	free_list(game->list);
}
