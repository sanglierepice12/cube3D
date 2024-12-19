/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_text_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:32:24 by gsuter            #+#    #+#             */
/*   Updated: 2024/12/18 16:15:08 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3D.h"

static bool	need_to_return(char *line, t_game *game)
{
	if (ft_comp_str(line, "\n") || is_line_full_spaces(line))
		return (true);
	if (game->map->count > 6)
	{
		printf("Error too much information\n");
		exit_prog(game);
	}
	return (false);
}

void	get_rgb(char *line, t_game *game)
{
	size_t	i;
	size_t	y;
	char	*temp;

	if (need_to_return(line, game))
		return ;
	i = parse_ws(line);
	y = i + parse_ws(line + i + 1) + 1;
	temp = rm_bs_wp(line + y);
	if (!temp)
		return (free(line), exit_prog(game));
	if (line[i] == 'F' && check_rgb(temp))
		return (fill_rgb(temp, game, FLO));
	if (line[i] == 'C' && check_rgb(temp))
		return (fill_rgb(temp, game, CEI));
	free(temp);
}

void	get_textures(char *line, t_tex *texture, t_game *game)
{
	size_t	i;
	size_t	y;
	char	*temp;

	if (need_to_return(line, game))
		return ;
	i = parse_ws(line);
	y = i + parse_ws(line + i + 2) + 2;
	temp = rm_bs_wp(line + y);
	if (!temp)
		return (free(line), exit_prog(game));
	if (line[i] == 'N' && line[i + 1] == 'O' && check_texture(temp))
		return (fill_tex(temp, texture, NO));
	if (line[i] == 'S' && line[i + 1] == 'O' && check_texture(temp))
		return (fill_tex(temp, texture, SO));
	if (line[i] == 'W' && line[i + 1] == 'E' && check_texture(temp))
		return (fill_tex(temp, texture, WE));
	if (line[i] == 'E' && line[i + 1] == 'A' && check_texture(temp))
		return (fill_tex(temp, texture, EA));
	free(temp);
}
